#include "pipe.h"
#include "help.h"
using namespace std;

int pipe::MaxID = 0;

pipe::pipe()
{
	ID = ++MaxID;
	name = "";
	in_repair = 0;
};

ostream& operator<<(std::ostream& out, const pipe& p)
{
	cout << "pipe ID = " << p.ID << endl;
	out << "name: " << p.name << endl
		<< "d: " << p.d << endl
		<< "l: " << p.l << endl
		<< "in_repair status: " << p.in_repair << endl;

	return out;
}

istream& operator>>(istream& in, pipe& p)
{
	cout << "pipe ID = " << p.ID << endl;
	cout << "name (str) = ";
	p.name = input_string(in);
	cout << "d (int) = ";
	p.d = get_positive_number<int>(in);
	cout << "l (double) = ";
	p.l = get_positive_number<double>(in);
	cout << "in_repair status: 0 (ready for use)" << endl;

	return in;
}

ofstream& operator << (ofstream& fout, const pipe& p)
{
	fout << p.ID << endl
		<< p.name << endl
		<< p.d << endl
		<< p.l << endl
		<< p.in_repair << endl;;

	return fout;
}

ifstream& operator >> (ifstream& fin, pipe& p)
{
	fin >> p.ID;
	getline(fin >> ws, p.name);
	fin >> p.d;
	fin >> p.l;
	fin >> p.in_repair;

	return fin;
}

pipe pipe::add_pipe()
{
	pipe p;
	cin >> p;
	return p;
}

void pipe::reset_maxID()
{
	MaxID = 0;
}

void pipe::edit_pipe()
{
	in_repair = !in_repair;
}