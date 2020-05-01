#pragma once
#include "seat.h"
class premium_seat :
	public seat
{
	bool type_bool() {
		return true;
	}
	void type() {
		cout << "premium";
	}
};

