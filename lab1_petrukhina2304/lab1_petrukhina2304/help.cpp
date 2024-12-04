#include "help.h"
using namespace std;

string input_string(istream& in)
{
	string str;
	getline(in >> ws, str);

	cerr << str << endl;
	return str;
}

template <typename T> // template to check different types of variables
T input_number(istream& in) // check type
{
	T x;
	while ((in >> x).fail()	// check type
		|| in.peek() != '\n')	// is buffer empty (int/float check)
	{
		in.clear();
		in.ignore(10000, '\n');
		cout << "ERROR wrong type --> try again: ";
		cerr << x << endl;
	}
	cerr << x << endl;
	return x;
}
template int input_number(istream& in);
template double input_number(istream& in);

template <typename T = int>
T get_correct_number(T a, T b, bool included, istream& in) // check that number is in range(a,b)
{
	T x = input_number<T>(in);
	while ((included && (x<a || x>b))
		|| (!included && (x <= a || x >= b)))
	{
		string str_included = included ? "= " : " ";
		cout << "ERROR wrong number: min >" << str_included << a << " and max <" << str_included << b << " --> try again: ";
		x = input_number<T>(in);
	}
	return x;
}
template int get_correct_number<int>(int a, int b, bool included, istream& in);
template double get_correct_number<double>(double a, double b, bool included, istream& in);

template <typename T>
T get_positive_number(istream& in)
{
	return get_correct_number<T>(0, std::numeric_limits<T>::max(), false, in);
}
template int get_positive_number(istream& in);
template double get_positive_number(istream& in);

bool confirm(string message)
{
	cout << message << "\n0.no\n1.yes" << endl;
	return get_correct_number(0, 1);
}