#include <iostream>
#include <fstream>

using namespace std;

struct Truba
{
	string otmetka;
	double dlina;
	int diametr;
	bool remont;
};

struct KS
{
	string nazvan; 
	int tsekh;
	int tsekh_rab;
	char effect;
};

Truba CreateTruba()
{
	Truba tb;
	cout << "Enter pipe elevation: ";
	cin >> tb.otmetka;
	cout << "Enter pipe length: ";
	cin >> tb.dlina;
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
		<< "\tPipe length: " << tr.dlina
		<< "\tThe pipe attribute: " << tr.remont << endl;
};

void PrintKS(KS ks)
{
	cout << "Title: " << ks.nazvan
		<< "\tEnter the number of workshops: " << ks.tsekh
		<< "\tEnter the number of workshops in operation: " << ks.tsekh_rab
		<< "\tEnter efficiency: " << ks.effect << endl;
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
		Truba tr = CreateTruba();
		//PrintTruba(tr);
		main();
		break;
	}
	case 2:
	{
		KS ks = CreateKS();
		//PrintKS(ks);
		main();
		break;
	}
	case 3:
	{
		cout << "vibrano 3" << endl;
		main();
		break;
	}
	case 4:
	{
		cout << "vibrano 4" << endl;
		main();
		break;
	}
	case 5:
	{
		cout << "vibrano 5" << endl;
		main();
		break;
	}
	case 6:
	{
		cout << "vibrano 6" << endl;
		main();
		break;
	}
	case 7:
	{
		cout << "vibrano 7" << endl;
		main();
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

	return 0;
}