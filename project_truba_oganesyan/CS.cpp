#include "CS.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Utils.h"

using namespace std;
int CS::max_ids = 0;

CS::CS()
{
	idcs = max_ids++;
}

void Add_CS(unordered_map <int, CS>& stations)
{
	CS station;
	cin >> station;
	stations.insert({ station.get_ids(), station});
}

istream& operator >> (istream& in, CS& cs)
{
	cout << "Enter the title: ";
	cin.ignore();
	getline(cin, cs.name);
	cout << "Enter the number of workshops: ";
	cs.shops = GetCorrectData(1, 1000);
	cout << "Enter the number of workshops in operation: ";
	cs.work_shops = GetCorrectData(0, 1000);
	while (cs.work_shops > cs.shops)
	{
		cout << "The number of workstations cannot exceed the number of all stations!" << endl;
		cs.work_shops = GetCorrectData(0, 1000);
	}
	cout << "Enter efficiency: ";
	cs.efficiency = GetCorrectData('A', 'F');
	return in;
}

ostream& operator << (ostream& out, const CS& cs)
{
	if (cs.shops == 0)
	{
		cout << "\nNo added compressor stations." << endl;
	}
	else
	{
		cout << "CS ID: " << cs.idcs
			<< "\nTitle: " << cs.name
			<< "\nEnter the number of workshops: " << cs.shops
			<< "\nEnter the number of workshops in operation: " << cs.work_shops
			<< "\nEnter efficiency: " << cs.efficiency << endl;
	}
	return out;
}

void DataRecordingCS(ofstream& fout, const CS& cs)
{
	if (cs.shops == 0)
	{
		logging_cout("You do not have CS data to save.");
	}
	else
	{
		logging_cout("CS data is written to a file.");
		fout << "CS" << endl;
		fout <<cs.idcs << endl << cs.name << endl << cs.shops << endl << cs.work_shops << endl << cs.efficiency << endl;
	}
}

void OutputCS(unordered_map <int, CS>& cs)
{
	if (cs.size() == 0)
	{
		logging_cout("You don't have a CS to watch.");
	}
	else
		logging_cout("Compressor stations:\n");
	for (auto& station : cs)
		cout << station.second << endl;
}

void DownloadCS(unordered_map <int, CS>& stations)
{
	string filename;
	logging_cout("Enter filename: ");
	cin >> filename;
	logging_cout(filename);
	ifstream fin;
	fin.open((filename + ".txt"));
	if (fin.is_open())
	{
		string cs_name = "";
		bool s = 0;
		while (getline(fin, cs_name))
		{
			if (cs_name == "CS")
			{
				CS station;
				cout << "Data received from file about CS:" << endl;
				cout << "\nCompressor station" << endl;
				fin >> station.idcs;
				cout << "CS ID: " << station.idcs << endl;
				fin >> station.name;
				cout << "CS title: " << station.name << endl;
				fin >> station.shops;
				cout << "Number of workshops of the CS: " << station.shops << endl;
				fin >> station.work_shops;
				cout << "Number of workshops in operation of the CS: " << station.work_shops << endl;
				fin >> station.efficiency;
				cout << "CS efficiency: " << station.efficiency << endl;
				stations.insert({ station.idcs, station });
				s = 1;
			}
		}
		if (!s)
		{
			cout << "No information about stations." << endl;
		}
		fin.close();
	}
	else
	{
		logging_cout("Could not open file named " + filename + " or it doesn't exist.");
	}
}