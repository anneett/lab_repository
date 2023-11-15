#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include "Truba.h"
#include "CS.h"
#include "Utils.h"
#include "Truba_and_CS.h"
#include <chrono>
#include <format>

using namespace std;
using namespace chrono;

void ObjectsSaving(unordered_map <int, Truba>& pipes, unordered_map <int, CS>& stations)
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

int main()
{
	redirect_output_wrapper cerr_out(cerr);
	string time = format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now());
	ofstream logfile("log_" + time);
	if (logfile)
		cerr_out.redirect(logfile);
	unordered_map <int, Truba> pipes;
	unordered_map <int, CS> stations;
	while (true) {
		cout << "\nSelect menu item: "
			<< "\n1. Add pipe;"
			<< "\n2. Add compressor station;"
			<< "\n3. View all objects;"
			<< "\n4. Save objects;"
			<< "\n5. Download objects;"
			<< "\n6. Filter: working with pipes;"
			<< "\n7. Filter: working with stations;"
			<< "\n0. Exit." << endl;
		cout << "\nSelect: ";

		int number = GetCorrectData(0, 7);
		switch (number)
		{
		case 1:
		{
			Add_pipe(pipes);
			break;
		}
		case 2:
		{
			Add_CS(stations);
			break;
		}
		case 3:
		{
			OutputPipe(pipes);
			OutputCS(stations);
			break;
		}
		case 4:
		{
			ObjectsSaving(pipes, stations);
			break;
		}
		case 5:
		{
			DownloadPipe(pipes);
			DownloadCS(stations);
			break;
		}
		case 6:
		{
			Filter_pipes(pipes);
			break;
		}
		case 7:
		{
			Filter_CS(stations);
			break;
		}
		case 0:
		{
			return false;
		}
		}
	}
}