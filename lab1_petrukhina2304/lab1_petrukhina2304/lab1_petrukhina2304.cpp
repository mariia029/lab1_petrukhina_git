#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Pipe
{
	string pipe_name = "None";
	double pipe_length = 0.0;
	int pipe_diameter = 0;
	bool pipe_repair = false;
};

struct Station
{
	string station_name = "None";
	int station_workshops = 0;
	int station_act_workshops = 0;
	double station_efficiency = 0.0;
};

int check_int()
{
	int int_data;
	cin >> int_data;
	while (cin.fail() || cin.peek() != '\n' || int_data <= 0)
	{
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "\nPlease, enter an integer data type greater than 0\n";
		cin >> int_data;
	}
	return int_data;
}

int check_input()
{
	int input_data;
	cin >> input_data;
	while (cin.fail() || cin.peek() != '\n' || input_data < 0 || input_data > 9)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "\nError of data input! Please, try again: ";
		cin >> input_data;
	}
	return input_data;
}


double check_double()
{
	double double_data;
	cin >> double_data;
	while (cin.fail() || cin.peek() != '\n' || double_data <= 0)
	{
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "\nPlease, enter a double data type greater than 0\n";
		cin >> double_data;
	}
	return double_data;
}


double check2_double()
{
	double efficiency_data;
	cin >> efficiency_data;
	while (cin.fail() || cin.peek() != '\n' || (efficiency_data < 0.0) || (efficiency_data > 1.0))
	{
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "\nPlease, enter efficiency data from 0.0 to 1.0\n";
		cin >> efficiency_data;
	}
	return efficiency_data;
}


bool check_bool()
{
	bool bool_data;
	cin >> bool_data;
	while (cin.fail() || cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "\nPlease, enter a boolean data type\n";
		cin >> bool_data;
	}
	return bool_data;
}


Pipe AddPipe()
{
	Pipe new_pipe;
	cout << endl << "Adding a new pipe..." << endl;
	cout << "Enter the name of the pipe: ";
	cin.ignore();
	getline(cin, new_pipe.pipe_name);
	cout << "Enter the length of the pipe (in metres): ";
	new_pipe.pipe_length = check_double();
	cout << "Enter the pipe diameter (in millimetres): ";
	new_pipe.pipe_diameter = check_int();
	cout << "Enter the repair status (0 or 1): ";
	new_pipe.pipe_repair = check_bool();
	return new_pipe;
}


void PrintAddPipe(const Pipe& new_pipe)
{
	cout << endl << "Info about your pipe..." << endl;
	if (new_pipe.pipe_name == "None")
	{
		cout << "No pipes available!\n";
	}
	else
	{
		cout << "Name: " << new_pipe.pipe_name << "\tLength: " << new_pipe.pipe_length
			<< "\tDiameter: " << new_pipe.pipe_diameter << "\tRepair: " << (new_pipe.pipe_repair ? "In repair" : "Not in repair") << endl;
	}
}

Pipe RepairPipe(Pipe new_pipe)
{
	if (new_pipe.pipe_name == "None")
	{
		cout << "No pipes available!\n";
	}
	else
	{
		new_pipe.pipe_repair = !new_pipe.pipe_repair;
		cout << endl << "You have changed the repair status!";
	}
	return new_pipe;
}


Station AddStation()
{
	Station new_station;
	cout << endl << "Adding a new CS..." << endl;
	cout << "Enter the station name: ";
	cin.ignore();
	getline(cin, new_station.station_name);
	cout << "Enter the number of workshops: ";
	new_station.station_workshops = check_int();
	cout << "Enter the number of active workshops: ";
	new_station.station_act_workshops = check_int();
	while (new_station.station_act_workshops > new_station.station_workshops)
	{
		cout << "The number of active workshops cannot be greater than those available!\n";
		cout << "Enter the number of active workshops: ";
		new_station.station_act_workshops = check_int();
	}
	cout << "Enter the station efficiency indicator (from 0 to 1 with tenths): ";
	new_station.station_efficiency = check2_double();
	return new_station;
}


void PrintAddStation(const Station& new_station)
{
	cout << endl << "Info about your CS..." << endl;
	if (new_station.station_name == "None")
	{
		cout << "No stations available!\n";
	}
	else
	{
		cout << "Name: " << new_station.station_name << "\tWorkshops: " << new_station.station_workshops
			<< "\tActive workshops: " << new_station.station_act_workshops << "\tEfficiency: "
			<< new_station.station_efficiency << endl;
	}
}
Station EditStation(Station new_station)
{
	if (new_station.station_name == "None")
	{
		cout << "No stations available!\n";
	}
	else
	{
		cout << "Enter the number of active workshops: ";
		new_station.station_act_workshops = check_int();
		while (new_station.station_act_workshops > new_station.station_workshops)
		{
			cout << "The number of active workshops cannot be greater than those available!\n";
			cout << "Enter the number of active workshops: ";
			new_station.station_act_workshops = check_int();
		}
	}
	return new_station;
}


