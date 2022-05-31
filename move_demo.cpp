#include "images.h"
#include <numeric> // std::inner_product
#include <vector>
#include <functional>

// movement globals - needs to be localised
int prevLeftVel = 0;
int prevRightVel = 0;
int forwardVel = 0;
const int MAX_VEL = 40;
int prevError = 0;
int minCol = 30;

// reverse engineered set_motor method, will calculate perfect speed
// to reach the target speed in 1 step, doesnt work for speeds above 24
// because that will go over the robots max speed and take more than 1 step
int get_vel(int tarVel, int prevVel)
{
	int vel = (tarVel - prevVel) / 0.6 + prevVel;
	return vel;
}

// WARNING use only with target velocity below 24
int set_vel(int tarVel, int velD)
{
	velD = (tarVel - velD < -24) ? 12 : velD;
	velD = (tarVel + velD > 24) ? 12 : velD;

	int velLeft = get_vel(tarVel + velD, prevLeftVel);
	prevLeftVel = (tarVel + velD);

	int velRight = get_vel(tarVel - velD, prevRightVel);
	prevRightVel = (tarVel - velD);

	forwardVel = tarVel;
	set_motors(velLeft, velRight);
	return 0;
}
/*
 while (vel > MAX_VEL || vel < -MAX_VEL) {
		if (vel > 0) set_motors(MAX_VEL,MAX_VEL);
		else set_motors(-MAX_VEL,-MAX_VEL);
		prevVel += vel;
		update_sim(1500);
		vel = (tarVel - prevVel) / 0.6 + prevVel;
	}
	set_motors(vel,vel);
	update_sim(1500);
 **/
bool pixelHasColour(int colourId, Pixel pixel)
{
	double threshold = 1.5; // the amount by which the red, green or blue has to be above the other two
	double luminosity = (pixel.r + pixel.g + pixel.b) / 3.0;

	/*std::cout << "Red: " << (int)pixel.r << std::endl;
	std::cout << "Green: " << (int)pixel.g << std::endl;
	std::cout << "Blue: " << (int)pixel.b << std::endl;
	std::cout << "Luminosity: " << (int)luminosity << std::endl;*/

	switch (colourId)
	{
	case 0: // red
		if (pixel.r > luminosity * threshold && pixel.r > minCol)
			return true; // if pixel red is more than luminosity by some threshold and mainly red, pixel is red
		break;
	case 1: // green
		if (pixel.g > luminosity * threshold && pixel.g > minCol)
			return true; // if pixel green is more than luminosity by some threshold and mainly green, pixel is green
		break;
	case 2: // blue
		if (pixel.b > luminosity * threshold && pixel.b > minCol)
			return true; // if pixel blue is more than luminosity by some threshold and mainly blue, pixel is blue
		break;
	case 3: // black
		if (luminosity < minCol)
			return true; // if pixel is darker than minCol, pixel is black
		break;
	}
	return false;
}

int offset_calc(bool isBot)
{
	int row = (isBot) ? camera_image.height - 1 : 0;
	int pixels = 0;
	int off = 0;
	for (int i = 0; i < camera_image.width; i++)
	{   
		if (pixelHasColour(3, get_camera_pixel(row, i)))
		{
			pixels++;
			off += i - (int)(camera_image.width / 2);
		}
	}
	off = (pixels > 0) ?  off/pixels : -camera_image.width / 2 -1;
	
	return off;
}
int side_offset(bool isLeft) {
	int col = (isLeft) ? 0 : camera_image.width - 1;
	int pixels = 0;
	float off = 0;
	for (int i = 0; i < camera_image.height; i++)
	{   
		if (pixelHasColour(3, get_camera_pixel(i, col)))
		{
			pixels++;
			off += i - (int)(camera_image.height / 2);
		}
	}
	off = (pixels > 0) ?  off/pixels : -camera_image.height / 2 -1;
	
	return off;
}
int turning_move(int error, int prevError, int f_vel, int step)
{

	// coefficients need tuning
	const double propGain = 0.24;
	const double derivGain = 0.12;
	// first step is just forward
	if (step == 0)
		set_vel(f_vel, 0);
	else
	{
		int velDiff = error * propGain + (error - prevError) * derivGain;
		set_vel(f_vel, velDiff);
	}
	return 0;
}

bool hasColour(int colourId)
{
	double minNumberOfColouredPixels = 50;
	double numberOfColouredPixels = 0;
	for (int i = 0; i < camera_image.height; i++)
	{
		for (int j = 0; j < camera_image.width; j++)
		{
			if (pixelHasColour(colourId, get_camera_pixel(i, j)))
			{
				if (minNumberOfColouredPixels <= numberOfColouredPixels)
					return true;
				else
					numberOfColouredPixels++;
			}
		}
	}
	return false;
}

bool detectLine()
{
	bool isBlack = hasColour(3);
	return isBlack;
}

