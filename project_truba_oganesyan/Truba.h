#pragma once
#include <string>

using namespace std;

class Truba
{
private:
	string mark = "None";
	double length = 0;
	int diameter = 0;
	bool repair = false;

public:
	static int max_idp;
	friend ostream& operator << (ostream& out, const Truba& tb);
	friend istream& operator >> (istream& in, Truba& tb);
};