void SavePipeToFile(const Pipe& pipe_data)
{
	ofstream fout("info.txt", ios::app);  
	if (pipe_data.pipe_name != "None")
	{
		fout << "Info about your pipe...\n";
		fout << pipe_data.pipe_name << endl;
		fout << pipe_data.pipe_length << endl;
		fout << pipe_data.pipe_diameter << endl;
		fout << pipe_data.pipe_repair << endl;
		cout << "Info about the pipe is written to a file!\n";
	}
	else
	{
		cout << "Nothing to record about pipe!\n";
	}
	fout.close();
}


void SaveStationToFile(const Station& station_data)
{
	ofstream fout("info.txt", ios::app);  
	if (station_data.station_name != "None")
	{
		fout << "Info about your station...\n";
		fout << station_data.station_name << endl;
		fout << station_data.station_workshops << endl;
		fout << station_data.station_act_workshops << endl;
		fout << station_data.station_efficiency << endl;
		cout << "Info about the station is written to a file!\n";
	}
	else
	{
		cout << "Nothing to record about station!\n";
	}
	fout.close();
}

void FileOutput()
{
	ifstream fin("info.txt");
	if (!fin)
	{
		cout << "Error: File not found!" << endl;
		return;
	}

	string line;
	while (getline(fin, line))
	{
		if (line == "Info about your pipe...")
		{
			cout << "\nThe pipe data is obtained from the file!" << endl;

			string pipe_name;
			double pipe_length;
			double pipe_diameter;
			bool pipe_repair;

			getline(fin, pipe_name);
			cout << "Name of the pipe: " << pipe_name << endl;

			fin >> pipe_length;
			cout << "Length of the pipe: " << pipe_length << endl;

			fin >> pipe_diameter;
			cout << "Diameter of the pipe: " << pipe_diameter << endl;

			fin >> pipe_repair;
			cout << "Repair status of the pipe: " << (pipe_repair ? "In repair" : "Not in repair") << endl;

			fin.ignore(numeric_limits<streamsize>::max(), '\n');  
		}
		else if (line == "Info about your station...")
		{
			cout << "\nThe station data is obtained from the file!" << endl;

			string station_name;
			int station_workshops;
			int station_act_workshops;
			double station_efficiency;

			getline(fin, station_name);
			cout << "Name of the station: " << station_name << endl;

			fin >> station_workshops;
			cout << "Number of workshops: " << station_workshops << endl;

			fin >> station_act_workshops;
			cout << "Number of active workshops: " << station_act_workshops << endl;

			fin >> station_efficiency;
			cout << "Station efficiency indicator: " << station_efficiency << endl;

			fin.ignore(numeric_limits<streamsize>::max(), '\n'); 
		}
	}

	fin.close();
}


int main()
{
	
	ofstream fout("info.txt", ios::trunc);
	fout.close(); 

	Pipe pipe0;
	Station station0;
	int num = 0;

	while (true)
	{
		cout << endl << "Menu:" << endl;
		cout << "1) Add pipe" << endl;
		cout << "2) Add a station (CS)" << endl;
		cout << "3) View all objects" << endl;
		cout << "4) Edit pipe" << endl;
		cout << "5) Edit a station" << endl;
		cout << "6) Save pipe to file" << endl;
		cout << "7) Save station to file" << endl;
		cout << "8) Load and display all data from file" << endl;
		cout << "0) Exit" << endl;
		cout << endl << "Please, enter the command number: ";
		num = check_input();

		switch (num)
		{
		case 1:
			pipe0 = AddPipe();  
			break;
		case 2:
			station0 = AddStation();  
			break;
		case 3:
			PrintAddPipe(pipe0);  
			PrintAddStation(station0);  
			break;
		case 4:
			pipe0 = RepairPipe(pipe0);  
			break;
		case 5:
			station0 = EditStation(station0); 
			break;
		case 6:
			SavePipeToFile(pipe0);  
			break;
		case 7:
			SaveStationToFile(station0);  
			break;
		case 8:
			FileOutput();  
			break;
		case 0:
			return 0;
		default:
			cout << "Invalid option, try again!" << endl;
		}
	}
}