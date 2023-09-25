#include <iostream>
#include <fstream>

using namespace std;

struct Truba
{
	string otmetka = "none";
	double dlina = 0;
	int diameter = 0;
	bool remont = false;
};

struct CS
{
	string nazvan = "none";
	int tsekh = 0;
	int tsekh_rab = 0;
	char effect = 'A';
};

int proverka_int(int& chislo)
{
	cin >> chislo;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "\nEnter data of type integer!\n";
		cin >> chislo;
	}
	return chislo;
}

string proverka_str(string& stroka)
{
	cin >> stroka;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "\nEnter string data!\n";
		cin >> stroka;
	}
	return stroka;
}

double proverka_doub(double& doub)
{
	cin >> doub;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "\nEnter double data!\n";
		cin >> doub;
	}
	return doub;
}

bool proverka_bool(bool& bob)
{
	cin >> bob;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "\nEnter bool data!\n";
		cin >> bob;
	}
	return bob;
}

char proverka_char(char& symbol)
{
	cin >> symbol;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "\nEnter data of type  char!\n";
		cin >> symbol;
	}
	return symbol;
}

Truba CreateTruba()
{
	Truba tb;
	cout << "Enter pipe elevation: ";
	proverka_str(tb.otmetka);
	//cin >> tb.otmetka;
	cout << "Enter pipe length: ";
	proverka_doub(tb.dlina);
	//cin >> tb.dlina;
	cout << "Enter pipe diameter: ";
	proverka_int(tb.diameter);
	//cin >> tb.diametr;
	cout << "Enter the pipe attribute: ";
	proverka_bool(tb.remont);
	//cin >> tb.remont;
	return tb;
};

CS CreateCS()
{
	CS cc;
	cout << "Enter the title: ";
	proverka_str(cc.nazvan);
	//cin >> cc.nazvan;
	cout << "Enter the number of workshops: ";
	proverka_int(cc.tsekh);
	//cin >> cc.tsekh;
	cout << "Enter the number of workshops in operation: ";
	proverka_int(cc.tsekh_rab);
	//cin >> cc.tsekh_rab;
	cout << "Enter efficiency: ";
	proverka_char(cc.effect);
	//cin >> cc.effect;
	return cc;
};

void PrintTruba(Truba tr)
{
	cout << "Pipe elevation: " << tr.otmetka
		<< "\nPipe length: " << tr.dlina
		<< "\nPipe diameter: " << tr.diameter
		<< "\nThe pipe attribute: " << tr.remont << endl;
};

void PrintCS(CS ks)
{
	cout << "Title: " << ks.nazvan
		<< "\nEnter the number of workshops: " << ks.tsekh
		<< "\nEnter the number of workshops in operation: " << ks.tsekh_rab
		<< "\nEnter efficiency: " << ks.effect << endl;
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

		int number = 0;
		cout << "\nSelect: ";

		proverka_int(number);

		switch (number)
		{
		case 1:
		{
			pipe = CreateTruba();
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
			cout << "\nPipe" << endl;
			PrintTruba(pipe);
			cout << "\nCompressor station" << endl;
			PrintCS(station);
			break;
		}
		case 4:
		{
			cout << "Change the sign 'in repair': ";
			proverka_bool(pipe.remont);
			//cin >> pipe.remont;
			break;
		}
		case 5:
		{
			cout << "Change the number of workshops in operation: ";
			proverka_int(station.tsekh_rab);
			//cin >> station.tsekh_rab;
			break;
		}
		case 6:
		{
			cout << "Data written to file." << endl;
			ofstream fout("data");
			if (fout)
			{
				fout << pipe.otmetka << endl;
				fout << pipe.dlina << endl;
				fout << pipe.diameter << endl;
				fout << pipe.remont << endl;
				fout << station.nazvan << endl;
				fout << station.tsekh << endl;
				fout << station.tsekh_rab << endl;
				fout << station.effect << endl;
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
				fin >> pipe.otmetka;
				cout << "Pipe elevation: " << pipe.otmetka << endl;
				fin >> pipe.dlina;
				cout <<  "Pipe length: " << pipe.dlina << endl;
				fin >> pipe.diameter;
				cout << "Pipe diameter: " << pipe.diameter << endl;
				fin >> pipe.remont;
				cout <<  "The pipe attribute: " << pipe.remont << endl;
				cout << "\nCompressor station" << endl;
				fin >> station.nazvan;
				cout << "CS title: " << station.nazvan << endl;
				fin >> station.tsekh;
				cout << "Number of workshops of the CS: " << station.tsekh << endl;
				fin >> station.tsekh_rab;
				cout <<  "Number of workshops in operation of the CS: " << station.tsekh_rab << endl;
				fin >> station.effect;
				cout <<  "CS efficiency: " << station.effect << endl;
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