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
	//redirect_output_wrapper cerr_out(cerr);
	//string time = format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now() + hours(3));
	//ofstream logfile("log_" + time);
	//if (logfile)
	//	cerr_out.redirect(logfile);

	unordered_map <int, Truba> pipes;
	unordered_map <int, CS> stations;
	GTS gts;
	vector<GTS> connection;
	while (true) {
		cout << "\nSelect menu item: "
			<< "\n1. Add pipe;"
			<< "\n2. Add compressor station;"
			<< "\n3. View all objects and connections;"
			<< "\n4. Save objects;"
			<< "\n5. Download objects;"
			<< "\n6. Filter: working with pipes;"
			<< "\n7. Filter: working with stations;"
			<< "\n8. Connect into a graph;"
			<< "\n9. Perform topological sort;"
			<< "\n10. Find the shortest path;"
			<< "\n11. Find the maximum flow;"
			<< "\n0. Exit." << endl;
		cout << "\nSelect: ";

		int number = GetCorrectData(0, 11);
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
			gts.All_connections(connection);
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
			gts.Filter_pipes(pipes, connection, stations);
			break;
		}
		case 7:
		{
			gts.Filter_CS(stations, connection, pipes);
			break;
		}
		case 8:
		{
			gts.Connection(pipes, stations, connection);
			break;
		}
		case 9:
		{
			gts.TopologicalSort(connection, stations);
			break;
		}
		case 10:
		{
			gts.dijkstra(pipes, connection, stations);
			break;
		}
		case 11:
		{
			gts.fordFulkerson(connection, pipes, stations);
			break;
		}
		case 0:
		{
			return false;
		}
		}
	}
}