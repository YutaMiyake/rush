/**
@file   vehicle.cpp 
@author   Yuta Miyake
@date     11/24/2014
@brief   the implementation of vehicle ADT
*/

#include "vehicle.h"
/**
*construct a vehicle
*
*This does nothing basically except for creating a empty vehicle object.
*
*@param none
*@pre none
*@post empty vehicle is created
*@exception none
*@note none
*@return none
*
*/
vehicle::vehicle()
{ 
	   // none
}
/**
*construct a vehicle with parameters
*
*This initialized the member data with parameters
*
*@param type [int]
*@param direction [char]
*@param row [int]
*@param col [int]
*@pre none
*@post vehicle with four properties are constructed
*@exception none
*@note none
*@return none
*
*/
vehicle::vehicle(int t, char d, int r, int c)
{
		type = t;
		dir = d;
		row =r;
		col = c;
}
/**
* Based on the direction, moves the vehicle's position forward 
*
*@param none
*@pre vehicle is correctly created
*@post the position is incremented toward the car's direction
*@exception none
*@note none
*@return none
*
*/
vehicle& vehicle::operator++()
{
		if(dir == 'H')
			col++;
		else
			row++;

		return *this;
}
/**
* Based on the direction, moves the vehicle's position backward 
*
*@param none
*@pre vehicle is correctly created
*@post the position is incremented toward the car's direction
*@exception none
*@note none
*@return none
*
*/
vehicle& vehicle::operator--()
{
		if(dir == 'H')
			col--;
		else
			row--;

		return *this;
}