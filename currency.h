#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ostream>
#include <algorithm>

class Currency
{
public:
	std::string charCode;
	std::vector<double> values;
	double value;
	
	void updateValues();

	double middleValue();

	double medianValue();

	friend std::ostream& operator<<(std::ostream& os, const Currency& currency);

};

std::ostream& operator<<(std::ostream& os, const Currency& currency);