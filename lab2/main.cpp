#pragma once
#include "help.h"
#include "pipe.h"
#include "CS.h"
using namespace std;
using namespace chrono;

template <typename T>
void show_map(const unordered_map<int, T>& map)
{
	for (auto& [id, val] : map)
	{
		cout << id;
		cout << val;
	}
}

template<typename T>
void save_map(std::ofstream& fout, const std::unordered_map<int, T>& map)
{
	fout << map.size() << endl;
	for (auto& [id, val] : map)
	{
		fout << val;
	}
}

template<typename T>
void load_map(std::ifstream& fin, std::unordered_map<int, T>& map)
{
	map.clear();
	T::reset_maxID();
	int sizemap;
	fin >> sizemap;
	for (int i = 1; i <= sizemap; i++)
	{
		T val; 
		fin >> val;
		map.emplace(val.get_ID(), val);
	}
}

void save_file(const unordered_map<int, pipe>& pipemap, const unordered_map<int, CS>& csmap)
{
	cout << "Enter file name: ";
	string filename = input_string();
	ofstream fout;
	fout.open(filename, ios::out);
	if (fout)
	{
		save_map(fout, pipemap);
		save_map(fout, csmap);
		fout.close();
		cout << "Pipe saved = " << pipemap.size() << endl
			<< "CS saved = " << csmap.size() << endl;
	}
	else cout << "ERROR save" << endl;
}

void load_file(unordered_map<int, pipe>& pipemap, unordered_map<int, CS>& csmap)
{
	cout << "Enter file name: ";
	string filename = input_string();
	ifstream fin;
	fin.open(filename, ios::in);
	if (fin)
	{
		load_map(fin, pipemap);
		load_map(fin, csmap);
		fin.close();
		cout << "Pipe loaded = " << pipemap.size() << endl
			<< "CS loaded = " << csmap.size() << endl;
	}
	else
		cout << "ERROR load" << endl;
}

void cout_NoObjectFound() { cout << "No objects found :(" << endl; }

template<typename T, typename U>
using Filter = bool(*)(T& val, U param);
template<typename T>
bool find_by_name(T& val, string name)
{
	return (val.get_name().find(name) != std::string::npos);		
}
bool find_by_repair_status(pipe& p, bool status)
{
	return p.get_inrepair() == status;
}
bool find_by_WS_inwork(CS& cs, double percent)
{
	return cs.get_ws_in_use() >= percent;
}

template<typename T, typename U>
unordered_set<int> find_byfilter(unordered_map<int, T>& map, Filter<T, U> f, U param)
{
	unordered_set<int> res;
	int i = 0;
	for (auto& [id, val] : map)
	{
		if (f(val, param))
			res.emplace(id);
	}
	return res;
}

unordered_set<int> select_byfilter(unordered_map<int, pipe>& map)
{
	unordered_set<int> res;
	cout << "Choose filter:\n1. Name\n2. Repair status" << endl;
	switch (get_correct_number(1, 2))
	{
	case 1:
	{
		cout << "Enter part of name: "; 
		string name = input_string();
		res = find_byfilter(map, find_by_name, name);
		break;
	}
	case 2:
	{
		cout << "Enter status \"in repair\": "; 
		bool status = get_correct_number<int>(0, 1);
		res = find_byfilter(map, find_by_repair_status, status);
		break;
	}
	default:
		break;
	}
	return res;
}

unordered_set<int> select_byfilter(unordered_map<int, CS>& map)
{
	unordered_set<int> res;
	cout << "Choose filter:\n1. Name\n2. Percent % of ws in use" << endl;
	switch (get_correct_number(1, 2))
	{
	case 1:
	{
		cout << "Enter part of name: "; 
		string name = input_string();
		res = find_byfilter(map, find_by_name, name);
		break;
	}
	case 2:
	{
		cout << "Enter percent %: "; 
		double percent = get_correct_number<double>(0.0, 100.0);
		res = find_byfilter(map, find_by_WS_inwork, percent);
		break;
	}
	default:
		break;
	}
	return res;
}

template<typename T>
unordered_set<int> select_by_ID(unordered_map<int, T>& map, unordered_set<int>& set = {})
{
	unordered_set<int> res;
	cout << "Enter all ID\nTo stop enter 0" << endl;
	while (1)
	{
		int id = input_number<int>();
		if (id == 0)
			break;
		if (set.size() == 0)
		{
			if (map.contains(id)) res.emplace(id);
		}
		else
			if (map.contains(id) and set.contains(id)) res.emplace(id);
	}
	return res;
}
void cout_foundbyID(unordered_set<int>& set)
{
	cout << "Found objects with id: ";
	for (int id : set)
		cout << id << " ";
	cout << endl;
}

