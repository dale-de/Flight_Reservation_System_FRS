#pragma once
#include "airports.h"

using namespace std;

airports::airports() {
	airport* a;
	string line;
	ifstream airport_file("airports.txt");
	if (airport_file.is_open()) {
		cout << "Read airports from file";
		while (getline(airport_file, line)) {
			a = new airport(line);
			this->LoC.push_back(*a);
			cout << ".";
		}
		airport_file.close();
		cout << "  Successfull" << endl;
	}
	else {
		a = new airport("London");
		this->LoC.push_back(*a);
		a = new airport("Paris");
		this->LoC.push_back(*a);
		a = new airport("Helsinki");
		this->LoC.push_back(*a);;
		a = new airport("Frankfurt");
		this->LoC.push_back(*a);
		a = new airport("Moscow");
		this->LoC.push_back(*a);
		a = new airport("NewYork");
		this->LoC.push_back(*a);
		a = new airport("Tokyo");
		this->LoC.push_back(*a);
		a = new airport("Sydney");
		this->LoC.push_back(*a);
	}
}

void airports::printAirports() {
	cout << "Available Airports and corresponding IDs are:" << endl;
	for (unsigned int i = 0; i < this->LoC.size(); i++) {
		cout << left << "| [" << i << "] " << setw(15) << LoC.at(i).name;
	}
	cout << endl;
}
	bool airports::isIDvalid(unsigned int IDtoCheck) {
		return IDtoCheck < LoC.size();
	}
	string airports::getAirportByID(unsigned int ID) {
		airport a = LoC.at(ID);
		return a.name.c_str();
	}
