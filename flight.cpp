#include <string.h>
#include <iostream>
#include <iomanip>
#include "flight.h"

using namespace std;

flight::flight(airports& Airports, unsigned int seatsPerRow,
	unsigned int numRows, unsigned int sourceID, unsigned int destID) {
	try {
		this->seatsPerRow = seatsPerRow;
		this->numRows = numRows;
		this->sourceID = sourceID;
		this->destID = destID;
		if (!Airports.isIDvalid(this->sourceID)) {
			throw 1;
		}
		if (!Airports.isIDvalid(this->destID)) {
			throw 2;
		}
		if (this->sourceID == this->destID) {
			throw 3;
		}
		if (seatsPerRow * numRows > 400) {
			throw 0;
		}
		for (int i = 0; i < seatsPerRow * (numRows / 5); i++)
		{
			premium_seat* s = new premium_seat();
			if ((i - (i / seatsPerRow * seatsPerRow)) % 2 != 0)
				s->reserved = true;
			this->seats.push_back(s);
		}
		for (int i = seatsPerRow * (numRows / 5); i < seatsPerRow * numRows; i++) {
			seat* s = new seat();
			this->seats.push_back(s);
		}
	}
	catch (int e) {
		throw e;
	}
}

flight::~flight() {
	seats.clear();
}

void flight::printFlightInfo(airports& Airports) {
	unsigned int seatsReserved = getNrOfReservedSeats();
	string source = Airports.getAirportByID(sourceID);
	string dest = Airports.getAirportByID(destID);
	cout << "from " << source << " to " << dest << " with "
		<< seatsPerRow * numRows << " seats (" << getRows() << " rows, "
		<< getCols() << " columns) of which " << seatsReserved
		<< " are reserved." << endl;
}

unsigned int flight::getSize() {
	return this->seatsPerRow * this->numRows;
}

unsigned int flight::getCols() {
	return this->seatsPerRow;
}

unsigned int flight::getRows() {
	return this->numRows;
}

unsigned int flight::mapSeat(unsigned int row, char column) {
	try {
		char tmpChar = toupper(column);
		unsigned int colNr = tmpChar - 65;
		if (colNr >= seatsPerRow || row > numRows) {
			throw 10;
		}
		int index = (row - 1) * this->getCols() + colNr;
		if (index >= getSize()) {
			throw 10;
		}
		else {
			return index;
		};
	}
	catch (int e) {
		throw e;
	}
}

bool flight::isSeatReserved(unsigned int row, char column) {
	try {
		int seatIndex = this->mapSeat(row, column);
		return this->isSeatReserved(seatIndex);
	}
	catch (int e) {
		throw e;
	}
}

bool flight::isSeatReserved(unsigned int seatIndex) {
	try {
		if (seatIndex >= getSize()) {
			throw 10;
		}
		return seats[seatIndex]->reserved;
	}
	catch (int e) {
		throw e;
	}
}

void flight::reserveSeat(string name, string surname, unsigned int row,
	char column) {
	try {
		int seatIndex = this->mapSeat(row, column);
		int not_valid=0;
		if (seatIndex < (numRows / 5 * seatsPerRow)) {
			char tmpChar = toupper(column);
			unsigned int colNr = tmpChar - 65;
			if (seatsPerRow % 2 == 0  && colNr %2 !=0) {
					not_valid = 1;
			}
		}
		if (not_valid == 1) {
			cout << "Seat (" << row << ", " << column
				<<"index" << seatIndex << ") is not avaiable it is just for overbooked flights! Searching for alternative!"
				<< std::endl;
			goto next;
		}
		if (isSeatReserved(seatIndex) == true) {
			cout << "Seat (" << row << ", " << column
				<< ") is already reserved! Searching for alternative in same class!"
				<< std::endl;
		next:
			unsigned int nextFreeSeat = 0;
			if (seatIndex > (numRows / 5 * seatsPerRow))
				nextFreeSeat = (numRows / 5 * seatsPerRow);
			while (nextFreeSeat < getSize() && isSeatReserved(nextFreeSeat)) {
				nextFreeSeat++;
			}
			if (nextFreeSeat == getSize()) {
				throw 11;
			}
			if (seats[seatIndex]->type_bool() && nextFreeSeat > (numRows / 5 * seatsPerRow))
				cout << "downgrading to classic seat.";
			seatIndex = nextFreeSeat;
			
		}
		seats[seatIndex]->reserved = true;
		seats[seatIndex]->name = name;
		seats[seatIndex]->surname = surname;
	}
	catch (int e) {
		throw e;
	}
}