void edit_map(unordered_map<int, pipe>& map)
{
	for (auto& [id, p] : map)
		p.edit_pipe();
	if (!map.empty()) cout << "Repair status of all pipes were edited (inverted)!" << endl;
	else cout_NoObjectFound();
}

void edit_map(unordered_map<int, CS>& map)
{
	if (!map.empty()) cout << "Do you want to run or stop 1 ws for all CS?\n1. Run\n2. Stop" << endl;
	else cout_NoObjectFound();
	switch (get_correct_number(1, 2))
	{
	case 1:
	{
		for (auto& [id, cs] : map)
			if (!cs.run_WS())
				cout << "Cannot change CS " << id << endl;
		break;
	}
	case 2:
	{
		for (auto& [id, cs] : map)
			if (!cs.stop_WS())
				cout << "Cannot change CS " << id << endl;

		break;
	}
	default:
		break;
	}

	if (!map.empty()) cout << "Well done!" << endl;
	else cout_NoObjectFound();
}

template<typename T>
void edit_select(unordered_map<int, T>& map, unordered_set<int>& set)
{
	cout << "Choose what to do with selected objects:\n1. Print\n2. Edit\n3. Delete\0. Exit" << endl;
	switch (get_correct_number<int>(1, 3))
	{
	case 1:
	{
		for (int id : set)
			cout << map[id];
		break;
	}
	case 2:
	{
		edit_map(map);
		break;
	}
	case 3:
	{
		for (int id : set)
			map.erase(id);
		break;
	}
	case 0:
	{
		if (confirm("All your filters will be gone. Are you sure?"))
			break;
	}
	default:
		break;
	}
}

template<typename T>
void select_objects(unordered_map<int, T>& map)
{
	unordered_set<int> res;
	if (map.empty())
	{
		cout_NoObjectFound();
		return;
	}
	cout << "You want to select by ID or by Filter?\n1. ID\n2. Filter" << endl;
	if (get_correct_number(1, 2) == 1) //ID
		res = select_by_ID(map, res);
	else // Filter
		res = select_byfilter(map);
	if (res.size() != 0)
	{
		cout_foundbyID(res);
		cout << "You want to select ALL or by ID?\n1. ALL\n2. ID" << endl;
		if (get_correct_number(1, 2) == 2) //ID
			res = select_by_ID(map, res);
		if (res.size() != 0)
			edit_select(map, res);
		else cout_NoObjectFound();
	}
	else cout_NoObjectFound();
}

void delete_all(unordered_map<int, pipe>& pipemap, unordered_map<int, CS>& csmap)
{
	if (pipemap.empty() && csmap.empty())
	{
		cout_NoObjectFound();
		return;
	}
	if (confirm("Are you sure?"))
	{
		pipemap.clear();
		csmap.clear();
		cout << "All objects are deleted" << endl;
	}
	return;
}

int main_menu()
{
	unordered_map<int, pipe> pipemap;
	unordered_map<int, CS> csmap;

	while (1)
	{
		cout << "Menu\n"
			"1. Add pipe\n2. Add CS\n3. View all objects\n"
			"4. Edit pipes\n5. Edit CS\n"
			"6. Save\n7. Download\n8. Delete All\n"
			"0. Exit\n";
		cout << "Choose option: ";

		switch (get_correct_number(0, 8))
		{
		case 0:
		{
			cout << "Goodbye" << endl;
			return 0;
		}
		case 1:
		{
			pipe p = pipe::add_pipe();
			pipemap.emplace(p.get_ID(), p);
			break;
		}
		case 2:
		{
			CS cs = CS::add_CS();
			csmap.emplace(cs.get_ID(), cs);
			break;
		}
		case 3:
		{
			cout << "View all objects" << endl;
			if (pipemap.empty() and csmap.empty()) cout_NoObjectFound();
			else
			{
				cout << "Pipes" << endl; show_map(pipemap);
				cout << "CS" << endl; show_map(csmap);
			}
			break;
		}
		case 4:
		{
			select_objects(pipemap);
			break;
		}
		case 5:
		{
			select_objects(csmap);
			break;
		}
		case 6:
		{
			save_file(pipemap, csmap);
			break;
		}
		case 7:
		{
			load_file(pipemap, csmap);
			break;
		}
		case 8:
		{
			delete_all(pipemap, csmap);
			break;
		}
		default:
		{
			cerr << "ERROR unexpected" << endl << "Programmer forgot to use get_correct_number function" << endl;
			return 0;
		}
		}
		cout << endl;
	}
}

int main() {
	cout << "Program started!" << endl;

	redirect_output_wrapper log_redirect(cerr);
	string timestamp = std::format("{:%Y-%m-%d_%H-%M-%S}", system_clock::now());
	ofstream log_file("log_" + timestamp + ".txt");
	if (log_file)
		log_redirect.redirect(log_file);

	main_menu();

	return 0;
}
