#pragma once
using namespace std;
#include <string>
#include <iomanip>
class airport
{
public:
	string name;
	airport(string name) {
		this->name = name;
	}
	string PrintName() {
		return name;
	}
};

