
#include "images.h" 
int prevVel = 0;
const int MAX_VEL = 40;

int linear_move(int tarVel){
	int vel = (tarVel - prevVel) / 0.6 + prevVel;
	while (vel > MAX_VEL || vel < -MAX_VEL) {
		if (vel > 0) set_motors(MAX_VEL,MAX_VEL);
		else set_motors(-MAX_VEL,-MAX_VEL);
		prevVel += vel;
		vel = (tarVel - prevVel) / 0.6 + prevVel;
	}
	set_motors(vel,vel);
	return 0;
}

int turning_move(int error[], int f_vel, int step) {
	if (step == 0) linear_move(20);
	else {
		
	}
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

