#pragma once
#include <unordered_map>
#include "Truba.h"
#include "CS.h"

class GTS
{
public:
	void Add_pipe(unordered_map <int, Truba>& pipes);
	void OutputPipe(unordered_map <int, Truba>& tb);
	void DownloadPipe(unordered_map <int, Truba>& pipes);
	int Filter_pipes(unordered_map <int, Truba>& tb);

	void Add_CS(unordered_map <int, CS>& pipes);
	void OutputCS(unordered_map <int, CS>& cs);
	void DownloadCS(unordered_map <int, CS>& cs);
	int Filter_CS(unordered_map <int, CS>& cs);

	void ObjectsSaving(unordered_map <int, Truba>& pipes, unordered_map <int, CS>& stations);
};