int rotate_left() {
	for (int i = 0; i < 13; i++) {
		turning_move(0, 25, 5, 1);
		update_sim(100);
	}
/*	while (offset_calc(false) > 10 || offset_calc(false) < -10) {
		turning_move(0, 25, 5, 1);
		update_sim(100);
	}*/
	turning_move(0, 0, 0, 1);
	return 0;
}
int rotate_right() {
	std::cout << "Vert Offset: " << offset_calc(false) << std::endl;
	for (int i = 0; i < 13; i++) {
		turning_move(0, -25, 5, 1);
		update_sim(100);
	}
/*	while (offset_calc(false) > 10 || offset_calc(false) < -10) {
		turning_move(0, -25, 5, 1);
		update_sim(100);
	}*/
	turning_move(0, 0, 0, 1);
	return 0;
}
int skip_turn() {
	for (int i = 0; i < 13; i++) {
		turning_move(0, 0, 5, 0);
		update_sim(100);
	}
	turning_move(0, 0, 0, 1);
	return 0;
}
int rotate_back() {
	for (int i = 0; i < 26; i++) {
		turning_move(0, 25, 0, 1);
		update_sim(100);
	}
	turning_move(0, 0, 0, 1);
	return 0;
}
int chal() {
	//bool isInter = false;
	int i = 0;
	int curError = 0;
	int turns = 0;
	while (offset_calc(true) > -51 || !hasColour(1)) {
		std::cout<<turns<<std::endl;
		if (turns == 7 && side_offset(false) > camera_image.height / 2 - 10) {
			std::cout<<"finish"<<std::endl;
			rotate_right();
			skip_turn();
		}
		else if (side_offset(true) > camera_image.height / 2 - 10 ) {
			turns++;
			std::cout<<"left"<<std::endl;
			rotate_left();
		}
		else if (offset_calc(false) > -51 && side_offset(false) > camera_image.height / 2 - 10 && side_offset(true) == -41 ) {
			std::cout<<"forward"<<std::endl;
			turns++;
			skip_turn();
		}
		else if (side_offset(false) > camera_image.height / 2 - 10 && side_offset(true) == -41) {
			std::cout<<"right"<<std::endl;
			turns++;
			rotate_right();
		}
		else if (offset_calc(true) == -51 && offset_calc(false) == -51) {
			std::cout<<"end"<<std::endl;
			if (offset_calc(true) == -51) {
				turns++;
				rotate_back();
			}
			
		}
		else {
			prevError = curError;
			curError = offset_calc(true);
			curError = (curError == -51) ? 0 : curError;
			if (true)
				turning_move(prevError, curError, 10, i);
			else
				turning_move(0, 0, -10, i);
			i++;
			update_sim(100);
		}
	}
	return 0;
}

int comp() {
	//bool isInter = false;
	int i = 0;
	int curError = 0;
	
	while (offset_calc(true) > -51 || !hasColour(2)) {
		if (side_offset(true) > camera_image.height / 2 - 10) {
			std::cout<<"left"<<std::endl;
			rotate_left();
		}
		else if (offset_calc(false) > -51 && side_offset(false) > camera_image.height / 2 - 10 && side_offset(true) == -51 ) {
			std::cout<<"forward"<<std::endl;
			skip_turn();
		}
		else if (side_offset(false) > camera_image.height / 2 - 10 && side_offset(true) == -51) {
			std::cout<<"right"<<std::endl;
			rotate_right();
		}
		else if (offset_calc(true) == -51 && offset_calc(false) == -51) {
			std::cout<<"end"<<std::endl;
			if (offset_calc(true) == -51) {
			
			rotate_back();
		}
			
		}
		else {
			prevError = curError;
			curError = offset_calc(true);
			curError = (curError == -51) ? 0 : curError;
			if (true)
				turning_move(prevError, curError, 5, i);
			else
				turning_move(0, 0, -10, i);
			i++;
			update_sim(100);
		}
	}
	while (offset_calc(true) < -camera_image.width / 2) {
		turning_move(0, 0, 10, 0);
		update_sim(100);
	}
	chal();
	return 0;
}

int core()
{

	int i = 0;
	int curError = 0;

	while (offset_calc(true) > -camera_image.width / 2 -1)
	{
		prevError = curError;
		curError = offset_calc(true);
		
		if (hasColour(3))
			turning_move(prevError, curError, 10, i);
		else
			turning_move(0, 0, -10, i);
		i++;
		std::cout<<(curError - prevError)<<std::endl;
		update_sim(100);
	}
	while (offset_calc(true) < -camera_image.width / 2) {
		turning_move(0, 0, 10, 0);
		update_sim(100);
	}
	comp();
	return 0;
}

int main()
{
	std::cout << "start simulation..." << std::endl;
	init(110,160,15*3.14159/180.0); // start of core
	// init(1880, 640, 90 * M_PI / 180.0); // start of completion

	core();

	return 0;
}
