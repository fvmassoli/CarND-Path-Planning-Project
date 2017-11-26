#include "vehicle.h"
#include <cmath>

Vehicle::Vehicle() { 

	this->ref_vel_ = 0.0;

}

Vehicle::~Vehicle() { }

void Vehicle::SetCurrentLane(int current_lane) {
	this->current_lane_ = current_lane;
}

int Vehicle::GetNextLane(vector<vector<double>> sensor_fusion, 
						int prev_size, 
						double end_path_s, 
						double car_s) {

	bool can_move_left = true;
	bool can_move_right = true;
	int already_leftmost_lane = 0;
	int already_rightmost_lane = 2;
	int lane_width = 4;
	int current_lane = this->current_lane_;
	int next_lane = current_lane;
	int space_on_left = 1000.0;
	int space_on_right = 1000.0;
	double check_speed;
	double car_dist;
	double space;

	this->too_close_ = false;

	// check if car is in the center or one of the outermost lanes
	if(current_lane == already_leftmost_lane) {
		can_move_left = false;
	} else if(current_lane == already_rightmost_lane) {
		can_move_right = false;
	}

	// loop through all the cars in the sensor fusion vector
	for(int i=0; i<sensor_fusion.size(); i++) {
		
		// sensor fusion vector: [id, x, y, vx, vy, s, d]
		double check_car_vx = sensor_fusion[i][3];
		double check_car_vy = sensor_fusion[i][4];
		double check_car_s  = sensor_fusion[i][5];
		double check_car_d  = sensor_fusion[i][6];
		
		check_speed = sqrt(check_car_vx*check_car_vx + check_car_vy*check_car_vy);
		check_car_s += ((double)prev_size*.02*check_speed);

		// the distance in the future
		space = check_car_s - end_path_s;

		// current distance
		car_dist = check_car_s - car_s;

		// check the distance with the observed car that is in fron of us
		if(car_dist > 0 && car_dist < this->safety_space_) {
			
			if(check_car_d == current_lane + 1) {
				if(space < space_on_left) {
					space_on_left = space;
				}
				can_move_left = false;
			}

			if(check_car_d == current_lane + 1) {
				if(space < space_on_right) {
					space_on_right = space;
				}
				can_move_right = false;
			}

		}

		// check the distance with the observed car that is behind of us
		if(car_dist < 0 && car_dist > -30) {
			
			if(check_car_d == current_lane + 1) {
				can_move_left = false;
			}

			if(check_car_d == current_lane + 1) {
				can_move_right = false;
			}

		}

		// check if there is a car in front of me
		if(check_car_d > (2+(4*current_lane)-2) && check_car_d < (2+(4*current_lane))+2) {

			// check if we are too close to the car in front of us
			if((check_car_s > car_s) && (car_dist < this->safety_space_)) {
				this->too_close_ = true;
			}

		}

	} // end loop on sensor fusion vector

	cout << "this->too_close_ " << this->too_close_ << endl;

	if(this->too_close_) {

		if(current_lane == already_leftmost_lane && can_move_right)
		{

			next_lane = current_lane + 1;
		
		} else if (current_lane == already_rightmost_lane && can_move_left) 
		{
		
			next_lane = current_lane - 1;
		
		} else 
		{

			if(can_move_left) {
				next_lane = current_lane - 1;	
			} else if (can_move_right) {
				next_lane = current_lane + 1;
			} 

		}

	}

	this->current_lane_ = next_lane;
	return next_lane;
}

/*double Vehicle::GetRefVel() {

	

	// deceleration of 5 m/s2
	if(this->too_close_)
	{
		this->ref_vel_ -= .224; 
	} else if(this->ref_vel_ < this->speed_limit_) {
		this->ref_vel_ += .224; 
	}

	return this->ref_vel_;

}*/

