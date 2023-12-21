#include "Truba.h"
#include "CS.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Utils.h"
#include "Truba_and_CS.h"
#include <set>
#include <stack>

using namespace std;

void GTS::Add_pipe(unordered_map <int, Truba>& pipes)
{
	Truba pipe;
	cin >> pipe;
	pipes.insert({ pipe.get_idp(), pipe });
}

void GTS::DownloadPipe(unordered_map <int, Truba>& pipes)
{
	string filename;
	cout << "Enter filename: " << endl;
	cin >> filename;
	ifstream fin;
	fin.open((filename + ".txt"));
	if (fin.is_open())
	{
		string pipe_name = "";
		bool p = 0;
		while (getline(fin, pipe_name))
		{
			if (pipe_name == "Pipe")
			{
				Truba pipe;
				cout << "Data received from file about pipe:" << endl;
				cout << "\nPipe" << endl;
				fin >> pipe.max_idp;
				cout << "Pipe MaxID: " << pipe.max_idp << endl;
				fin >> pipe.idpipe;
				cout << "Pipe ID: " << pipe.idpipe << endl;
				fin.clear();
				fin.ignore(1000, '\n');
				getline(fin, pipe.mark);
				cout << "Pipe elevation: " << pipe.mark << endl;
				fin >> pipe.length;
				cout << "Pipe length: " << pipe.length << endl;
				fin >> pipe.diameter;
				cout << "Pipe diameter: " << pipe.diameter << endl;
				fin >> pipe.repair;
				cout << "The pipe attribute: " << pipe.repair << endl;
				pipes.insert({ pipe.idpipe, pipe });
				p = 1;
			}
		}
		if (!p)
		{
			cout << "No information about pipes." << endl;
		}
		fin.close();
	}
	else
	{
		cout << "Could not open file named " + filename + " or it doesn't exist." << endl;
	}
}

void GTS::OutputPipe(unordered_map <int, Truba>& tb)
{
	if (tb.size() == 0)
	{
		cout << "You don't have a pipe to watch." << endl;
	}
	else
		cout << "Pipes:\n" << endl;
	for (auto& pipe : tb)
		cout << pipe.second << endl;
}

template <typename T>
using Filter = bool(*)(const Truba& pipe, T param);

bool CheckByName(const Truba& pipe, string param)
{
	return (pipe.mark.find(param) != string::npos);
}
bool CheckByAttribute(const Truba& pipe, bool param)
{
	return (pipe.repair == param);
}

template <typename T>
set <int> FindPipesByFilter(const unordered_map <int, Truba>& tb, Filter<T> filt, T param)
{
	set <int> ident;
	int i = 0;
	for (auto& [id, pipe] : tb)
	{
		if (filt(pipe, param))
			ident.insert(i);
		i++;
	}
	return ident;
}

void Edit_pipe(unordered_map <int, Truba>& tb, set <int>& id_filter)
{
	if ((id_filter.size()) != 0) {
		cout << "Enter number of pipes to edit. You have " + to_string(id_filter.size()) + " pipes. Enter: ";
		int number_of_pipes = GetCorrectData(0, int(id_filter.size()));
		for (int i = 1; i <= number_of_pipes; i++)
		{
			cout << "Enter ID pipe: ";
			int id = GetCorrectData(0, *max_element(id_filter.begin(), id_filter.end()));
			if (id_filter.find(id) != id_filter.end())
			{
				Truba& pipe = tb[id];
				pipe.repair = !pipe.repair;
			}
		}
	}
	else
		cout << " You do not have a pipes with this filter." << endl;
}