void flight::releaseSeat(unsigned int row, char column) {
	try {
		if (!isSeatReserved(row, column)) {
			throw 13;
		}
		unsigned int seatIndex = mapSeat(row, column);
		cout << "Seat (" << row << ", " << column
			<< ") (originally reserved for " << this->seats[seatIndex]->surname
			<< " " << this->seats[seatIndex]->name << ") released!" << std::endl;
		seats[seatIndex]->reserved = false;
		seats[seatIndex]->name = "";
		seats[seatIndex]->surname = "";
	}
	catch (int e) {
		throw e;
	}
}

unsigned int flight::getNrOfReservedSeats() {
	unsigned int count = 0;
	for (unsigned int i = 0; i < getSize(); i++) {
		if (isSeatReserved(i)) {
			count++;
		}
	}
	return count;
}

unsigned int flight::getNrOfFreeSeats() {
	return getSize() - getNrOfReservedSeats();
}


void flight::remapSeat(unsigned int seatIndex, unsigned int* row, char* col) {
	*row = seatIndex / getCols() + 1;
	*col = seatIndex % getCols() + 65;
}

void flight::printReservations() {
	unsigned int row;
	char seat;
	for (unsigned int i = 0; i < getSize(); i++) {
		if ((this->isSeatReserved(i) && this->seats[i]->type_bool() != true) || (this->isSeatReserved(i) && this->seats[i]->type_bool() == true && seats[i]->name != "")) {
			remapSeat(i, &row, &seat);
			cout << "(" << row << ", " << seat << ") reserved for "
				<< seats[i]->surname << " " << seats[i]->name << endl;
		}

	}
	cout << getSize() << " seats in plane of which " << getNrOfReservedSeats()

		<< " are reserved and " << getNrOfFreeSeats() << " are free. Load: "
		<< getNrOfReservedSeats() / getSize() << "%." << endl << endl
		<< endl;
}

void flight::giveReservations(unsigned int ID, int i) {
	ofstream reservationFile;
	if (i == 0) {
		reservationFile.open("reservations.txt");
	}
	else
		reservationFile.open("reservations.txt", std::ios_base::app);
	unsigned int row;
	char seat;
	for (unsigned int i = 0; i < getSize(); i++) {
		if ((this->isSeatReserved(i) && this->seats[i]->type_bool() != true) || (this->isSeatReserved(i) && this->seats[i]->type_bool() == true && seats[i]->name != "")) {
			remapSeat(i, &row, &seat);
			reservationFile << 
			ID <<',' << row << ',' << seat << "," << seats[i]->surname << "," << seats[i]->name << '\n'; //',' + row + ',' + seat + 
		}
	}
	reservationFile.close();
}




void flight::printSeatMap() {
	cout << "      ";
	unsigned int offset = this->seatsPerRow;
	for (unsigned int i = 0; i < offset; i++) {
		cout << (char)(65 + i) << " ";
		if (this->seatsPerRow == 7) {
			if ((i + 1) == 2 || (i + 1) == 5) {
				cout << "  ";
			}
		}
		else if (this->seatsPerRow == 6) {
			if ((i + 1) == 2) {
				cout << "  ";
			}
		}
		else if (this->seatsPerRow == 9) {
			if ((i + 1) == 3 || (i + 1) == 6) {
				cout << "  ";
			}
		}
		else
		{
			if ((i + 1) % 2 == 0 && i != this->seatsPerRow - 1) {
				cout << "  ";
			}
		}
	}
	cout << std::endl;
	for (unsigned int i = 0; i < this->numRows; i++) {
		cout << std::setw(3) << i + 1 << " | ";
		for (unsigned int j = 0; j < this->seatsPerRow; j++) {
			if (isSeatReserved(i * this->seatsPerRow + j) == 0 && this->seats[i * this->seatsPerRow + j]->type_bool() == false) {
				cout << "_ ";
			}
			else if (isSeatReserved(i * this->seatsPerRow + j) == 0 && this->seats[i * this->seatsPerRow + j]->type_bool() == true) {
				if (j % 2 == 0) {
					cout << "* ";
				}
			}
			else {
				if(j % 2 != 0 && this->seats[i * this->seatsPerRow + j]->type_bool() == true)
					cout << "  ";
				else
					cout << "X ";
			}
			if (this->seatsPerRow == 7) {
				if ((j + 1) == 2 || (j + 1) == 5) {
					cout << "  ";
				}
			}
			else if (this->seatsPerRow == 6) {
				if ((j + 1) == 2) {
					cout << "  ";
				}
			}
			else if (this->seatsPerRow == 9) {
				if ((j + 1) == 3 || (j + 1) == 6) {
					cout << "  ";
				}
			}
			else
			{
				if ((j + 1) % 2 == 0 && j != this->seatsPerRow - 1) {
					cout << "  ";
				}
			}
		}
		cout << "|" << std::endl;
	}

}
