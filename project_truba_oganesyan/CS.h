#pragma once
#include <string>

using namespace std;

class CS
{
private:
	int idcs = 0;
	string name = "None";
	int shops = 0;
	int work_shops = 0;
	char efficiency = 'F';

public:
	static int max_ids;
	friend istream& operator >> (istream& in, CS& cs);
	friend ostream& operator << (ostream& out, const CS& cs);
};