void Delete_pipe(unordered_map <int, Truba>& tb, set <int>& id_filter, vector<GTS>& connection, unordered_map <int, CS>& cs)
{
	if ((id_filter.size()) != 0) {
		cout << "Enter number of pipes to delete. You have " + to_string(id_filter.size()) + " pipes. Enter: ";
		int number_of_pipes = GetCorrectData(0, int(id_filter.size()));
		for (int i = 1; i <= number_of_pipes; i++)
		{
			cout << "Enter ID pipe: ";
			int id = GetCorrectData(0, *max_element(id_filter.begin(), id_filter.end()));
			if (id_filter.find(id) != id_filter.end())
			{
				tb.erase(id);
				set<int>::iterator itr = id_filter.find(id);
				id_filter.erase(itr);
				for (int i = 0; i < connection.size(); i++)
				{
					GTS connect;
					connect = connection[i];
					if (connect.id_pipe == id)
					{
						connection.erase(connection.begin() + i);
						cs[connect.id_outlet].id_output -= 1;
						cs[connect.id_entry].id_input -= 1;
					}
				}
			}
		}
	}
	else
		cout << " You do not have a pipes with this filter." << endl;
}

int Working_with_pipes(unordered_map <int, Truba>& tb, set <int>& id_filter, vector<GTS>& connection, unordered_map <int, CS>& cs)
{
	while (true)
	{
		cout << "You have " + to_string(id_filter.size()) + " pipes." << endl;
		cout << "\nChoose what you want to do:"
			<< "\n1. Edit pipe;"
			<< "\n2. Delete pipe;"
			<< "\n3. Exit." << endl;
		cout << "\nSelect: ";

		int number = GetCorrectData(1, 3);
		switch (number)
		{
		case 1:
		{
			Edit_pipe(tb, id_filter);
			break;
		}
		case 2:
		{
			Delete_pipe(tb, id_filter, connection, cs);
			break;
		}
		case 3:
		{
			return 0;
		}
		}
	}
}

int GTS::Filter_pipes(unordered_map <int, Truba>& tb, vector<GTS>& connection, unordered_map <int, CS>& cs)
{
	while (true)
	{
		cout << "\nSelect object parameter: "
			<< "\n1. Pipe name;"
			<< "\n2. 'Under repair' sign;"
			<< "\n3. All pipes."
			<< "\n4. Exit." << endl;
		cout << "\nSelect: ";

		int number = GetCorrectData(1, 4);
		switch (number)
		{
		case 1:
		{
			string pipename;
			cout << "Enter an occurrence by name: ";
			cin.ignore();
			getline(cin, pipename);
			set <int> id1_filter;
			id1_filter = FindPipesByFilter(tb, CheckByName, pipename);
			Working_with_pipes(tb, id1_filter, connection, cs);
			break;
		}
		case 2:
		{
			bool repairpipe;
			cout << "Enter an occurrence by attribute: ";
			cin >> repairpipe;
			set <int> id2_filter;
			id2_filter = FindPipesByFilter(tb, CheckByAttribute, repairpipe);
			Working_with_pipes(tb, id2_filter, connection, cs);
			break;
		}
		case 3:
		{
			set <int> id3_filter;
			for (auto& pipe_case3 : tb)
			{
				id3_filter.insert(pipe_case3.first);
			}
			Working_with_pipes(tb, id3_filter, connection, cs);
			break;
		}
		case 4:
		{
			return 0;
		}
		}
	}
}

void GTS::Add_CS(unordered_map <int, CS>& stations)
{
	CS station;
	cin >> station;
	stations.insert({ station.get_ids(), station });
}

void GTS::OutputCS(unordered_map <int, CS>& cs)
{
	if (cs.size() == 0)
	{
		cout << "You don't have a CS to watch." << endl;
	}
	else
		cout << "Compressor stations:\n" << endl;
	for (auto& station : cs)
		cout << station.second << endl;
}

