#pragma once
#include <string>
#include <unordered_map>

using namespace std;

class CS
{
private:
	int idcs = 0;
	char efficiency = 'F';

public:
	string name = "None";
	int shops = 0;
	int work_shops = 0;
	static int max_ids;

	CS();
	int get_ids() { return idcs; };
	friend ostream& operator << (ostream& out, const CS& cs);
	friend istream& operator >> (istream& in, CS& cs);
	friend void Add_CS(unordered_map <int, CS>& pipes);
	friend void OutputCS(unordered_map <int, CS>& cs);
	friend void DataRecordingCS(ofstream& fout, const CS& cs);
	friend void DownloadCS(unordered_map <int, CS>& cs);

	//friend void ObjectsSaving(unordered_map <int, Truba>& pipes, unordered_map <int, CS>& stations);
};