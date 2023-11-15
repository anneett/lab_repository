#include "Truba.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Utils.h"

using namespace std;
int Truba::max_idp = 0;

Truba::Truba()
{
	idpipe = max_idp++;
}

void Add_pipe(unordered_map <int, Truba>& pipes)
{
	Truba pipe;
	cin >> pipe;
	pipes.insert({ pipe.get_idp(), pipe });		
}

istream& operator >> (istream& in, Truba& tb)
{
	cout << "Enter pipe mark: ";
	cin.ignore();
	getline(cin, tb.mark);
	cout << "Enter pipe length: ";
	tb.length = GetCorrectData(0.0, 10000.0);
	cout << "Enter pipe diameter: ";
	tb.diameter = GetCorrectData(500, 1400);
	cout << "Enter the pipe attribute: ";
	tb.repair = GetCorrectData(0, 1);
	return in;
}

ostream& operator << (ostream& out, const Truba& tb)
{
	if (tb.length == 0)
	{
		cout << "\nNo pipes added." << endl;
	}
	else
	{
		cout << "Pipe ID: " << tb.idpipe
			<< "\nPipe mark: " << tb.mark
			<< "\nPipe length: " << tb.length
			<< "\nPipe diameter: " << tb.diameter
			<< "\nThe pipe attribute: " << tb.repair << endl;
	}
	return out;
}

void DataRecordingPipe(ofstream& fout, const Truba& tb)
{
	if (tb.length == 0)
	{
		cout << "You do not have pipe data to save." << endl;
	}
	else
	{
		cout << "Pipe data is written to a file." << endl;
		fout << "Pipe" << endl;
		fout << tb.idpipe << endl << tb.mark << endl << tb.length << endl << tb.diameter << endl << tb.repair << endl;
	}
}

void DownloadPipe(unordered_map <int, Truba>& pipes)
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

void OutputPipe(unordered_map <int, Truba>& tb)
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

int Filter_pipes(unordered_map <int, Truba>& tb)
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
			vector <int> id1_filter;
			for (auto& xpipe1: tb)
			{
				Truba& pipe_case1 = xpipe1.second;
				if (pipe_case1.mark.find(pipename) != string::npos)
				{
					id1_filter.push_back(pipe_case1.idpipe);
				}	 
			}
			Working_with_pipes(tb, id1_filter);
			break;
		}
		case 2:
		{
			bool repairpipe;
			cout << "Enter an occurrence by attribute: ";
			cin >> repairpipe;
			vector <int> id2_filter;
			for (auto& xpipe2: tb)
			{
				Truba pipe_case2 = xpipe2.second;
				if (pipe_case2.repair == repairpipe)
				{
					id2_filter.push_back(pipe_case2.idpipe);
				}
			}
			Working_with_pipes(tb, id2_filter);
			break;
		}
		case 3:
		{
			vector <int> id3_filter;
			for (auto& pipe_case3 : tb)
			{
				id3_filter.push_back(pipe_case3.first);
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

void Edit_pipe(unordered_map <int, Truba>& tb, vector <int>& id_filter)
{
	if ((id_filter.size()) != 0) {
		cout << "Enter number of pipes to edit. You have " + to_string(id_filter.size()) + " pipes. Enter: ";
		int number_of_pipes = GetCorrectData(0, int(id_filter.size()));
		for (int i = 1; i <= number_of_pipes; i++)
		{
			cout << "Enter ID pipe: ";
			int id = GetCorrectData(0, *max_element(id_filter.begin(), id_filter.end()));
			if (find(id_filter.begin(), id_filter.end(), id) != id_filter.end())
			{
				Truba& pipe = tb[id];
				pipe.repair = !pipe.repair;
			}
		}
	}
	else
		cout << " You do not have a pipes with this filter." << endl;
}

void Delete_pipe(unordered_map <int, Truba>& tb, vector <int>& id_filter)
{
	if ((id_filter.size()) != 0) {
		cout << "Enter number of pipes to delete. You have " + to_string(id_filter.size()) + " pipes. Enter: ";
		int number_of_pipes = GetCorrectData(0, int(id_filter.size()));
		for (int i = 1; i <= number_of_pipes; i++)
		{
			cout << "Enter ID pipe: ";
			int id = GetCorrectData(0, *max_element(id_filter.begin(), id_filter.end()));
			if (find(id_filter.begin(), id_filter.end(), id) != id_filter.end())
			{
				tb.erase(id);
				vector<int>::iterator itr = find(id_filter.begin(), id_filter.end(), id);
				id_filter.erase(itr);
			}
		}
	}
	else
		cout << " You do not have a pipes with this filter." << endl;
}

int Working_with_pipes(unordered_map <int, Truba>& tb, vector <int>& id_filter)
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