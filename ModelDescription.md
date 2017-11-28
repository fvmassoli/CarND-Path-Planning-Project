# Project Introduction

The goal of the project is to implement a trajectory planner ables to plan drivable trajectories while respecting some restrictions as max jerk, max speed, etc...

The project is divided into three main files: main.cpp, vehicle.cpp, vehicle.h.

The two files pid.cpp and pid.h are not currently used into the project. The idea was to use PID to control the speed of the car.

## Vehicle class

The Vehicle class is in charge of choosing the next lane that the car should take. The main method of the class is the ```
 Vehicle::GetNextLane() ```. 
 
 In that method I first check if the car is in one of the outermost lanes (liens 28-32).  
 
 At the line 37 I start to loop over all the vehicles around the car in order to understand their location with respect to my car. Given an observed car, at line 60 I project its position at the end of the current trajectory and then if the observed car is in my car lane and in front of it I set to true the variable ```car_ahead``` otherwise I check if the observed car is in the left or right lane and within 30 meters from my car. If the observed car is in a different lane and its distance from us is less then 30 meters (that I defined as safety distance) then my car won't go in that specific lane. Otherwise the lane change is allowed.
 
 From line 81 to 101 the vehicle decided what to do. If there is an observed car in front us and there is a lane available, my car will change lane. If there are not lane availbale then the car will slow down (line 87). 
 
 If the car is not in the center lane it will try go back in the center lane as soon as possible and if there are not observed cars in the car lane it starts to speed up.
 
## main file

In the main file I create the trajectory by interpolating next positions points using a spline. 

Given a set of reference points and a target number of specific points, the spline can be used to interpolate among that points in order to obtain a smooth and drivible trajectory. 

The trajectory is evaluated from line 362 to 384. As we can see the algorithm does not create a totally new trajectory every time but add points (if any) to the previous one in order to:

1) avoid too fast trajectory changes
2) have a total of 50 points in each generated trajectory

