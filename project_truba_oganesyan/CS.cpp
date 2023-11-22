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
		cout << "CS MaxID: " << cs.max_ids
			<< "\nCS ID: " << cs.idcs
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
		cout << "You do not have CS data to save." << endl;
	}
	else
	{
		cout << "CS data is written to a file." << endl;
		fout << "CS" << endl;
		fout << cs.max_ids << endl << cs.idcs << endl << cs.name << endl << cs.shops << endl << cs.work_shops << endl << cs.efficiency << endl;
	}
}

