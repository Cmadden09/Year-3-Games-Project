/*=============================================================================
* System.h
* Author: Adam Stanton
* Abstract parent to our system classes...
=============================================================================*/

#pragma once
#include <string>

class System
{
public:

	System() {};
	virtual ~System() {};

	virtual void init() = 0;

};