#pragma once
#pragma once
#include <iostream>
#include <string>
#include <fstream>

class CS
{
private:
	static int MaxID;
	int ID;
	std::string name;
	int ws; // workstations 
	int ws_work; // // workstations in work
	double eff; //efficienty;

public:
	CS();

	static CS add_CS();
	static void reset_maxID();

	friend std::ostream& operator << (std::ostream& out, const CS& cs);
	friend std::istream& operator >> (std::istream& in, CS& cs);
	friend std::ofstream& operator << (std::ofstream& fout, const CS& cs);
	friend std::ifstream& operator >> (std::ifstream& fin, CS& cs);

	bool run_WS();
	bool stop_WS();

	int get_ID()
	{
		return ID;
	}
	std::string get_name()
	{
		return name;
	}
	double get_ws_in_use()
	{
		return (double)ws_work / ws * 100;
	}
};
#pragma once
