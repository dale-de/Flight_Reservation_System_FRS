#include <iostream>
#include "flight.h"
#include "airports.h"
#include "database.h"
#include <ctype.h>
using namespace std;

unsigned int readInput() {
	unsigned int tmp;
	while (!(cin >> tmp)) {
		cout << "Please enter numerical!";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return tmp;
}

int main() {
	airports& Airports = airports::buildAirports();
	database& Database = database::buildDatabase();
	// Example Flights
	flight* newFlight;
	unsigned int ID;
	newFlight = new flight(Airports, 4, 20,
		1, 4);
	Database.addFlightToDataBase(newFlight);
	newFlight = new flight(Airports, 7, 20,
		0, 7);
	ID = Database.addFlightToDataBase(newFlight);
	try
	{
		Database.reserveFlight(ID, "Maco", "Kulla", 4,
			'A');
		Database.reserveFlight(ID, "Robin", "Weyand", 7,
			'B');
		Database.reserveFlight(ID, "David", "Lehr", 2,
			'B');
		Database.reserveFlight(ID, "Matthias", "Lehr", 1,
			'A');
		Database.printSeatMap(ID);
	}
	catch (int e)
	{
		cout << e;
	}
	

	cout << "Welcome to flight reservation system FRS." << endl;
	Airports.printAirports();
	bool running = true;
	do {
		try {
			cout << endl << "Please enter what to do:" << endl;
			cout << "A: List all flights registered in system." << endl;
			cout << "B: Add a new flight." << endl;
			cout << "C: Change reserverations for flight identified by ID."
				<< endl;
			cout
				<< "D: Print informations about reservations and seat map for flight identified by ID."
				<< endl;
			cout << "E: Delete a flight from the system." << endl;
			cout << "F: List airports." << endl;
			cout << "G: Quit system." << endl;
			char selection;
			unsigned int ID;
			unsigned int newSource;
			unsigned int newDest;
			unsigned int newSeatsPerRow;
			unsigned int newRows;
			string newName;
			string newSurname;
			unsigned int resRow;
			char resSeat;
			cin >> selection;
			selection = toupper(selection);
			flight* newFlight;
			switch (selection) {
			case 'A':
				cout << "Listing Flights in System:" << endl;
				Database.listFlights(Airports);
				break;
			case 'B':
				cout << "Adding a new flight to the system." << endl;
				cout << "Please enter ID of source Airport." << endl;
				Airports.printAirports();
				newSource = readInput();
				cout << "Please enter ID of destination Airport." << endl;
				newDest = readInput();
				cout << "Please enter the number of rows in your plane."
					<< endl;
				newRows = readInput();
				cout
					<< "Please enter the number of seats per row in your plane."
					<< endl;
				newSeatsPerRow = readInput();
				newFlight = new flight(Airports, newSeatsPerRow, newRows,
					newSource, newDest);
				ID = Database.addFlightToDataBase(newFlight);
				cout << "Created flight with ID " << ID << " ";
				newFlight->printFlightInfo(Airports);

				break;
			case 'C':
				cout
					<< "Please enter ID of flight for which to change reservations."
					<< endl;
				ID = readInput();
				if (Database.isIDvalid(ID)) {
					Database.printFlightByID(Airports, ID);
					cout << "Please choose what to do." << endl;
					cout << "A: Make reservation" << endl;
					cout << "B: Delete Reservation" << endl;
					cin >> selection;
					selection = toupper(selection);
					switch (selection) {
					case 'A':
						cout << "Please enter last name of passenger." << endl;
						cin >> newName;
						cout << "Please enter surname of passenger." << endl;
						cin >> newSurname;
						cout << "Reservation for which row?" << endl;
						resRow = readInput();
						cout << "Reservation for which seat in row? (A, B, ...)"
							<< endl;
						cin >> resSeat;
						Database.reserveFlight(ID, newName, newSurname, resRow,
							resSeat);
						break;
					case 'B':
						cout << "Row of seat to be released?" << endl;
						resRow = readInput();
						cout << "Which seat in row " << resRow
							<< " (A, B, ...) to be released?" << endl;
						cin >> resSeat;
						Database.releaseSeat(ID, resRow, resSeat);
						break;
					}
				}
				break;
			case 'D':
				cout
					<< "Please enter ID of flight for which to change reservations."
					<< endl;
				ID = readInput();
				if (Database.isIDvalid(ID)) {
					Database.printFlightByID(Airports, ID);
					cout << "Please choose what to do." << endl;
					cout << "A: Print all reservations for flight " << ID << endl;
					cout << "B: Print seat map for flight " << ID << endl;
					cin >> selection;
					selection = toupper(selection);
					switch (selection) {
					case 'A':
						Database.printReservations(ID);
						break;
					case 'B':
						Database.printSeatMap(ID);
						break;
					}
				}
				break;
			case 'E':
				cout << "Please enter ID of flight to delete" << endl;
				ID = readInput();
				Database.deleteFlightByID(ID);
				break;

			case 'F':
				Airports.printAirports();
				break;
			case 'G':
				running = false;
				cout
					<< "Now leaving the TH AB flight reservation system. Good bye."
					<< endl;

			}
		}
		catch (int e) {
			switch (e) {
			case 0:
				cerr << "Current flight cannot be created due to an error."
					<< endl;
				cerr << "Invalid number of seats for flight!" << endl;
				break;
			case 1:
				cerr << "Current flight cannot be created due to an error."
					<< endl;
				cerr << "Invalid source airport!" << endl;
				break;
			case 2:
				cerr << "Current flight cannot be created due to an error."
					<< endl;
				cerr << "Invalid destination airport!" << endl;
				break;
			case 3:
				cerr << "Current flight cannot be created due to an error."
					<< endl;
				cerr << "Same source and destination airport!" << endl;
				break;
			case 10:
				cerr << "Invalid Seat given!" << endl;
				break;
			case 11:
				cerr << "Cannot reserve seat. Plane fully booked!" << endl;
				break;
			case 13:
				cerr << "No reservation found for given seat!" << endl;
				break;
			default:
				cerr << "Undefined Error." << endl;
			}

		}
	} while (running == 1);
	return 0;
}
