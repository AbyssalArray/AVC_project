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
	std::cout << "velocity, prev velocity :"<<vel << "," << prevVel << std::endl;
	return vel;
}

// WARNING use only with target velocity below 24
int set_vel(int tarVel, int velD)
{
	velD = (tarVel - velD < -24) ? 12  : velD;
	velD = (tarVel + velD> 24 ) ? 12  : velD;
	
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
int offset_calc()
{
	std::vector<int> bW_array; // array for black and white pixels
	int offset = 0;
	for (int i = 0; i < camera_image.width; i++)
	{
		int r, g, b = 0;
		bW_array.push_back(0); // white
		// std::cout<<bW_array.at(i)<<std::endl;
		// int mPosition = camera_image.width / 2;
		// index_array.push_back(i - mPosition);
	}
	for (int i = 0; i < camera_image.width; i++)
	{
		if (bW_array[i] == 1)
		{
			offset = i - 50;
		}
	}
	bW_array.clear();
	std::cout << offset << std::endl;
	return offset;
}

int turning_move(int error, int prevError, int f_vel, int step)
{

	// coefficients need tuning
	const double propGain = 0.01;
	const double derivGain = 0.005;
	// first step is just forward
	if (step == 0)
		set_vel(f_vel, 0);
	else
	{
		int velDiff = error * propGain + (error - prevError) * derivGain;
		std::cout<<"vel diff: "<<velDiff<<std::endl;
		set_vel(f_vel, velDiff);
	}
	return 0;
}

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

bool hasColour(int colourId)
{
	double minColPixels = 20;
	double numColPixels = 0;
	if (colourId == 0)
		std::cout << "New image" << std::endl;

	for (int row = 0; row < camera_image.height; row++)
	{
		for (int column = 0; column < camera_image.width; column++)
		{
			if (pixelHasColour(colourId, get_camera_pixel(row, column)))
			{
				if (minColPixels <= numColPixels)
					return true;
				else
					numColPixels++;
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

int core()
{
	
	int i = 1;
	int curError = 0;
	
	while (!hasColour(0))
	{	
		if (i >= 0)
		{
			std::cout<<"forwards"<<std::endl;
			curError = offset_calc();
			turning_move(prevError, curError, 10, i);
			prevError = curError;
			i++;
		}
		else
		{
			i = 0;
			curError = offset_calc();
			turning_move(0, 0, -10, i);
			prevError = curError;
			i++;
		}
		update_sim(1500);
	}
	return 0;
}

int main()
{
	std::cout << "start simulation..." << std::endl;
	init(110, 160, 0 * M_PI / 180.0); // start of core
	// init(1880, 640, 90 * M_PI / 180.0); // start of completion

	core();
	
	return 0;
}
