#pragma once
#include <string.h>
#include <iostream>
#include <iomanip>

using namespace std;

class seat
{
public:
	bool reserved;
	seat() {
		this->reserved = false;
	}

	string name;
	string surname;

	virtual bool type_bool();
	virtual void type();
};