void GTS::DownloadCS(unordered_map <int, CS>& stations)
{
	string filename;
	cout << "Enter filename: " << endl;
	cin >> filename;
	ifstream fin;
	fin.open((filename + ".txt"));
	if (fin.is_open())
	{
		string cs_name = "";
		bool s = 0;
		while (getline(fin, cs_name))
		{
			if (cs_name == "CS")
			{
				CS station;
				cout << "Data received from file about CS:" << endl;
				cout << "\nCompressor station" << endl;
				fin >> station.max_ids;
				cout << "CS ID: " << station.max_ids << endl;
				fin >> station.idcs;
				cout << "CS ID: " << station.idcs << endl;
				fin.clear();
				fin.ignore(1000, '\n');
				getline(fin, station.name);
				cout << "CS title: " << station.name << endl;
				fin >> station.shops;
				cout << "Number of workshops of the CS: " << station.shops << endl;
				fin >> station.work_shops;
				cout << "Number of workshops in operation of the CS: " << station.work_shops << endl;
				fin >> station.efficiency;
				cout << "CS efficiency: " << station.efficiency << endl;
				stations.insert({ station.idcs, station });
				s = 1;
			}
		}
		if (!s)
		{
			cout << "No information about stations." << endl;
		}
		fin.close();
	}
	else
	{
		cout << "Could not open file named " + filename + " or it doesn't exist." << endl;
	}
}

template <typename T>
using Filter1 = bool(*)(const CS& cs, T param);

bool CheckByName(const CS& cs, string param)
{
	return (cs.name.find(param) != string::npos);
}
bool CheckByMore(const CS& cs, int param)
{
	return (((cs.shops - cs.work_shops) * 100 / cs.shops) > param);
}
bool CheckByLess(const CS& cs, int param)
{
	return (((cs.shops - cs.work_shops) * 100 / cs.shops) < param);
}
bool CheckByEqual(const CS& cs, int param)
{
	return (((cs.shops - cs.work_shops) * 100 / cs.shops) == param);
}

template <typename T>
set <int> FindCSByFilter(const unordered_map <int, CS>& cs, Filter1<T> filt, T param)
{
	set <int> ident;
	int i = 0;
	for (auto& [id, station] : cs)
	{
		if (filt(station, param))
			ident.insert(i);
		i++;
	}return ident;
}

void Edit_CS(unordered_map <int, CS>& cs, set <int>& id_filter)
{
	if ((id_filter.size()) != 0) {
		cout << "Enter number of CS to edit. You have " + to_string(id_filter.size()) + " CS. Enter: ";
		int number_of_cs = GetCorrectData(0, int(id_filter.size()));
		for (int i = 1; i <= number_of_cs; i++)
		{
			cout << "Enter ID station: ";
			int id = GetCorrectData(0, *max_element(id_filter.begin(), id_filter.end()));
			if (id_filter.find(id) != id_filter.end())
			{
				CS& cstation = cs[id];
				cout << "Change the number of workshops in operation: ";
				cstation.work_shops = GetCorrectData(0, 1000);
				while (cstation.work_shops > cstation.shops)
				{
					cout << "The number of workshops cannot exceed the number of all shops!" << endl;
					cstation.work_shops = GetCorrectData(0, 1000);
				}
			}
		}
	}
	else
		cout << "You do not have a CS with this filter." << endl;
}

void Delete_CS(unordered_map <int, CS>& cs, set <int>& id_filter, vector<GTS>& connection, unordered_map <int, Truba>& tb)
{
	if ((id_filter.size()) != 0) {
		cout << "Enter number of CS to delete. You have " + to_string(id_filter.size()) + " CS. Enter: ";
		int number_of_cs = GetCorrectData(0, int(id_filter.size()));
		for (int i = 1; i <= number_of_cs; i++)
		{
			cout << "Enter ID station: ";
			int id = GetCorrectData(0, *max_element(id_filter.begin(), id_filter.end()));
			if (id_filter.find(id) != id_filter.end())
			{
				cs.erase(id);
				set <int>::iterator itr = id_filter.find(id);
				id_filter.erase(itr);
				for (int i = 0; i < connection.size(); i++)
				{
					GTS connect;
					connect = connection[i];
					if (connect.id_entry == id)
					{
						connection.erase(connection.begin() + i);
						cs[connect.id_outlet].id_output -= 1;
						tb[connect.id_pipe].free = 1;
					}
					if (connect.id_outlet == id)
					{
						connection.erase(connection.begin() + i);
						cs[connect.id_entry].id_input -= 1;
						tb[connect.id_pipe].free = 1;
					}
				}
			}
		}
	}
	else
		cout << " You do not have a CS with this filter." << endl;
}

