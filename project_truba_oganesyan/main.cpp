#include <iostream>
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

int check_int(int& digit)
{
	cin >> digit;
	while (cin.fail() || cin.peek() != '\n' || digit <= 0)
	{
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "\nEnter data of type integer greater then 0!\n";
		cin >> digit;
	}
	return digit;
}

int check_case(int& digit_case)
{
	cin >> digit_case;
	while (cin.fail() || cin.peek() != '\n' || digit_case < 0 || digit_case > 7)
	{
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "\nEnter a number from 0 to 7!\n";
		cin >> digit_case;
	}
	return digit_case;
}

double check_doub(double& dual)
{
	cin >> dual;
	while (cin.fail() || cin.peek() != '\n' || dual <= 0)
	{
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "\nEnter double data greater then 0!!\n";
		cin >> dual;
	}
	return dual;
}

bool check_bool(bool& boolean)
{
	cin >> boolean;
	while (cin.fail() || cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "\nEnter bool data!\n";
		cin >> boolean;
	}
	return boolean;
}

char check_char(char& symbol)
{
	cin >> symbol;
	while (cin.fail() || cin.peek() != '\n' || (symbol < 'A') || (symbol > 'F'))
	{
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "\nEnter data of type char from 'A' to 'F'!\n";
		cin >> symbol;
	}
	return symbol;
}

Truba CreatePipe()
{
	Truba tb;
	cout << "Enter pipe elevation: ";
	cin >> (tb.mark);
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
	cin >> (cs.name);
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

void PrintTruba(Truba tb)
{
	if (tb.mark == "None")
	{
		cout << "\nNo pipes added." << endl;
	}
	else
	{
		cout << "\nPipe" << endl;
		cout << "Pipe elevation: " << tb.mark
			<< "\nPipe length: " << tb.length
			<< "\nPipe diameter: " << tb.diameter
			<< "\nThe pipe attribute: " << tb.repair << endl;
	}
};

void PrintCS(CS cs)
{
	if (cs.name == "None")
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
			<< "\n0. Exit." << endl;

		int number = -1;
		cout << "\nSelect: ";

		check_case(number);

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
			PrintTruba(pipe);
			PrintCS(station);
			break;
		}
		case 4:
		{
			if (pipe.mark == "None")
			{
				cout << "You don't have added pipe" << endl;
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
			if (station.name == "None" )
			{
				cout << "You don't have added CS" << endl;
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
			cout << "Data written to file." << endl;
			ofstream fout("data");
			if (fout)
			{
				fout << pipe.mark << endl;
				fout << pipe.length << endl;
				fout << pipe.diameter << endl;
				fout << pipe.repair << endl;
				fout << station.name << endl;
				fout << station.shops << endl;
				fout << station.work_shops << endl;
				fout << station.efficiency << endl;
				fout.close();
			}
			break;
		}
		case 7:
		{
			cout << "Data received from file:\n" << endl;
			ifstream fin("data");
			if (fin)
			{
				cout << "Pipe" << endl;
				fin >> pipe.mark;
				cout << "Pipe elevation: " << pipe.mark << endl;
				fin >> pipe.length;
				cout <<  "Pipe length: " << pipe.length << endl;
				fin >> pipe.diameter;
				cout << "Pipe diameter: " << pipe.diameter << endl;
				fin >> pipe.repair;
				cout <<  "The pipe attribute: " << pipe.repair << endl;
				cout << "\nCompressor station" << endl;
				fin >> station.name;
				cout << "CS title: " << station.name << endl;
				fin >> station.shops;
				cout << "Number of workshops of the CS: " << station.shops << endl;
				fin >> station.work_shops;
				cout <<  "Number of workshops in operation of the CS: " << station.work_shops << endl;
				fin >> station.efficiency;
				cout <<  "CS efficiency: " << station.efficiency << endl;
				fin.close();
			}
			break;
		}
		case 0:
		{
			return false;
		}
		default:
		{
			cout << "Enter a number from 0 to 7!" << endl;
			break;
		}
		}
	}
}