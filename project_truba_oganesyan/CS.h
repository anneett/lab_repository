#pragma once
#include <string>
#include <unordered_map>

using namespace std;

class CS
{
public:
	int idcs = 0;
	static int max_ids;

	string name = "None";
	int shops = 0;
	int work_shops = 0;
	char efficiency = 'F';

	int id_input = 0;
	int id_output = 0;
	int shortest_path;

	CS();
	int get_ids() { return idcs; };
	friend ostream& operator << (ostream& out, const CS& cs);
	friend istream& operator >> (istream& in, CS& cs);
	friend void DataRecordingCS(ofstream& fout, const CS& cs);
};