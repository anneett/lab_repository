#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include "Truba.h"
#include "CS.h"
#include "Utils.h"
#include "Truba_and_CS.h"

using namespace std;

//if (station.shops == 0)
//{
//	cout << "You don't have added CS." << endl;
//}
//else
//{
//	cout << "Change the number of workshops in operation: ";
//	station.work_shops = GetCorrectData(0, 1000);
//	//check_int(station.work_shops);
//	while (station.work_shops > station.shops)
//	{
//		cout << "The number of workstations cannot exceed the number of all stations!" << endl;
//		station.work_shops = GetCorrectData(0, 1000);
//		//check_int(station.work_shops);
//	}
//}

void ObjectsSaving(unordered_map <int, Truba>& pipes, unordered_map <int, CS>& stations)
{
	if (pipes.size() == 0 && stations.size() == 0)
	{
		logging_cout("You have no objects to save");
	}
	else
	{
		string filename;
		logging_cout("Enter filename: ");
		cin >> filename;
		logging_cout(filename);
		ofstream fout;
		fout.open((filename + ".txt"), ios::trunc);
		if (fout.is_open())
		{
			fout << pipes.size() << " " << stations.size() << endl;
			for (const auto& tb : pipes)
			{
				DataRecordingPipe(fout, tb.second);
				logging_cout("Data about the pipe with ID " + to_string(tb.first) + " is saved to file named " + filename + ".");
			}
			for (const auto& cs : stations)
			{
				DataRecordingCS(fout, cs.second);
				logging_cout("Data about the station with ID " + to_string(cs.first) + " is saved to file named " + filename + ".");
			}
			fout.close();
		}
		else
		{
			logging_cout("Could not open file named " + filename + ".");
		}
	}
}

int main()
{
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

		int number = -1;
		cout << "\nSelect: ";

		number = GetCorrectData(0, 7);
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