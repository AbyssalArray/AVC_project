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
	std::vector<int> index_array; // indexing array from -50 to 49 for inner product calculation
	std::vector<int> range_array; // array for range of pixels
	std::vector<int> bW_array;	  // array for black and white pixels
	int init = 0;				  // additonal number for inner product

	for (int i = 0; i < camera_image.width; i++)
	{
		int r, g, b = 0;
		r = (int)get_camera_pixel(50, i, 0);
		g = (int)get_camera_pixel(50, i, 1);
		b = (int)get_camera_pixel(50, i, 2);
		int rgbv = (r + g + b) / 3;
		if (rgbv < 30)
		{
			bW_array.push_back(1); // black
		}
		else if (rgbv >= 30)
		{
			bW_array.push_back(0); // white
		}
		// std::cout<<bW_array.at(i)<<std::endl;
	}

	for (int i = 0; i < camera_image.width; i++)
	{
		range_array.push_back(i);
		// std::cout<<range_array.at(i)<<std::endl;
	}

	for (int i = 0; i < camera_image.width; i++)
	{

		int mPosition = camera_image.width / 2;
		index_array.push_back(i - mPosition);
		// std::cout<<index_array.at(i)<<std::endl;
	}

	int offset_calc = std::inner_product(index_array.begin(), index_array.end(), bW_array.begin(), init);
	std::cout << "error: "<<offset_calc << std::endl;
	bW_array.clear();
	range_array.clear();
	index_array.clear();

	// return offset calc;
	return offset_calc;
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
	
	double threshold = 1.5;	  // the amount by which the red, green or blue has to be above the other two
	double minCol = 5; // the strength of the colour (out of 255)
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
			return true; // if pixel blue is more than luminosity by some threshold and mainly blue, pixel is blue
		break;
	}
	return false;
}

bool hasColour(int colourId, ImagePPM camera)
{
	double maxNumberOfColouredPixels = 0;
	double numberOfColouredPixels = 0;
	//potential issue in for loop
	for (int i = 0; i < (int)camera.pixs.size(); i++)
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

bool detectLine()
{
	bool isBlack = hasColour(3,camera_image);
	
	return isBlack;
}

int core()
{
	
	int i = 1;
	int curError = 0;
	
	while (!hasColour(0, camera_image))
	{	
		if (i >= 0)
		{
			std::cout<<"forwrads"<<std::endl;
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
	// init(1698,1018,90*3.14159/180.0); // start of completion
	// init(1880,640,90*3.14159/180.0);
	// init(110,160,15*3.14159/180.0); // start of core

	init(110, 160, 0 * 3.14159 / 180.0); // start of completion

		/*offset_calc();
		turning_move(0, 0, 15, 0);
		update_sim(1500);*/
		core();
	
	return 0;
}
