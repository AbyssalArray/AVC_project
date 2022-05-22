#include "images.h"

// movement globals - needs to be localised
int prevLeftVel = 0;
int prevRightVel = 0;
int forwardVel = 0;
const int MAX_VEL = 40;

// reverse engineered set_motor method, will calculate perfect speed
// to reach the target speed in 1 step, doesnt work for speeds above 24
// because that will go over the robots max speed and take more than 1 step
int get_vel(int tarVel, int prevVel)
{
	int vel = (tarVel - prevVel) / 0.6 + prevVel;
	std::cout << vel << "," << prevVel << std::endl;
	return vel;
}

// WARNING use only with target velocity below 24
int set_vel(int tarVel, int velD)
{
	tarVel = (tarVel - velD < -24) ? -24 + velD : tarVel;
	tarVel = (tarVel > 24 + velD) ? 24 - velD : tarVel;

	int velLeft = get_vel(tarVel - velD, prevLeftVel);
	prevLeftVel = (tarVel - velD);

	int velRight = get_vel(tarVel + velD, prevRightVel);
	prevRightVel = (tarVel + velD);

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

int turning_move(int error, int prevError, int f_vel, int step)
{

	// coefficients need tuning
	const double propGain = 1;
	const double derivGain = 1;
	// first step is just forward
	if (step == 0)
		set_vel(f_vel, 0);
	else
	{
		int velDiff = error * propGain + (error - prevError) * derivGain;
		set_vel(forwardVel, velDiff);
	}
	return 0;
}

bool hasColour(int colourId, ImagePPM camera)
{
	double maxNumberOfColouredPixels = 0;
	double numberOfColouredPixels = 0;
	for (int i = 0; i < camera.pixs.size(); i++)
	{
		if (pixelHasColour(colourId, camera.pixs[i]))
		{
			if (maxNumberOfColouredPixels >= numberOfColouredPixels)
			{
				return true;
			}
			else
			{
				numberOfColouredPixels++;
			}
		}
	}
	return false;
}

bool pixelHasColour(int colourId, Pixel pixel)
{
	double threshold = 1.5;	  // the amount by which the red, green or blue has to be above the other two
	double minimumColour = 5; // the strength of the colour (out of 255)
	double luminosity = (pixel.r + pixel.g + pixel.b) / 3.0;
	switch (colourId)
	{
	case 0: // red
		if (pixel.r > luminosity * threshold && pixel.r > minimumColour)
		{
			return true; // if pixel red is more than luminosity by some threshold and mainly red, pixel is red
		}
		break;
	case 1: // green
		if (pixel.g > luminosity * threshold && pixel.g > minimumColour)
		{
			return true; // if pixel green is more than luminosity by some threshold and mainly green, pixel is green
		}
		break;
	case 2: // blue
		if (pixel.b > luminosity * threshold && pixel.b > minimumColour)
		{
			return true; // if pixel blue is more than luminosity by some threshold and mainly blue, pixel is blue
		}
		break;
	}
	return false;
}

bool detectLine()
{
	bool isBlack = true;

	return isBlack;
}

int core()
{
	int i = 0;
	while (!hasColour(0, camera_image))
	{
		if (detectLine())
		{
			int[] error = readPixels();
			turning_move(error[0], error[1], 10, i);
			i++;
		}
		else
		{
			i = 0;
			turning_move(0, 0, -10, i);
		}
		update_sim(1500);
	}
	return 0;
}

int main()
{
	std::cout << "start simulation..." << std::endl;
	// init(1698,1018,90*3.14159/180.0); // start of completion
	// init(1880,640,90*3.14159/180.0);
	// init(110,160,15*3.14159/180.0); // start of core

	init(110, 160, 15 * 3.14159 / 180.0); // start of completion

	while (true)
	{
		turning_move(0, 0, 15, 0);
		update_sim(1500);
	}
	return 0;
}
