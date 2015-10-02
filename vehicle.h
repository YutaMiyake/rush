/**
@file vehicle.h
@author Yuta Miyake
@brief The class declaration for the vehicle ADT
@date Sep. 25 2014
*/

#ifndef VEHICLE_H
#define VEHICLE_H

struct vehicle
{
	int type;
	char dir;
	int row;
	int col;

	vehicle();
	vehicle(int t, char d, int r, int c);
	vehicle& operator++();
	vehicle& operator--();
};

#endif