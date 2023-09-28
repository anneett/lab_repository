#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Truba
{
	string mark = "None";
	double length = 0;
	int diameter = 0;
	bool repair = false;
};

struct CS
{
	string name = "None";
	int shops = 0;
	int work_shops = 0;
	char efficiency = 'F';
};

void check_int(int& digit)
{
	cin >> digit;
	while (cin.fail() || cin.peek() != '\n' || digit <= 0)
	{
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "\nEnter data of type integer greater then 0!\n";
		cin >> digit;
	}
}

void check_doub(double& dual)
{
	cin >> dual;
	while (cin.fail() || cin.peek() != '\n' || dual <= 0)
	{
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "\nEnter double data greater then 0!\n";
		cin >> dual;
	}
}

void check_bool(bool& boolean)
{
	cin >> boolean;
	while (cin.fail() || cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "\nEnter bool data!\n";
		cin >> boolean;
	}
}

void check_char(char& symbol)
{
	cin >> symbol;
	while (cin.fail() || cin.peek() != '\n' || (symbol < 'A') || (symbol > 'F'))
	{
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "\nEnter data of type char from 'A' to 'F'!\n";
		cin >> symbol;
	}
}

Truba CreatePipe()
{
	Truba tb;
	cout << "Enter pipe mark: ";
	cin.ignore();
	getline(cin, tb.mark);
	cout << "Enter pipe length: ";
	check_doub(tb.length);
	cout << "Enter pipe diameter: ";
	check_int(tb.diameter);
	cout << "Enter the pipe attribute: ";
	check_bool(tb.repair);
	return tb;
};

CS CreateCS()
{
	CS cs;
	cout << "Enter the title: ";
	cin.ignore();
	getline(cin, cs.name);
	cout << "Enter the number of workshops: ";
	check_int(cs.shops);
	cout << "Enter the number of workshops in operation: ";
	check_int(cs.work_shops);
	while (cs.work_shops > cs.shops)
	{
		cout << "The number of workstations cannot exceed the number of all stations!" << endl;
		check_int(cs.work_shops);
	}
	cout << "Enter efficiency: ";
	check_char(cs.efficiency);
	return cs;
};

void PrintPipe(const Truba& tb)
{
	if (tb.length == 0)
	{
		cout << "\nNo pipes added." << endl;
	}
	else
	{
		cout << "\nPipe" << endl;
		cout << "Pipe mark: " << tb.mark
			<< "\nPipe length: " << tb.length
			<< "\nPipe diameter: " << tb.diameter
			<< "\nThe pipe attribute: " << tb.repair << endl;
	}
};

void PrintCS(const CS& cs)
{
	if (cs.shops == 0)
	{
		cout << "\nNo added compressor stations." << endl;
	}
	else
	{
		cout << "\nCompressor station" << endl;
		cout << "Title: " << cs.name
			<< "\nEnter the number of workshops: " << cs.shops
			<< "\nEnter the number of workshops in operation: " << cs.work_shops
			<< "\nEnter efficiency: " << cs.efficiency << endl;
	}
};

void DataReceivingPipe(Truba& trb)
{
	ifstream fin("data");
	if (fin)
	{
		string pipe_name = "no";
		int p = 0;
		while (getline(fin, pipe_name))
		{
			if (pipe_name == "Pipe")
			{
				cout << "Data received from file about pipe:" << endl;
				cout << "\nPipe" << endl;
				getline(fin, trb.mark);
				cout << "Pipe elevation: " << trb.mark << endl;
				fin >> trb.length;
				cout << "Pipe length: " << trb.length << endl;
				fin >> trb.diameter;
				cout << "Pipe diameter: " << trb.diameter << endl;
				fin >> trb.repair;
				cout << "The pipe attribute: " << trb.repair << endl;
				p += 1;
			}
		}
		if (p == 0)
		{
			cout << "No information about pipe." << endl;
		}
		fin.close();
	}
}

