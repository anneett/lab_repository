#include "Truba.h"
#include "CS.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Utils.h"
#include "Truba_and_CS.h"
#include <set>

using namespace std;

void GTS::Add_pipe(unordered_map <int, Truba>& pipes)
{
	Truba pipe;
	cin >> pipe;
	pipes.insert({ pipe.get_idp(), pipe });
}

void GTS::DownloadPipe(unordered_map <int, Truba>& pipes)
{
	string filename;
	cout << "Enter filename: " << endl;
	cin >> filename;
	ifstream fin;
	fin.open((filename + ".txt"));
	if (fin.is_open())
	{
		string pipe_name = "";
		bool p = 0;
		while (getline(fin, pipe_name))
		{
			if (pipe_name == "Pipe")
			{
				Truba pipe;
				cout << "Data received from file about pipe:" << endl;
				cout << "\nPipe" << endl;
				fin >> pipe.max_idp;
				cout << "Pipe MaxID: " << pipe.max_idp << endl;
				fin >> pipe.idpipe;
				cout << "Pipe ID: " << pipe.idpipe << endl;
				fin.clear();
				fin.ignore(1000, '\n');
				getline(fin, pipe.mark);
				cout << "Pipe elevation: " << pipe.mark << endl;
				fin >> pipe.length;
				cout << "Pipe length: " << pipe.length << endl;
				fin >> pipe.diameter;
				cout << "Pipe diameter: " << pipe.diameter << endl;
				fin >> pipe.repair;
				cout << "The pipe attribute: " << pipe.repair << endl;
				pipes.insert({ pipe.idpipe, pipe });
				p = 1;
			}
		}
		if (!p)
		{
			cout << "No information about pipes." << endl;
		}
		fin.close();
	}
	else
	{
		cout << "Could not open file named " + filename + " or it doesn't exist." << endl;
	}
}

void GTS::OutputPipe(unordered_map <int, Truba>& tb)
{
	if (tb.size() == 0)
	{
		cout << "You don't have a pipe to watch." << endl;
	}
	else
		cout << "Pipes:\n" << endl;
	for (auto& pipe : tb)
		cout << pipe.second << endl;
}

template <typename T>
using Filter = bool(*)(const Truba& pipe, T param);

bool CheckByName(const Truba& pipe, string param)
{
	return (pipe.mark.find(param) != string::npos);
}
bool CheckByAttribute(const Truba& pipe, bool param)
{
	return (pipe.repair == param);
}

template <typename T>
set <int> FindPipesByFilter(const unordered_map <int, Truba>& tb, Filter<T> filt, T param)
{
	set <int> ident;
	int i = 0;
	for (auto& [id, pipe] : tb)
	{
		if (filt(pipe, param))
			ident.insert(i);
		i++;
	}
	return ident;
}

void Edit_pipe(unordered_map <int, Truba>& tb, set <int>& id_filter)
{
	if ((id_filter.size()) != 0) {
		cout << "Enter number of pipes to edit. You have " + to_string(id_filter.size()) + " pipes. Enter: ";
		int number_of_pipes = GetCorrectData(0, int(id_filter.size()));
		for (int i = 1; i <= number_of_pipes; i++)
		{
			cout << "Enter ID pipe: ";
			int id = GetCorrectData(0, *max_element(id_filter.begin(), id_filter.end()));
			if (id_filter.find(id) != id_filter.end())
			{
				Truba& pipe = tb[id];
				pipe.repair = !pipe.repair;
			}
		}
	}
	else
		cout << " You do not have a pipes with this filter." << endl;
}

void Delete_pipe(unordered_map <int, Truba>& tb, set <int>& id_filter)
{
	if ((id_filter.size()) != 0) {
		cout << "Enter number of pipes to delete. You have " + to_string(id_filter.size()) + " pipes. Enter: ";
		int number_of_pipes = GetCorrectData(0, int(id_filter.size()));
		for (int i = 1; i <= number_of_pipes; i++)
		{
			cout << "Enter ID pipe: ";
			int id = GetCorrectData(0, *max_element(id_filter.begin(), id_filter.end()));
			if (id_filter.find(id) != id_filter.end())
			{
				tb.erase(id);
				set<int>::iterator itr = id_filter.find(id);
				id_filter.erase(itr);
			}
		}
	}
	else
		cout << " You do not have a pipes with this filter." << endl;
}


int Working_with_pipes(unordered_map <int, Truba>& tb, set <int>& id_filter)
{
	while (true)
	{
		cout << "You have " + to_string(id_filter.size()) + " pipes." << endl;
		cout << "\nChoose what you want to do:"
			<< "\n1. Edit pipe;"
			<< "\n2. Delete pipe;"
			<< "\n3. Exit." << endl;
		cout << "\nSelect: ";

		int number = GetCorrectData(1, 3);
		switch (number)
		{
		case 1:
		{
			Edit_pipe(tb, id_filter);
			break;
		}
		case 2:
		{
			Delete_pipe(tb, id_filter);
			break;
		}
		case 3:
		{
			return 0;
		}
		}
	}
}

