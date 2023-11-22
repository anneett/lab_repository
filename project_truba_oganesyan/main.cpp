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

int main()
{
	redirect_output_wrapper cerr_out(cerr);
	string time = format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now() + hours(3));
	ofstream logfile("log_" + time);
	if (logfile)
		cerr_out.redirect(logfile);

	unordered_map <int, Truba> pipes;
	unordered_map <int, CS> stations;
	GTS gts;
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
			gts.Add_pipe(pipes);
			break;
		}
		case 2:
		{
			gts.Add_CS(stations);
			break;
		}
		case 3:
		{
			gts.OutputPipe(pipes);
			gts.OutputCS(stations);
			break;
		}
		case 4:
		{
			gts.ObjectsSaving(pipes, stations);
			break;
		}
		case 5:
		{
			gts.DownloadPipe(pipes);
			gts.DownloadCS(stations);
			break;
		}
		case 6:
		{
			gts.Filter_pipes(pipes);
			break;
		}
		case 7:
		{
			gts.Filter_CS(stations);
			break;
		}
		case 0:
		{
			return false;
		}
		}
	}
}