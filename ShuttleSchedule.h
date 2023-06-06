#pragma once
#include "bibl.h"

struct DayProperties {
	bool light;
	int day;
	int temp;
	int wind;
	int humid;
	int precip;
	string clouds;
	
	DayProperties(int d) {
		day = d;
	}
};

class ShuttleSchedule {
	vector<DayProperties> dates;
	int bestDay = -1;

	void gatherParms(vector<string>&); // TASK 1
	void getLaunchingData(); // TASK 2

	int avg(size_t);
	int max(size_t);
	int min(size_t);
	int median(size_t);
public:
	void gatherInformationFromFile(ifstream&); // TASK 1
	void writeInformationToFile();  // TASK 2
};