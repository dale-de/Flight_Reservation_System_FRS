#pragma once
#include <vector>
#include "flight.h"
#include <algorithm>

class database final {
private:
	vector<flight*> flights;	//list of flights in the system (pushback/realloc)
	vector<int> IDs;
	unsigned int nextID;		//the next unique ID given for the flight (what in case of overflow?)
	database();
	database(const database&);
	database& operator= (const database&);
public:
	static database& buildDatabase() {
		static database Database;
		return Database;
	}
	unsigned int assignID();
	unsigned int addFlightToDataBase(flight*);
	~database();
	void listFlights(airports&);
	void deleteFlightByID(unsigned int ID);
	bool isIDvalid(unsigned int ID);
	unsigned int getPositionInVectorByID(unsigned int ID);
	void reserveFlight(unsigned int ID, string name, string surname, unsigned int row, char column);
	void printFlightByID(airports& Airports, unsigned int ID);
	void releaseSeat(unsigned int ID, unsigned int row, char col);
	void printReservations(unsigned int ID);
	void printSeatMap(unsigned int ID);
};

