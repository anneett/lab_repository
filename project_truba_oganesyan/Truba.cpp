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
		logging_cout("You do not have pipe data to save.");
	}
	else
	{
		logging_cout("Pipe data is written to a file.");
		fout << "Pipe" << endl;
		fout << tb.idpipe << endl << tb.mark << endl << tb.length << endl << tb.diameter << endl << tb.repair << endl;
	}
}

void DownloadPipe(unordered_map <int, Truba>& pipes)
{
	string filename;
	logging_cout("Enter filename: ");
	cin >> filename;
	logging_cout(filename);
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
					fin >> pipe.mark;
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
		logging_cout("Could not open file named " + filename + " or it doesn't exist.");
	}
}

void OutputPipe(unordered_map <int, Truba>& tb)
{
	if (tb.size() == 0)
	{
		logging_cout("You don't have a pipe to watch.");
	}
	else
		logging_cout("Pipes:\n");
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
			<< "\n4. Exit.";

		int number = -1;
		cout << "\nSelect: ";

		number = GetCorrectData(1, 4);
		switch (number)
		{
		case 1:
		{
			string pipename;
			cout << "Enter an occurrence by name: ";
			cin.ignore();
			getline(cin, pipename);
			unordered_map <int, Truba> trubs1;
			for (auto& xpipe1: tb)
			{
				Truba& pipe_case1 = xpipe1.second;
				if (pipe_case1.mark.find(pipename) != string::npos)
				{
					trubs1.insert({ pipe_case1.idpipe, pipe_case1 });
				}	 
			}
			Working_with_pipes(trubs1);
			for (auto& y : trubs1)
			{
				cout << y.first << y.second << endl;
			}
			break;
		}
		case 2:
		{
			bool repairpipe;
			cout << "Enter an occurrence by attribute: ";
			cin >> repairpipe;
			unordered_map <int, Truba> trubs2;
			for (auto& xpipe2 : tb)
			{
				Truba pipe_case2 = xpipe2.second;
				if (pipe_case2.repair == repairpipe)
				{
					trubs2.insert({ pipe_case2.idpipe, pipe_case2 });
				}
			}
			Working_with_pipes(trubs2);
			for (auto& xxpipe2 : trubs2)
			{
				Truba& truba = xxpipe2.second;
				tb.insert({ truba.idpipe, truba });
			}
			break;
		}
		case 3:
		{
			break;
		}
		case 4:
		{
			return 0;
		}
		default:
		{
			cout << "Enter a number from 1 to 3!" << endl;
			break;
		}
		}
	}
}

void Edit_pipe(unordered_map <int, Truba>& p)
{
	if ((p.size()) != 0) {
		cout << "Enter number of pipes to edit. You have " + to_string(p.size()) + " pipes. Enter: ";
		int number_of_pipes = GetCorrectData(0, int(p.size()));
		Truba ppipe;
		int MaxID = ppipe.max_idp;
		for (int i = 1; i <= number_of_pipes; i++)
		{
			cout << "Enter id pipe: ";
			int id = GetCorrectData(0, MaxID - 1);
			Truba& pipe = p[id];
			pipe.repair = !pipe.repair;
		}
		ppipe.max_idp -= 1;
	}
	else
		cout << " You do not have a pipes." << endl;
}

void Delete_pipe(unordered_map <int, Truba>& p)
{
	if ((p.size()) != 0) {
		cout << "Enter number of pipes to delete. You have " + to_string(p.size()) + " pipes. Enter: ";
		int number_of_pipes = GetCorrectData(0, int(p.size()));
		Truba ppipe;
		int MaxID = ppipe.max_idp;
		cout << MaxID;
		for (int i = 1; i <= number_of_pipes; i++)
		{
			cout << "Enter id pipe: ";
			int id = GetCorrectData(0, MaxID - 1);
			cout << "Entry the pipe state: ";
			Truba& pipe = p[id];
			p.erase(pipe.get_idp());
		}
		ppipe.max_idp -= 1;
	}
	else
		cout << " You do not have a pipes." << endl;
}

int Working_with_pipes(unordered_map <int, Truba>& p)
{
	while (true)
	{

		cout << "\nChoose what you want to do:"
			<< "\n1. Edit pipe;"
			<< "\n2. Delete pipe;"
			<< "\n3. Exit.";

		int number = -1;
		cout << "\nSelect: ";

		number = GetCorrectData(1, 3);
		switch (number)
		{
		case 1:
		{
			Edit_pipe(p);
			break;
		}
		case 2:
		{
			Delete_pipe(p);
			break;
		}
		case 3:
		{
			return 0;
		}
		default:
		{
			cout << "Enter a number from 1 to 3!" << endl;
			break;
		}
		}
	}
}