#pragma once
#include <unordered_map>
#include <set>
#include "Truba.h"
#include "CS.h"

class GTS
{
public:
	int id_entry;
	int id_pipe;
	int id_outlet;

	void Add_pipe(unordered_map <int, Truba>& pipes);
	void OutputPipe(unordered_map <int, Truba>& tb);
	void DownloadPipe(unordered_map <int, Truba>& pipes);
	int Filter_pipes(unordered_map <int, Truba>& tb, vector<GTS>& connection, unordered_map <int, CS>& cs);

	void Add_CS(unordered_map <int, CS>& cs);
	void OutputCS(unordered_map <int, CS>& cs);
	void DownloadCS(unordered_map <int, CS>& cs);
	int Filter_CS(unordered_map <int, CS>& cs, vector<GTS>& connection, unordered_map <int, Truba>& tb);

	void ObjectsSaving(unordered_map <int, Truba>& pipes, unordered_map <int, CS>& stations);
	void Connection(unordered_map <int, Truba>& pipes, unordered_map <int, CS>& stations, vector<GTS>& connection);
	int Add_newpipe_connect(unordered_map<int, Truba>& pipe, int diameter);
	void All_connections(vector<GTS>& connection);

	void TopologicalSort(vector<GTS>& graph);
};