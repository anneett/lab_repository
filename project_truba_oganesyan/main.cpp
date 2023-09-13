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

int main()
{
	/*vector <Truba> trub_group;
	size_t n = 0;
	cin >> n;
	trub_group.resize(n);*/

	Truba tr = CreateTruba();
	PrintTruba(tr);

	/*vector <KS> ks_group;
	size_t m = 0;
	cin >> m;
	ks_group.resize(m);*/

	KS ks = CreateKS();
	PrintKS(ks);

	return 0;
}