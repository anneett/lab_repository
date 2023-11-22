#pragma once
#include <string>
#include <unordered_map>

using namespace std;

class Truba
{
public:
	int idpipe = 0;
	static int max_idp;
	string mark = "None";
	double length = 0;
	int diameter = 0;
	bool repair = false;
	Truba();
	int get_idp() { return idpipe; };
	friend ostream& operator << (ostream& out, const Truba& tb);
	friend istream& operator >> (istream& in, Truba& tb);
	friend void DataRecordingPipe(ofstream& fout, const Truba& tb);
};