#include <iostream>
#include <fstream>

using namespace std;

struct Truba
{
	string otmetka = "none";
	double dlina = 0;
	int diametr = 0;
	bool remont = false;
};

struct KS
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
	proverka_int(tb.diametr);
	//cin >> tb.diametr;
	cout << "Enter the pipe attribute: ";
	proverka_bool(tb.remont);
	//cin >> tb.remont;
	return tb;
};

KS CreateKS()
{
	KS kc;
	cout << "Enter the title: ";
	proverka_str(kc.nazvan);
	//cin >> kc.nazvan;
	cout << "Enter the number of workshops: ";
	proverka_int(kc.tsekh);
	//cin >> kc.tsekh;
	cout << "Enter the number of workshops in operation: ";
	proverka_int(kc.tsekh_rab);
	//cin >> kc.tsekh_rab;
	cout << "Enter efficiency: ";
	proverka_char(kc.effect);
	//cin >> kc.effect;
	return kc;
};

void PrintTruba(Truba tr)
{
	cout << "Pipe elevation: " << tr.otmetka
		<< "\nPipe length: " << tr.dlina
		<< "\nPipe diameter: " << tr.diametr
		<< "\nThe pipe attribute: " << tr.remont << endl;
};

void PrintKS(KS ks)
{
	cout << "Title: " << ks.nazvan
		<< "\nEnter the number of workshops: " << ks.tsekh
		<< "\nEnter the number of workshops in operation: " << ks.tsekh_rab
		<< "\nEnter efficiency: " << ks.effect << endl;
};



int main()
{
	Truba pipe;
	KS station;
	while (true) {
		cout << "\nSelect menu item: "
			<< "\n1. Add pipe;"
			<< "\n2. Add KS;"
			<< "\n3. View all objects;"
			<< "\n4. Edit pipe;"
			<< "\n5. Edit KS;"
			<< "\n6. Save;"
			<< "\n7. Download;"
			<< "\n8. Exit." << endl;

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
			station = CreateKS();
			break;
		}
		case 3:
		{
			cout << "\nPipe" << endl;
			PrintTruba(pipe);
			cout << "\nCompressor station" << endl;
			PrintKS(station);
			break;
		}
		case 4:
		{
			cout << "\nChange the sign 'in repair': ";
			proverka_bool(pipe.remont);
			//cin >> pipe.remont;
			break;
		}
		case 5:
		{
			cout << "\nChange the number of workshops in operation: ";
			proverka_int(station.tsekh_rab);
			//cin >> station.tsekh_rab;
			break;
		}
		case 6:
		{
			cout << "vibrano 6" << endl;
			break;
		}
		case 7:
		{
			cout << "vibrano 7" << endl;
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