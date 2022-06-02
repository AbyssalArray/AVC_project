#include "images.h"
#include <numeric> // std::inner_product
#include <vector>
#include <functional>

// movement globals - needs to be localised
int prevLeftVel = 0;
int prevRightVel = 0;
int forwardVel = 0;
const int MAX_VEL = 24;
int prevError = 0;
int minCol = 30;
int update_speed = 100;

const int OUT_SIDE = -camera_image.height / 2 - 1;
const int OUT_VERT = -camera_image.width / 2 - 1;
const bool LEFT = true;
const bool RIGHT = false;
const bool TOP = false;
const bool BOT = true;

const int SLOW_VEL = 5;
const int FAST_VEL = 10;
const int DETECT_RANGE = 10;
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
	velD = (tarVel - velD < -MAX_VEL) ? MAX_VEL - tarVel : velD;
	velD = (tarVel + velD > MAX_VEL) ? MAX_VEL - tarVel : velD;

	int velLeft = get_vel(tarVel + velD, prevLeftVel);
	prevLeftVel = (tarVel + velD);

	int velRight = get_vel(tarVel - velD, prevRightVel);
	prevRightVel = (tarVel - velD);

	forwardVel = tarVel;
	set_motors(velLeft, velRight);
	return 0;
}

bool pixelHasColour(int colourId, Pixel pixel)
{
	double threshold = 1.5; // the amount by which the red, green or blue has to be above the other two
	double luminosity = (pixel.r + pixel.g + pixel.b) / 3.0;
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
	off = (pixels > 0) ?  off/pixels : OUT_VERT;
	
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
	off = (pixels > 0) ?  off/pixels : OUT_SIDE;
	
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
		turning_move(0, 25, SLOW_VEL, 1);
		update_sim(update_speed);
	}
	turning_move(0, 0, 0, 1);
	return 0;
}
int rotate_right() {
	std::cout << "Vert Offset: " << offset_calc(false) << std::endl;
	for (int i = 0; i < 13; i++) {
		turning_move(0, -25, SLOW_VEL, 1);
		update_sim(update_speed);
	}
	turning_move(0, 0, 0, 1);
	return 0;
}
int skip_turn() {
	for (int i = 0; i < 13; i++) {
		turning_move(0, 0, SLOW_VEL, 0);
		update_sim(update_speed);
	}
	turning_move(0, 0, 0, 1);
	return 0;
}
int rotate_back() {
	for (int i = 0; i < 26; i++) {
		turning_move(0, 25, 0, 1);
		update_sim(update_speed);
	}
	turning_move(0, 0, 0, 1);
	return 0;
}
int chal() {
	//bool isInter = false;
	int i = 0;
	int curError = 0;
	int turns = 0;
	while (offset_calc(BOT) > OUT_VERT || !hasColour(1)) {
		// after robot turns 7 times break the left hand rule and turn right
		if (turns == 7 && side_offset(RIGHT) > camera_image.height / 2 - DETECT_RANGE) {
			std::cout<<"finish"<<std::endl;
			rotate_right();
			skip_turn();
		}
		else if (side_offset(LEFT) > camera_image.height / 2 - DETECT_RANGE ) {
			turns++;
			std::cout<<"left"<<std::endl;
			rotate_left();
		}
		else if (offset_calc(TOP) > OUT_VERT && side_offset(RIGHT) > camera_image.height / 2 - DETECT_RANGE && side_offset(LEFT) == OUT_SIDE ) {
			std::cout<<"forward"<<std::endl;
			turns++;
			skip_turn();
		}
		else if (side_offset(RIGHT) > camera_image.height / 2 - DETECT_RANGE && side_offset(LEFT) == OUT_SIDE) {
			std::cout<<"right"<<std::endl;
			turns++;
			rotate_right();
		}
		else if (offset_calc(BOT) == OUT_VERT && offset_calc(TOP) == OUT_VERT) {
			std::cout<<"end"<<std::endl;
			turns++;
			rotate_back();
		}
		else {
			prevError = curError;
			curError = (offset_calc(BOT) == OUT_VERT) ? 0 : offset_calc(BOT);
			turning_move(prevError, curError, FAST_VEL, i);
			i++;
			update_sim(update_speed);
		}
	}
	return 0;
}

int comp() {
	//bool isInter = false;
	int i = 0;
	int curError = 0;
	
	while (offset_calc(BOT) > OUT_VERT || !hasColour(2)) {
		if (side_offset(LEFT) > camera_image.height / 2 - DETECT_RANGE) {
			std::cout<<"left"<<std::endl;
			rotate_left();
		}
		else if (offset_calc(TOP) > OUT_VERT && side_offset(RIGHT) > camera_image.height / 2 - DETECT_RANGE && side_offset(LEFT) == OUT_SIDE) {
			std::cout<<"forward"<<std::endl;
			skip_turn();
		}
		else if (side_offset(RIGHT) > camera_image.height / 2 - DETECT_RANGE && side_offset(LEFT) == OUT_SIDE) {
			std::cout<<"right"<<std::endl;
			rotate_right();
		}
		else if (offset_calc(BOT) == OUT_VERT && offset_calc(TOP) == OUT_VERT) {
			std::cout<<"end"<<std::endl;
			rotate_back();
		}
		else {
			prevError = curError;
			curError = (offset_calc(BOT) == OUT_VERT) ? 0 : offset_calc(BOT);
			turning_move(prevError, curError, 8, i);
			i++;
			update_sim(update_speed);
		}
	}
	// after robot reaches the blue marker, keep going forward untill it sees the line again
	while (offset_calc(BOT) < -camera_image.width / 2) {
		turning_move(0, 0, FAST_VEL, 0);
		update_sim(update_speed);
	}
	chal();
	return 0;
}

int core()
{

	int i = 0;
	int curError = 0;

	while (offset_calc(BOT) > OUT_VERT || !hasColour(0))
	{
		prevError = curError;
		curError = offset_calc(BOT);
		
		if (hasColour(3))
			turning_move(prevError, curError, FAST_VEL, i);
		else
			turning_move(0, 0, -FAST_VEL, i);
		i++;
		update_sim(update_speed);
	}
	// after robot reaches the red marker, keep going forward untill it sees the line again
	while (offset_calc(BOT) == OUT_VERT) {
		turning_move(0, 0, FAST_VEL, 0);
		update_sim(update_speed);
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
