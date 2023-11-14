#pragma once
#include <string>
#include <unordered_map>

using namespace std;

class Truba
{
private:
	int idpipe = 0;
	double length = 0;
	int diameter = 0;

public:
	string mark = "None";
	bool repair = false;
	static int max_idp;

	Truba();
	int get_idp() { return idpipe; };
	friend ostream& operator << (ostream& out, const Truba& tb);
	friend istream& operator >> (istream& in, Truba& tb);
	friend void Add_pipe(unordered_map <int, Truba>& pipes);
	friend void OutputPipe(unordered_map <int, Truba>& tb);
	friend void DataRecordingPipe(ofstream& fout, const Truba& tb);
	friend void DownloadPipe(unordered_map <int, Truba>& pipes);
	friend int Filter_pipes(unordered_map <int, Truba>& tb);
	friend int Working_with_pipes(unordered_map <int, Truba>& tb);

	//friend void ObjectsSaving(unordered_map <int, Truba>& pipes, unordered_map <int, CS>& stations);
};