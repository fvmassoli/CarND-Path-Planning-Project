#ifndef VEHICLE_H
#define VEHICLE_H

#include <vector>

using namespace std;

class Vehicle {

private:

	int lane_width = 4.;
	double check_car_vx;
	double check_car_vy;
	double check_car_s;
	double check_car_d;
	double check_speed;
	
public:

	int current_lane_;
	double ref_vel_;
	/*
	 * Minimum space required between cars in order to allow any lane change
	 */
	double safety_space_ = 30.;
	double speed_limit_ = 49.5;	

	Vehicle();

	/**
	 * Destructor
	 */
	virtual ~Vehicle();

	int GetNextLane(vector<vector<double>> sensor_fusion, 
			int prev_size, 
			double end_path_s, 
			double car_s);

	void SetCurrentLane(int current_lane);

};


#endif /* VEHICLE_H */
