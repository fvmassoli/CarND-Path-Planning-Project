#ifndef VEHICLE_H
#define VEHICLE_H

#include <vector>

using namespace std;

class Vehicle {

	public:
		bool too_close_;

	Vehicle();

	/**
	 * Destructor
	 */
	virtual ~Vehicle();

	int GetNextLane(vector<vector<double>> sensor_fusion);
	
};


#endif /* VEHICLE_H */
