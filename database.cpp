#include "database.h"
#include <vector>
#include "database.h"
#include "flight.h"
#include <algorithm>

database::database() {
	nextID = 12300;
}
unsigned int database::assignID() {
	nextID += 10;
	return nextID;
}
unsigned int database::addFlightToDataBase(flight* newFlight) {
	flights.push_back(newFlight);
	unsigned int newID = assignID();
	IDs.push_back(newID);
	return newID;
}
database::~database() {
	for (unsigned int i = 0; i < flights.size(); i++) {
		if (flights.at(i) != NULL) {
			delete flights.at(i);
		}
	}
}
void database::listFlights(airports& Airports) {
	if (flights.size() == 0) {
		cout << "Currently no flights in system." << endl;
	}
	for (unsigned int i = 0; i < flights.size(); i++) {
		cout << "Flight ID " << IDs.at(i) << " ";
		flights.at(i)->printFlightInfo(Airports);
	}

	cout << endl << endl << endl;
}
void database::deleteFlightByID(unsigned int ID) {
	std::vector<int>::iterator it = std::find(IDs.begin(), IDs.end(), ID);
	if (it == IDs.end()) {
		cout << "No flight existing with given ID!" << endl;
	}
	else {
		int index = std::distance(IDs.begin(), it);
		cout << "Deleting flight with ID " << ID << endl;
		delete flights.at(index);
		flights.erase(flights.begin() + index);
		IDs.erase(it);
	}
	cout << endl << endl << endl;
}
bool database::isIDvalid(unsigned int ID) {
	std::vector<int>::iterator it = std::find(IDs.begin(), IDs.end(), ID);
	if (it == IDs.end()) {
		cout << "No flight existing with given ID!" << endl << endl << endl;
		return false;
	}
	return true;
}
unsigned int database::getPositionInVectorByID(unsigned int ID) {
	std::vector<int>::iterator it = std::find(IDs.begin(), IDs.end(), ID);
	if (it == IDs.end()) {
		cout << "No flight existing with given ID!" << endl << endl << endl;
		return false;
	}
	unsigned int index = std::distance(IDs.begin(), it);
	return index;

}
void database::reserveFlight(unsigned int ID, string name, string surname, unsigned int row, char column) {
	try {
		unsigned int index = getPositionInVectorByID(ID);
		flights.at(index)->reserveSeat(name, surname, row, column);
		cout << "Fulfilled reservation for " << surname << " " << name << " for flight " << ID << endl;
	}
	catch (int e) {
		throw e;
	}
}

void database::printFlightByID(airports& Airports, unsigned int ID) {
	try {
		unsigned int index = getPositionInVectorByID(ID);
		cout << "Flight ID " << IDs.at(index) << " ";
		flights.at(index)->printFlightInfo(Airports);
	}
	catch (int e) {
		throw e;
	}
}

void database::releaseSeat(unsigned int ID, unsigned int row, char col) {
	try {
		unsigned int index = getPositionInVectorByID(ID);
		flights.at(index)->releaseSeat(row, col);
	}
	catch (int e) {
		throw e;
	}
}
void database::printReservations(unsigned int ID) {
	try {
		unsigned int index = getPositionInVectorByID(ID);
		flights.at(index)->printReservations();
	}
	catch (int e) {
		throw e;
	}

}
void database::printSeatMap(unsigned int ID) {
	unsigned int index = getPositionInVectorByID(ID);
	flights.at(index)->printSeatMap();
}
