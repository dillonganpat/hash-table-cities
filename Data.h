#ifndef _DATA_H
#define _DATA_H

#include <iostream>
	using namespace std;

#define MAX_ELEMENTS 5000

struct City {
	string name;
	double latitude;
	double longitude;
	string country;
	string country_iso2;
	int population;
};

#endif
