#include <iostream>
#include <vector>

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
	int tsekh_pab;
	char effect;
};

int main()
{
	vector <Truba> trub_group;
	size_t n = 0;
	cin >> n;
	trub_group.resize(n);

	vector <KS> ks_group;
	size_t m = 0;
	cin >> m;
	ks_group.resize(m);

	return 0;
}