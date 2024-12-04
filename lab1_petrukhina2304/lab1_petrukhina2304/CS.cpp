#include "CS.h"
#include "help.h"
using namespace std;

int CS::MaxID = 0;

CS::CS()
{
	ID = ++MaxID;
	name = "";
	ws_work = 0;
};

ostream& operator << (ostream& out, const CS& cs)
{
	cout << "CS ID = " << cs.ID << endl;
	out << "name: " << cs.name << endl
		<< "ws: " << cs.ws << endl
		<< "ws in work: " << cs.ws_work << endl
		<< "eff: " << cs.eff << endl;

	return out;
}

istream& operator >> (istream& in, CS& cs)
{
	cout << "CS ID = " << cs.ID << endl;
	cout << "name (str): ";
	cs.name = input_string(in);
	cout << "ws (int) = ";
	cs.ws = get_positive_number<int>(in);
	cout << "ws in work (int) = ";
	cs.ws_work = get_correct_number<int>(0, cs.ws, true, in);
	cout << "eff (double) = ";
	cs.eff = get_positive_number<double>(in);

	return in;
}

ofstream& operator << (ofstream& fout, const CS& cs)
{
	fout << cs.ID << endl
		<< cs.name << endl
		<< cs.ws << endl
		<< cs.ws_work << endl
		<< cs.eff << endl;

	return fout;
}

ifstream& operator >> (ifstream& fin, CS& cs)
{
	fin >> cs.ID;
	getline(fin >> ws, cs.name);
	fin >> cs.ws;
	fin >> cs.ws_work;
	fin >> cs.eff;

	return fin;
}

CS CS::add_CS() // add new CS
{
	CS cs;
	cin >> cs;
	return cs;
}

void CS::reset_maxID()
{
	MaxID = 0;
}

bool CS::run_WS() // change number of ws in in_repair for cs
{
	if (ws_work < ws)
	{
		ws_work++;
		return 1;
	}
	else
		return 0;
}

bool CS::stop_WS() // change number of ws in in_repair for cs
{
	if (ws_work > 0)
	{
		ws_work--;
		return 1;
	}
	else
		return 0;
}