int GTS::Filter_pipes(unordered_map <int, Truba>& tb)
{
	while (true)
	{
		cout << "\nSelect object parameter: "
			<< "\n1. Pipe name;"
			<< "\n2. 'Under repair' sign;"
			<< "\n3. All pipes."
			<< "\n4. Exit." << endl;
		cout << "\nSelect: ";

		int number = GetCorrectData(1, 4);
		switch (number)
		{
		case 1:
		{
			string pipename;
			cout << "Enter an occurrence by name: ";
			cin.ignore();
			getline(cin, pipename);
			set <int> id1_filter;
			id1_filter = FindPipesByFilter(tb, CheckByName, pipename);
			Working_with_pipes(tb, id1_filter);
			break;
		}
		case 2:
		{
			bool repairpipe;
			cout << "Enter an occurrence by attribute: ";
			cin >> repairpipe;
			set <int> id2_filter;
			id2_filter = FindPipesByFilter(tb, CheckByAttribute, repairpipe);
			Working_with_pipes(tb, id2_filter);
			break;
		}
		case 3:
		{
			set <int> id3_filter;
			for (auto& pipe_case3 : tb)
			{
				id3_filter.insert(pipe_case3.first);
			}
			Working_with_pipes(tb, id3_filter);
			break;
		}
		case 4:
		{
			return 0;
		}
		}
	}
}

void GTS::Add_CS(unordered_map <int, CS>& stations)
{
	CS station;
	cin >> station;
	stations.insert({ station.get_ids(), station });
}

void GTS::OutputCS(unordered_map <int, CS>& cs)
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

void GTS::DownloadCS(unordered_map <int, CS>& stations)
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
				fin >> station.max_ids;
				cout << "CS ID: " << station.max_ids << endl;
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

template <typename T>
using Filter1 = bool(*)(const CS& cs, T param);

bool CheckByName(const CS& cs, string param)
{
	return (cs.name.find(param) != string::npos);
}
bool CheckByMore(const CS& cs, int param)
{
	return (((cs.shops - cs.work_shops) * 100 / cs.shops) > param);
}
bool CheckByLess(const CS& cs, int param)
{
	return (((cs.shops - cs.work_shops) * 100 / cs.shops) < param);
}
bool CheckByEqual(const CS& cs, int param)
{
	return (((cs.shops - cs.work_shops) * 100 / cs.shops) == param);
}

template <typename T>
set <int> FindCSByFilter(const unordered_map <int, CS>& cs, Filter1<T> filt, T param)
{
	set <int> ident;
	int i = 0;
	for (auto& [id, station] : cs)
	{
		if (filt(station, param))
			ident.insert(i);
		i++;
	}return ident;
}

void Edit_CS(unordered_map <int, CS>& cs, set <int>& id_filter)
{
	if ((id_filter.size()) != 0) {
		cout << "Enter number of CS to edit. You have " + to_string(id_filter.size()) + " CS. Enter: ";
		int number_of_cs = GetCorrectData(0, int(id_filter.size()));
		for (int i = 1; i <= number_of_cs; i++)
		{
			cout << "Enter ID station: ";
			int id = GetCorrectData(0, *max_element(id_filter.begin(), id_filter.end()));
			if (id_filter.find(id) != id_filter.end())
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

void Delete_CS(unordered_map <int, CS>& cs, set <int>& id_filter)
{
	if ((id_filter.size()) != 0) {
		cout << "Enter number of CS to delete. You have " + to_string(id_filter.size()) + " CS. Enter: ";
		int number_of_cs = GetCorrectData(0, int(id_filter.size()));
		for (int i = 1; i <= number_of_cs; i++)
		{
			cout << "Enter ID station: ";
			int id = GetCorrectData(0, *max_element(id_filter.begin(), id_filter.end()));
			if (id_filter.find(id) != id_filter.end())
			{
				cs.erase(id);
				set <int>::iterator itr = id_filter.find(id);
				id_filter.erase(itr);
			}
		}
	}
	else
		cout << " You do not have a CS with this filter." << endl;
}

int Working_with_CS(unordered_map <int, CS>& cs, set <int>& id_filter)
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

int GTS::Filter_CS(unordered_map <int, CS>& cs)
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
			set <int> id1_filter;
			id1_filter = FindCSByFilter(cs, CheckByName, csname);
			Working_with_CS(cs, id1_filter);
			break;
		}
		case 2:
		{
			cout << "Enter an occurrence by percentage of idle workshops: ";
			int percent = GetCorrectData(0, 100);
			set <int> id2_filter;
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
				id2_filter = FindCSByFilter(cs, CheckByMore, percent);
				break;
			}
			case 2:
			{
				id2_filter = FindCSByFilter(cs, CheckByLess, percent);
				break;
			}
			case 3:
			{
				id2_filter = FindCSByFilter(cs, CheckByEqual, percent);
				break;
			}
			}
			Working_with_CS(cs, id2_filter);
			break;
		}
		case 3:
		{
			set <int> id3_filter;
			for (auto& cs_case3 : cs)
			{
				id3_filter.insert(cs_case3.first);
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

void GTS::ObjectsSaving(unordered_map <int, Truba>& pipes, unordered_map <int, CS>& stations)
{
	if (pipes.size() == 0 && stations.size() == 0)
	{
		cout << "You have no objects to save" << endl;
	}
	else
	{
		string filename;
		cout << "Enter filename: " << endl;
		cin >> filename;
		ofstream fout;
		fout.open((filename + ".txt"), ios::trunc);
		if (fout.is_open())
		{
			for (const auto& tb : pipes)
			{
				DataRecordingPipe(fout, tb.second);
				cout << "Data about the pipe with ID " + to_string(tb.first) + " is saved to file named " + filename + "." << endl;
			}
			for (const auto& cs : stations)
			{
				DataRecordingCS(fout, cs.second);
				cout << "Data about the station with ID " + to_string(cs.first) + " is saved to file named " + filename + "." << endl;
			}
			fout.close();
		}
		else
		{
			cout << "Could not open file named " + filename + "." << endl;
		}
	}
}