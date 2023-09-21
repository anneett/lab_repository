#include <iostream>
#include <fstream>

using namespace std;

struct Truba
{
	string otmetka = "0 km";
	double dlina = 0;
	int diametr = 0;
	bool remont = false;
};

struct KS
{
	string nazvan = "no";
	int tsekh = 0;
	int tsekh_rab = 0;
	char effect = 'A';
};

Truba CreateTruba()
{
	Truba tb;
	cout << "Enter pipe elevation: ";
	cin >> tb.otmetka;
	cout << "Enter pipe length: ";
	cin >> tb.dlina;
	cout << "Enter pipe diameter: ";
	cin >> tb.diametr;
	cout << "Enter the pipe attribute: ";
	cin >> tb.remont;
	return tb;
};

KS CreateKS()
{
	KS kc;
	cout << "Enter the title: ";
	cin >> kc.nazvan;
	cout << "Enter the number of workshops: ";
	cin >> kc.tsekh;
	cout << "Enter the number of workshops in operation: ";
	cin >> kc.tsekh_rab;
	cout << "Enter efficiency: ";
	cin >> kc.effect;
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

//int selection()
//{
//	int number = 0;
//	cout << "Select: ";
//	cin >> number;
//	while (cin.fail())
//	{
//		cin.clear();
//		cin.ignore(1000, '\n');
//		cout << "Try again\n";
//		cin >> number;
//	}
//	return number;
//}

int main()
{
	Truba pipe;
	KS station;
	while (true) {
		cout << "Select menu item: "
			<< "\n1. Add pipe;"
			<< "\n2. Add KS;"
			<< "\n3. View all objects;"
			<< "\n4. Edit pipe;"
			<< "\n5. Edit KS;"
			<< "\n6. Save;"
			<< "\n7. Download;"
			<< "\n8. Exit." << endl;

		int number = 0;
		cout << "Select: ";
		cin >> number;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Try again\n";
			cin >> number;
		}

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
			cout << "vibrano 3" << endl;
			PrintTruba(pipe);
			PrintKS(station);
			break;
		}
		case 4:
		{
			cout << "vibrano 4" << endl;
			break;
		}
		case 5:
		{
			cout << "vibrano 5" << endl;
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
		case 8:
		{
			cout << "vixod" << endl;
			break;
		}
		default:
		{
			cout << "Enter a number from 1 to 8!" << endl;
			break;
		}
		}
	}
}