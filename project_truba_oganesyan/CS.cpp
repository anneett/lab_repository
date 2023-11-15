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
		cout << "You do not have CS data to save." << endl;
	}
	else
	{
		cout << "CS data is written to a file." << endl;
		fout << "CS" << endl;
		fout <<cs.idcs << endl << cs.name << endl << cs.shops << endl << cs.work_shops << endl << cs.efficiency << endl;
	}
}

void OutputCS(unordered_map <int, CS>& cs)
{
	if (cs.size() == 0)
	{
		cout << "You don't have a CS to watch." << endl;
	}
	else
		cout << "Compressor stations:\n" << endl;
	for (auto& station : cs)
		cout << station.second << endl;
}

void DownloadCS(unordered_map <int, CS>& stations)
{
	string filename;
	cout << "Enter filename: " << endl;
	cin >> filename;
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
				fin.clear();
				fin.ignore(1000, '\n');
				getline(fin, station.name);
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
		cout << "Could not open file named " + filename + " or it doesn't exist." << endl;
	}
}


int Filter_CS(unordered_map <int, CS>& cs)
{
	while (true)
	{
		cout << "\nSelect object parameter: "
			<< "\n1. Station name;"
			<< "\n2. Percentage of idle workshops;"
			<< "\n3. All stations."
			<< "\n4. Exit." << endl;
		cout << "\nSelect: ";

		int number = GetCorrectData(1, 4);
		switch (number)
		{
		case 1:
		{
			string csname;
			cout << "Enter an occurrence by name: ";
			cin.ignore();
			getline(cin, csname);
			vector <int> id1_filter;
			for (auto& xcs1 : cs)
			{
				CS& cs_case1 = xcs1.second;
				if (cs_case1.name.find(csname) != string::npos)
				{
					id1_filter.push_back(cs_case1.idcs);
				}
			}
			Working_with_CS(cs, id1_filter);
		}
		case 2:
		{
			cout << "Enter an occurrence by percentage of idle workshops: ";
			int percent = GetCorrectData(0, 100);
			vector <int> id2_filter;
			cout << "\nSelect comparison option: ";
			cout << "\n1. More;"
				<< "\n2. Less;"
				<< "\n3. Equals." << endl;
			cout << "\nSelect: ";
			int choice = GetCorrectData(1, 3);
			switch (choice)
			{
			case 1:
			{
				for (auto& per_case : cs)
				{
					CS& per_cs = per_case.second;
					if (((per_cs.shops - per_cs.work_shops) * 100 / per_cs.shops) > percent)
					{
						id2_filter.push_back(per_cs.idcs);
					}
				}
				break;
			}
			case 2:
			{
				for (auto& per_case : cs)
				{
					CS& per_cs = per_case.second;
					if (((per_cs.shops - per_cs.work_shops) * 100 / per_cs.shops) < percent)
					{
						id2_filter.push_back(per_cs.idcs);
					}
				}
				break;
			}
			case 3:
			{
				for (auto& per_case : cs)
				{
					CS& per_cs = per_case.second;
					if (((per_cs.shops - per_cs.work_shops) * 100 / per_cs.shops) == percent)
					{
						id2_filter.push_back(per_cs.idcs);
					}
				}
				break;
			}
			}
			Working_with_CS(cs, id2_filter);
			break;
		}
		case 3:
		{
			vector <int> id3_filter;
			for (auto& cs_case3 : cs)
			{
				id3_filter.push_back(cs_case3.first);
			}
			Working_with_CS(cs, id3_filter);
			break;
		}
		case 4:
		{
			return 0;
		}
		}
	}
}

void Edit_CS(unordered_map <int, CS>& cs, vector <int>& id_filter)
{
	if ((id_filter.size()) != 0) {
		cout << "Enter number of CS to edit. You have " + to_string(id_filter.size()) + " CS. Enter: ";
		int number_of_cs = GetCorrectData(0, int(id_filter.size()));
		for (int i = 1; i <= number_of_cs; i++)
		{
			cout << "Enter ID station: ";
			int id = GetCorrectData(0, *max_element(id_filter.begin(), id_filter.end()));
			if (find(id_filter.begin(), id_filter.end(), id) != id_filter.end())
			{
				CS& cstation = cs[id];
				cout << "Change the number of workshops in operation: ";
				cstation.work_shops = GetCorrectData(0, 1000);
				while (cstation.work_shops > cstation.shops)
				{
					cout << "The number of workshops cannot exceed the number of all shops!" << endl;
					cstation.work_shops = GetCorrectData(0, 1000);
				}
			}
		}
	}
	else
		cout << "You do not have a CS with this filter." << endl;
}

void Delete_CS(unordered_map <int, CS>& cs, vector <int>& id_filter)
{
	if ((id_filter.size()) != 0) {
		cout << "Enter number of CS to delete. You have " + to_string(id_filter.size()) + " CS. Enter: ";
		int number_of_cs = GetCorrectData(0, int(id_filter.size()));
		for (int i = 1; i <= number_of_cs; i++)
		{
			cout << "Enter ID station: ";
			int id = GetCorrectData(0, *max_element(id_filter.begin(), id_filter.end()));
			if (find(id_filter.begin(), id_filter.end(), id) != id_filter.end())
			{
				cs.erase(id);
				vector<int>::iterator itr = find(id_filter.begin(), id_filter.end(), id);
				id_filter.erase(itr);
			}
		}
	}
	else
		cout << " You do not have a CS with this filter." << endl;
}

int Working_with_CS(unordered_map <int, CS>& cs, vector <int>& id_filter)
{
	while (true)
	{
		cout << "You have " + to_string(id_filter.size()) + " CS." << endl;
		cout << "\nChoose what you want to do:"
			<< "\n1. Edit stations;"
			<< "\n2. Delete stations;"
			<< "\n3. Exit." << endl;
		cout << "\nSelect: ";

		int number = GetCorrectData(1, 3);
		switch (number)
		{
		case 1:
		{
			Edit_CS(cs, id_filter);
			break;
		}
		case 2:
		{
			Delete_CS(cs, id_filter);
			break;
		}
		case 3:
		{
			return 0;
		}
		}
	}
}