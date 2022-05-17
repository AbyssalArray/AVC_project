
#include "images.h" 
int prevLeftVel = 0;
int prevRightVel = 0;
int forwardVel = 0;
const int MAX_VEL = 40;

// reverse engineered set_motor method, will calculate perfect speed
// to reach the target speed in 1 step, doesnt work for speeds above 24
// because that will go over the robots max speed and take more than 1 step
int get_vel(int tarVel, int prevVel) {
	int vel = (tarVel - prevVel) / 0.6 + prevVel;
	return vel;
}

// WARNING use only with target velocity below 24
int set_vel(int tarVel, int velD){
	tarVel = (tarVel - velD < -24) ? -24 + velD : tarVel;
	tarVel = (tarVel > 24 + velD) ? 24 - velD: tarVel;
	
	int velLeft = get_vel(tarVel - velD, prevLeftVel);
	prevLeftVel += velLeft;
	
	int velRight = get_vel(tarVel + velD, prevRightVel);
	prevRightVel += velRight;
	
	forwardVel = tarVel;
	set_motors(velLeft,velRight);
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

int turning_move(int error,int prevError, int f_vel, int step) {
	// coefficients need tuning
	const double propGain = 1;
	const double derivGain = 1;
	// first step is just forward
	if (step == 0) set_vel(20, 0);
	else {
		int velDiff = error * propGain + (error - prevError) * derivGain;
		set_vel(forwardVel, velDiff);
	}
	return 0;
} 
int core() {
	return 0;
}
int main()
{        
	std::cout<<"start simulation..."<<std::endl;
	//init(1698,1018,90*3.14159/180.0); // start of completion
	//init(1880,640,90*3.14159/180.0);
	//init(110,160,15*3.14159/180.0); // start of core
	
	init(110,160,15*3.14159/180.0); // start of completion
	
	while(true){
	  set_motors(2,2);
      update_sim(300);
  }
    return 0;
}

