#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "airports.h"
#include "seat.h"
#include "premium_seat.h"

using namespace std;

class database;

class flight {
private:
	unsigned int seatsPerRow;
	unsigned int numRows;
	unsigned int sourceID;
	unsigned int destID;
	vector<seat*> seats;
	string* name;
	string* surname;
	void remapSeat(unsigned int seatIndex, unsigned int* row, char* col);
public:
	flight(airports& Airports, unsigned int seatsPerRow, unsigned int numRows, unsigned int sourceID, unsigned int destID);
	~flight();
	void printFlightInfo(airports&);
	unsigned int getNrOfReservedSeats();
	unsigned int getNrOfFreeSeats();
	unsigned int getSize();
	unsigned int getRows();
	unsigned int getCols();
	unsigned int mapSeat(unsigned int row, char column);
	void reserveSeat(string name, string surname, unsigned int row, char column);
	bool isSeatReserved(unsigned int row, char column);
	bool isSeatReserved(unsigned int seatIndex);
	void releaseSeat(unsigned int row, char column);
	void printReservations();
	void printSeatMap();
};