int Working_with_CS(unordered_map <int, CS>& cs, set <int>& id_filter, vector<GTS>& connection, unordered_map <int, Truba>& tb)
{
	while (true)
	{
		cout << "You have " + to_string(id_filter.size()) + " CS." << endl;
		cout << "\nChoose what you want to do:"
			<< "\n1. Edit stations;"
			<< "\n2. Delete stations;"
			<< "\n3. Exit." << endl;
		cout << "\nSelect: ";

		int number = GetCorrectData(1, 3);
		switch (number)
		{
		case 1:
		{
			Edit_CS(cs, id_filter);
			break;
		}
		case 2:
		{
			Delete_CS(cs, id_filter, connection, tb);
			break;
		}
		case 3:
		{
			return 0;
		}
		}
	}
}

int GTS::Filter_CS(unordered_map <int, CS>& cs, vector<GTS>& connection, unordered_map <int, Truba>& tb)
{
	while (true)
	{
		cout << "\nSelect object parameter: "
			<< "\n1. Station name;"
			<< "\n2. Percentage of idle workshops;"
			<< "\n3. All stations."
			<< "\n4. Exit." << endl;
		cout << "\nSelect: ";

		int number = GetCorrectData(1, 4);
		switch (number)
		{
		case 1:
		{
			string csname;
			cout << "Enter an occurrence by name: ";
			cin.ignore();
			getline(cin, csname);
			set <int> id1_filter;
			id1_filter = FindCSByFilter(cs, CheckByName, csname);
			Working_with_CS(cs, id1_filter, connection, tb);
			break;
		}
		case 2:
		{
			cout << "Enter an occurrence by percentage of idle workshops: ";
			int percent = GetCorrectData(0, 100);
			set <int> id2_filter;
			cout << "\nSelect comparison option: ";
			cout << "\n1. More;"
				<< "\n2. Less;"
				<< "\n3. Equals." << endl;
			cout << "\nSelect: ";
			int choice = GetCorrectData(1, 3);
			switch (choice)
			{
			case 1:
			{
				id2_filter = FindCSByFilter(cs, CheckByMore, percent);
				break;
			}
			case 2:
			{
				id2_filter = FindCSByFilter(cs, CheckByLess, percent);
				break;
			}
			case 3:
			{
				id2_filter = FindCSByFilter(cs, CheckByEqual, percent);
				break;
			}
			}
			Working_with_CS(cs, id2_filter, connection, tb);
			break;
		}
		case 3:
		{
			set <int> id3_filter;
			for (auto& cs_case3 : cs)
			{
				id3_filter.insert(cs_case3.first);
			}
			Working_with_CS(cs, id3_filter, connection, tb);
			break;
		}
		case 4:
		{
			return 0;
		}
		}
	}
}

