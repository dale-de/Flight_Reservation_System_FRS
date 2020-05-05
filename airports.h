#pragma once
using namespace std;
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include "airport.h"
class airports sealed
{
public:
	airports();
	vector<airport> LoC;
	 static airports& buildAirports() {
		static airports Airports;
		return Airports;
	}
	void printAirports();
	bool isIDvalid(unsigned int IDCheck);
	string getAirportByID(unsigned int ID);
};