void DataReceivingCS(CS& drcs)
{
	ifstream fin("data");
	if (fin)
	{
		string cs_name = "no";
		int s = 0;
		while (getline(fin, cs_name))
		{
			if (cs_name == "Compressor station")
			{
				cout << "Data received from file about CS:" << endl;
				cout << "\nCompressor station" << endl;
				getline(fin, drcs.name);
				cout << "CS title: " << drcs.name << endl;
				fin >> drcs.shops;
				cout << "Number of workshops of the CS: " << drcs.shops << endl;
				fin >> drcs.work_shops;
				cout << "Number of workshops in operation of the CS: " << drcs.work_shops << endl;
				fin >> drcs.efficiency;
				cout << "CS efficiency: " << drcs.efficiency << endl;
				s += 1;
			}
		}
		if (s == 0)
		{
			cout << "No information about station." << endl;
		}
		fin.close();
	}
}

void DataRecordingPipe(Truba trb, CS drcs)
{
	
	if (trb.length == 0)
	{
		cout << "No pipe data to record." << endl;
	}
	else
	{
		ofstream fout;
		if (drcs.shops == 0)
		{
			fout.open("data");
		}
		else
		{
			fout.open("data");
		}
		cout << "Data about pipe written to file." << endl;
		if (fout)
		{
			fout << "Pipe" << endl;
			fout << trb.mark << endl;
			fout << trb.length << endl;
			fout << trb.diameter << endl;
			fout << trb.repair << endl;
		}
		fout.close();
	}
	
}

void DataRecordingCS(Truba trb, CS drcs)
{

	if (drcs.shops == 0)
	{
		cout << "No CS data to record." << endl;
	}
	else
	{
		ofstream fout;
		if (trb.length == 0)
		{
			fout.open("data");
		}
		else
		{
			fout.open("data", ios::app);
		}
		if (fout)
		{
			cout << "Data about CS written to file." << endl;
			fout << "Compressor station" << endl;
			fout << drcs.name << endl;
			fout << drcs.shops << endl;
			fout << drcs.work_shops << endl;
			fout << drcs.efficiency << endl;
		}
		fout.close();
	}

}







int main()
{
	Truba pipe;
	CS station;
	while (true) {
		cout << "\nSelect menu item: "
			<< "\n1. Add pipe;"
			<< "\n2. Add compressor station;"
			<< "\n3. View all objects;"
			<< "\n4. Edit pipe;"
			<< "\n5. Edit compressor station;"
			<< "\n6. Save;"
			<< "\n7. Download;"
			<< "\n8. Exit." << endl;

		int number = -1;
		cout << "\nSelect: ";

		check_int(number);

		switch (number)
		{
		case 1:
		{
			pipe = CreatePipe();
			break;
		}
		case 2:
		{
			station = CreateCS();
			break;
		}
		case 3:
		{
			cout << "\All objects: " << endl;
			PrintPipe(pipe);
			PrintCS(station);
			break;
		}
		case 4:
		{
			if (pipe.length == 0)
			{
				cout << "You don't have added pipe." << endl;
			}
			else
			{
				cout << "Change the sign 'in repair': ";
				check_bool(pipe.repair);
			}
			break;
		}
		case 5:
		{
			if (station.shops == 0)
			{
				cout << "You don't have added CS." << endl;
			}
			else
			{
				cout << "Change the number of workshops in operation: ";
				check_int(station.work_shops);
				while (station.work_shops > station.shops)
				{
					cout << "The number of workstations cannot exceed the number of all stations!" << endl;
					check_int(station.work_shops);
				}
			}
			break;
		}
		case 6:
		{
			DataRecordingPipe(pipe, station);
			DataRecordingCS(pipe, station);
			break;
		}
		case 7:
		{
			DataReceivingPipe(pipe);
			DataReceivingCS(station);
			break;
		}
		case 8:
		{
			return false;
		}
		default:
		{
			cout << "Enter a number from 1 to 8!" << endl;
			break;
		}
		}
	}
}