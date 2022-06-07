#include "currency.h"

void Currency::updateValues()
{
	values.push_back(value);
}

double Currency::middleValue()
{
	double sum = 0;
	for (auto i : values)
	{
		sum += i;
	}

	return sum / values.size();
}

double Currency::medianValue()
{
	sort(values.begin(), values.end());
	return values[values.size() / 2];
}

std::ostream& operator<<(std::ostream& os, const Currency& currency)
{
	os << currency.charCode << " : " << currency.value << std::endl;
	return os;
}