void GTS::ObjectsSaving(unordered_map <int, Truba>& pipes, unordered_map <int, CS>& stations)
{
	if (pipes.size() == 0 && stations.size() == 0)
	{
		cout << "You have no objects to save" << endl;
	}
	else
	{
		string filename;
		cout << "Enter filename: ";
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

void GTS::Connection(unordered_map <int, Truba>& pipes, unordered_map <int, CS>& stations, vector<GTS>& connection)
{
	if (stations.size() == 0)
	{
		cout << "You don't have any CS.";
		return;
	}
	if (pipes.size() == 0)
	{
		cout << "You don't have any pipes.";
		return;
	}
	int k = 0;
	vector <int> free_cs;
	for (auto& [id, station] : stations)
	{
		if (station.id_input + station.id_output < 2)
		{
			k += 1;
			free_cs.push_back(id);
		}
	}
	if (k < 2)
	{
		cout << "You don't have any free CS.";
		return;
	}
	int n = 0;
	vector <int> free_pipes;
	for (auto& [id, pipe] : pipes)
	{
		if (pipe.free)
		{
			n += 1;
			free_pipes.push_back(id);
		}
	}
	if (n < 1)
	{
		cout << "You don't have any free pipes.";
		return;
	}

	GTS pipe_connect;
	cout << "Entry the ID of entry CS: ";
	cin >> pipe_connect.id_entry;
	if (find(free_cs.begin(), free_cs.end(), pipe_connect.id_entry) == free_cs.end())
	{
		while (true)
		{
			cout << "There is no such ID, please enter it again: ";
			cin >> pipe_connect.id_entry;
			if (find(free_cs.begin(), free_cs.end(), pipe_connect.id_entry) != free_cs.end())
			{
				stations[pipe_connect.id_entry].id_input += 1;
				break;
			}
		}
	}
	else stations[pipe_connect.id_entry].id_input += 1;
	cout << "Entry the ID of outlet CS: ";
	cin >> pipe_connect.id_outlet;
	if (find(free_cs.begin(), free_cs.end(), pipe_connect.id_outlet) == free_cs.end() || (pipe_connect.id_outlet == pipe_connect.id_entry))
	{
		while (true)
		{
			cout << "There is no such ID, please enter it again: ";
			cin >> pipe_connect.id_outlet;
			if (find(free_cs.begin(), free_cs.end(), pipe_connect.id_outlet) != free_cs.end() && (pipe_connect.id_outlet != pipe_connect.id_entry))
			{
				stations[pipe_connect.id_outlet].id_output += 1;
				break;
			}
		}
	}
	else stations[pipe_connect.id_outlet].id_output += 1;
	int i = 0;
	int pipe_diameter;
	while (true)
	{
		cout << "Enter the diameter of the pipe you want to use (500, 700, 1000, 1400): ";
		while (true)
		{
			pipe_diameter = GetCorrectData(500, 1400);
			if (pipe_diameter != 500 && pipe_diameter != 700 && pipe_diameter != 1000 && pipe_diameter != 1400)
			{
				cout << "Enter the diameter 500, 700, 1000 or 1400! Enter: ";
			}
			else break;
		}
		for (auto& id_pip : free_pipes)
		{
			if (pipes[id_pip].diameter == pipe_diameter)
			{
				pipe_connect.id_pipe = id_pip;
				i += 1;
				pipes[id_pip].free = 0;
				break;
			}
		}
		if (i == 1) 
		{
			connection.push_back(pipe_connect);
			break;
		}
		else
		{
			cout << "There is no free pipe with this diameter. ";
			int new_id_pipe = Add_newpipe_connect(pipes, pipe_diameter);
			pipe_connect.id_pipe = new_id_pipe;
			pipes[new_id_pipe].free = 0;
			connection.push_back(pipe_connect);
			break;
		}
	}
}

int GTS::Add_newpipe_connect(unordered_map<int, Truba>& pipe, int diameter)
{
	cout << "Despite the entered diameter, the one that was missing will be installed." << endl;
	Truba tr;
	cin >> tr;
	tr.diameter = diameter;
	int new_pipe_id = tr.get_idp();
	pipe.insert({ new_pipe_id, tr });
	return new_pipe_id;
}

void GTS::All_connections(vector<GTS>& connection)
{
	cout << "All connections: " << endl;
	cout << "ID entry  ID pipe  ID oulet" << endl;
	if (connection.size() == 0)
	{
		cout << "You don't have a connections to watch." << endl;
	}
	else
	{
		for (auto& i : connection)
		{
			cout << "\t" << i.id_entry << "  \t" << i.id_pipe << "  \t" << i.id_outlet << endl;
		}
	}
}

bool isCyclicUtil(int v, vector<GTS>& graph, vector<bool>& visited, vector<bool>& recStack) {
	if (!visited[v]) {
		visited[v] = true;
		recStack[v] = true;

		for (auto edge : graph) {
			if (edge.id_entry == v) {
				int i = edge.id_outlet;
				if (!visited[i] && isCyclicUtil(i, graph, visited, recStack))
					return true;
				else if (recStack[i])
					return true;
			}
		}
	}

	recStack[v] = false;
	return false;
}

bool isCyclic(vector<GTS>& graph, int n) {
	vector<bool> visited(n, false);
	vector<bool> recStack(n, false);

	for (int v = 0; v < n; v++) {
		if (isCyclicUtil(v, graph, visited, recStack))
			return true;
	}

	return false;
}

void topologicalSortUtil(int v, vector<GTS>& graph, vector<bool>& visited, stack<int>& stack) {
	visited[v] = true;
	for (auto edge : graph) {
		if (edge.id_entry == v) {
			int i = edge.id_outlet;
			if (!visited[i])
				topologicalSortUtil(i, graph, visited, stack);
		}
	}
	stack.push(v);
}

void GTS::TopologicalSort(vector<GTS>& graph) {
	if (graph.size() == 0)
	{
		cout << "You have no connections." << endl;
		return;
	}
	set<int>vertex;
	for (auto& edge : graph)
	{
		vertex.insert(edge.id_entry);
		vertex.insert(edge.id_outlet);
	}
	int n = vertex.size();

	vector<bool> visited(n, false);
	stack<int> stack;

	for (int v = 0; v < n; v++) {
		if (!visited[v])
			topologicalSortUtil(v, graph, visited, stack);
	}

	vector<int> result;
	while (!stack.empty()) {
		result.push_back(stack.top());
		stack.pop();
	}

	if (isCyclic(graph, n)) {
		cout << "Graph contains a cycle.\n";
	}
	else {
		cout << "Topologically sorted list of vertices: ";
		for (int v : result) {
			cout << v << " ";
		}
		cout << endl;
	}

}

void GTS::dijkstra(unordered_map<int, Truba>& pipe, vector<GTS>& graph, unordered_map<int, CS>& ks)
{
	if (graph.size() == 0)
	{
		cout << "You have no connections." << endl;
		return;
	}

	set<int>vertexes;
	for (auto& edge : graph)
	{
		vertexes.insert(edge.id_entry);
		vertexes.insert(edge.id_outlet);
	}

	int start_vertex;
	int end_vertex;

	cout << "Enter CS from which you want to find the shortest path: ";
	cin >> start_vertex;

	if (find(vertexes.begin(), vertexes.end(), start_vertex) == vertexes.end())
	{
		while (true)
		{
			cout << "There is no such ID, please enter it again: ";
			cin >> start_vertex;
			if (find(vertexes.begin(), vertexes.end(), start_vertex) != vertexes.end())
			{
				break;
			}
		}
	}

	cout << "Enter the cs you want to find the shortest path to: ";
	cin >> end_vertex;

	if (find(vertexes.begin(), vertexes.end(), end_vertex) == vertexes.end())
	{
		while (true)
		{
			cout << "There is no such ID, please enter it again: ";
			cin >> end_vertex;
			if (find(vertexes.begin(), vertexes.end(), start_vertex) != vertexes.end())
			{
				break;
			}
		}
	}

	for (const auto& vertex : vertexes) {
		ks[vertex].shortest_path = std::numeric_limits<int>::max();
	}

	ks[start_vertex].shortest_path = 0;

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
	pq.push({ 0, start_vertex });

	while (!pq.empty()) {
		int current_vertex = pq.top().second;
		int current_distance = pq.top().first;
		pq.pop();

		if (current_vertex == end_vertex) {
			break;
		}

		for (const auto& edge : graph) {
			if (edge.id_entry == current_vertex) {
				int neighbor_vertex = edge.id_outlet;
				const Truba& truba = pipe[edge.id_pipe];
				int new_distance = current_distance + truba.length;

				if (new_distance < ks[neighbor_vertex].shortest_path) {
					ks[neighbor_vertex].shortest_path = new_distance;
					pq.push({ new_distance, neighbor_vertex });
				}
			}
		}
	}

	cout << "Shortest path from " << start_vertex << " to " << end_vertex << ": " << ks[end_vertex].shortest_path << endl;
}