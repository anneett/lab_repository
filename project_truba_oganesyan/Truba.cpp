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

istream& operator >> (istream& in, Truba& tb)
{
	cout << "Enter pipe mark: ";
	cin.ignore();
	getline(cin, tb.mark);
	//INPUT_LINE(in, tb.mark);
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
		cout << "Pipe MaxID: " << tb.max_idp
			<< "\nPipe ID: " << tb.idpipe
			<< "\nPipe mark: " << tb.mark
			<< "\nPipe length: " << tb.length
			<< "\nPipe diameter: " << tb.diameter
			<< "\nThe pipe attribute: " << tb.repair << endl;
		//PRINT_PARAM(out, tb.idpipe);
		//PRINT_PARAM(out, tb.mark);
		//PRINT_PARAM(out, tb.length);
		//PRINT_PARAM(out, tb.diameter);
		//PRINT_PARAM(out, tb.repair);
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
		fout << tb.max_idp << endl << tb.idpipe << endl << tb.mark << endl << tb.length << endl << tb.diameter << endl << tb.repair << endl;
	}
}