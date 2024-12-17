#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
#include "CS3.h"
#include "utilities.h"

using namespace std;


int CS::current_csID = 0;


CS::CS() {
    cout << "---add compressor station---\n";

    this->id = ++CS::current_csID;
    cout << "id: " << this->id << endl;

    cout << "name: ";
    INPUT_LINE(cin, this->name);

    cout << "number of workshops: ";
    this->number_of_workshops = GetCorrectNumber<int, std::vector<int>>("number of workshops: ", { 1, 10000 }, IsInRange);

    cout << "workshops in work: ";
    this->workshops_in_work = GetCorrectNumber<int, std::vector<int>>("workshops in work: ", { 0, this->number_of_workshops }, IsInRange);

    cout << "workload: ";
    calc_workload();
    cout << PRINT_WORKLOAD(this->) << endl;

    cout << "Comperssor Station is created!\n";

    cout << "----------------------------\n";
}


CS::CS(std::ifstream& file) {
    file >> this->id;
    file.ignore(10000, '\n');
    getline(file >> std::ws, this->name);
    file >> this->number_of_workshops;
    file >> this->workshops_in_work;
    this->calc_workload();
    file.ignore(10000, '\n');
    this->set_links(file, 0);
    this->set_links(file, 1);
}


int CS::get_currentId() {
    return CS::current_csID;
}


void CS::set_currentID(const std::unordered_map<int, CS>& data) {
    CS::current_csID = get_maxKey(data);
}


int CS::get_id() const {
    return this->id;
}


std::string CS::get_name() const {
    return this->name;
}


bool CS::InUse() const {
    return (this->links[0].size()) || (this->links[1].size());
}


std::vector<std::unordered_set<int>> CS::get_links() const {
    return this->links;
}


void CS::set_links(std::ifstream& file, const int& pos) {
    string line;
    getline(file >> std::ws, line);
    istringstream iss(line);
    int id;
    while (iss >> id)
        if (id)
            this->links[pos].emplace(id);
    file.clear();
}


bool CS::addLink(const int& pos, const int& id) {
    this->links[pos].emplace(id);
    return 1;
}


bool CS::delLink(const int& pos, const int& id) {
    this->links[pos].erase(id);
    return 1;
}


void CS::clear_currentID() {
    CS::current_csID = 1;
}


float CS::get_workload() const {
    return this->workload;
}

ostream& operator << (ostream& os, const CS& cs) {
    os << "-----Compressor Station " << cs.get_id() << "-----" << endl
        << "id: " << cs.get_id() << endl
        << "name: " << cs.name << endl
        << "number of workshops: " << cs.number_of_workshops << endl
        << "workshops in work: " << cs.workshops_in_work << endl
        << "efficiency: " << PRINT_WORKLOAD(cs.) << endl;
    os << "links{" << endl;
    os << "   " << "in: ";
    for (const auto& id : cs.links[0]) os << id << " ";
    os << endl;
    os << "   " << "out: ";
    for (const auto& id : cs.links[1]) os << id << " ";
    os << endl;
    os << "}" << endl;
    os << "--------------" << endl;

    return os;
}


void CS::calc_workload() {
    this->workload = (float)this->workshops_in_work / this->number_of_workshops;
}


void CS::edit_workshop_status(int choice) {
    if (choice == 1) {
        if (this->workshops_in_work > 0) {
            --this->workshops_in_work;
        };
    }
    else {
        if (this->workshops_in_work < this->number_of_workshops) {
            ++this->workshops_in_work;
        };
    };
    this->calc_workload();
}


void CS::save(ofstream& file) const {
    file << "CS" << endl;
    file << this->id << endl;
    file << this->name << endl;
    file << this->number_of_workshops << endl;
    file << this->workshops_in_work << endl;
    if (this->links[0].size())
        for (const auto& id : this->links[0]) file << id << " ";
    else file << 0;
    file << endl;
    if (this->links[1].size())
        for (const auto& id : this->links[1]) file << id << " ";
    else file << 0;
    file << endl;
    file << PRINT_WORKLOAD(this->) << endl;
}