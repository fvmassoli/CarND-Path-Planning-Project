#include "vehicle.h"
#include <cmath>

Vehicle::Vehicle() { 
	this->ref_vel_ = 0.0;
	this->current_lane_ = 1;
}

Vehicle::~Vehicle() { }

void Vehicle::SetCurrentLane(int current_lane) {
	this->current_lane_ = current_lane;
}

int Vehicle::GetNextLane(vector<vector<double>> sensor_fusion, 
						 int prev_size, 
						 double end_path_s, 
						 double car_s) {
	
	int observed_car_lane = -1;
	bool can_move_left = true;
	bool can_move_right = true;
	bool car_ahead = false;
		
	/*
     * check if we are in leftmost or rightmost lane
	 */
	if(current_lane_ == 0) {
		can_move_left = false;
	} else if(current_lane_ == 2) {
		can_move_right = false;
	}
	
	/*
    	 * loop through all the surrounding cars
	 */
	for(int i=0; i<sensor_fusion.size(); i++) {
	
		// sensor fusion vector: [id, x, y, vx, vy, s, d]
		check_car_vx = sensor_fusion[i][3];
		check_car_vy = sensor_fusion[i][4];
		check_car_s  = sensor_fusion[i][5];
		check_car_d  = sensor_fusion[i][6];
		
		/*
		 * set the observed car lane to an integer within [0, 2]		
		 */
		if(check_car_d >= 0. && check_car_d < lane_width) {
			observed_car_lane = 0;
		} else if(check_car_d >= lane_width && check_car_d < (2*lane_width)) {
			observed_car_lane = 1;
		} else if(check_car_d >= (2*lane_width) && check_car_d <= (3*lane_width)) {
			observed_car_lane = 2;
		}
		if(observed_car_lane == -1) {
			continue;
		}
	
		check_speed = sqrt(check_car_vx*check_car_vx + check_car_vy*check_car_vy);
		check_car_s += ((double)prev_size*.02*check_speed);

		/*
    		 * recognize where are the cars around us
		 */
		if(observed_car_lane == current_lane_ && check_car_s > car_s && check_car_s - car_s < safety_space_) { 
			car_ahead = true;
		} else if(car_s-safety_space_ < check_car_s && car_s+safety_space_ > check_car_s) {
			if(observed_car_lane < current_lane_) {
				can_move_left = false;
			} else if(observed_car_lane > current_lane_) {
				can_move_right = false;
			}
		}
		
	}

	/*
  	 * if there is a car in our lane try to change lane. 
	 * If it is not possible then slow down
	 */
	if(car_ahead) {
		if(can_move_left) {
			current_lane_--;
		} else if(can_move_right) {
			current_lane_++;
		} else {
			ref_vel_ -= 0.224;
		}
	} else {
	/*
  	 * Try to get back into the center lane if possible and/or accelerate
	 */
		if ( current_lane_ != 1 ) {
			if ( ( current_lane_ == 0 && can_move_right ) || ( current_lane_ == 2 && can_move_left ) ) {
				current_lane_ = 1;
			}
		}
		if ( ref_vel_ < speed_limit_ ) {
			ref_vel_ += 0.224;
        }
	}
		
	return current_lane_;		
}

