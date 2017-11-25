#include "vehicle.h"

Vehicle::Vehicle() { }

Vehicle::~Vehicle() { }

int Vehicle::GetNextLane(vector<vector<double>> sensor_fusion) {
	this->too_close_ = false;
/*	for(int i=0; i<this->sensor_fusion_.size(); i++) {
				// sensor fusion vector: [id, x, y, vx, vy, s, d]
				float d = sensor_fusion[i][6];
				if(d > (2+(4*lane)-2) && d < (2+(4*lane)+2)) {
					double vx = sensor_fusion[i][3];
					double vy = sensor_fusion[i][4];
					double check_speed = sqrt(vx*vx + vy*vy);
					double check_car_s = sensor_fusion[i][5];

					check_car_s += ((double)prev_size*.02*check_speed);
					
					if((check_car_s > car_s) && (check_car_s-car_s < 30)) {
						//ref_vel = 29.5;
						too_close = true;
						if(lane > 0) {
							lane = 0;
						}
					}
				}
			}*/

	return 0;
}
