#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//структуры
struct Pipe
{
    string Name; //название трубы
    float length; //километры 
    int diameter; //миллиметры
    bool repair; //признак "в ремонте" 
};

struct Station
{
    string Name; //название КС
    int workshops; //Кол-во цехов
    int workshopsinwork; //Кол-во цехов в работе
    int effectiveness; //Коэфф. эффективности
};

//Функции
int check_int(int max, int low) {
    int z;
    cin >> z;
    cin.ignore();
    while (true) {
        if (cin.fail()) {
            cout << "Error. Not an integer or a character is entered! Try again: ";
            cin.clear();
            while (cin.get() != '\n');
        }
        else if (z < low) {
            cout << "Error. A negative number or zero is entered! Try again: ";
        }
        else if (max != 0 && z > max) {
            cout << "Error. A number greater than the maximum has been entered! Try again: ";
        }
        else {
            break;
        }
        cin >> z;
        cin.ignore();
    }
    return z;
}

float floatcheck(int max, float low) {
    float z;
    cin >> z;
    cin.ignore();
    while (true) {
        if (cin.fail()) {
            cout << "Error. Not an integer or a character is entered! Try again: ";
            cin.clear();
            while (cin.get() != '\n');
        }
        else if (z < low) {
            cout << "Error. A negative number or zero is entered! Try again: ";
        }
        else if (max != 0 && z > max) {
            cout << "Error. A number greater than the maximum has been entered! Try again: ";
        }
        else {
            break;
        }
        cin >> z;
        cin.ignore();
    }
    return z;
}

int menu() {
    int k = -1;
    while (true) {
        cout << "Menu" << endl
            << "1) Add pipe" << endl
            << "2) Add station" << endl
            << "3) View objects" << endl
            << "4) Edit pipe" << endl
            << "5) Edit CS" << endl
            << "6) Save data" << endl
            << "7) Load data" << endl
            << "0) Exit" << endl
            << "Enter the command (0 to 7): ";
        k = check_int(7, 0);
        return k;
    }
}

void new_pipe(Pipe& P) {
    cout << "Enter pipe name: ";
    getline(cin, P.Name);
    cout << "Enter pipe length in kilometers:  ";
    P.length = floatcheck(0, 0.1);
    cout << "Enter pipe diameter in millimeters: ";
    P.diameter = check_int(0, 1);
    cout << "Select pipe status: " << endl << "0)Not under repair" << endl << "1)Under repair" << endl;
    P.repair = check_int(1, 0);
    cout << "Pipe created: " << endl << "Pipe name: " << P.Name << "; Pipe length: " << P.length << "; Pipe diameter: " << P.diameter << "; Status 'under repair: " << boolalpha << P.repair << endl;
}
void new_ks(Station& CS) {
    cout << "Enter station name: ";
    getline(cin, CS.Name);
    cout << "Enter number of workshops: ";
    CS.workshops = check_int(0, 1);
    cout << "Enter number of workshops in operation: ";
    CS.workshopsinwork = check_int(CS.workshops, 0);
    cout << "Enter station efficiency coefficient (from 0 to 100): ";
    CS.effectiveness = check_int(100, 0);
    cout << "Station created: " << endl << "Station name: " << CS.Name << "; Number of workshops: " << CS.workshops << "; Workshops in operation: " << CS.workshopsinwork << "; Efficiency coefficient: " << CS.effectiveness << endl;
}

void show_Pipe(const Pipe& P) {
    cout << "Pipe: " << endl << "Pipe name: " << P.Name << "; Pipe length: " << P.length << "; Pipe diameter: " << P.diameter << "; Status 'under repair': " << boolalpha << P.repair << endl;
}
void show_cs(const Station& CS) {
    cout << "Station: " << endl << "Station name: " << CS.Name << ";Number of workshops: " << CS.workshops << "; Workshops in operation: " << CS.workshopsinwork << "; Efficiency coefficient: " << CS.effectiveness << endl;
}

void view_all(const Pipe& P, const Station& CS) {
    if (CS.workshops > 0 && P.diameter > 0) {
        show_Pipe(P);
        show_cs(CS);
    }
    else if (CS.workshops < 1 && P.diameter > 0) {
        show_Pipe(P);
        cout << "No station added yet!" << endl;
    }
    else if (CS.workshops > 0 && P.diameter < 1) {
        show_cs(CS);
        cout << "No pipe added yet!" << endl;
    }
    else {
        cout << "No objects have been added yet." << endl;
    }
}

void edit_Pipe(Pipe& P) {
    int m = 0;
    if (P.diameter > 0) {
        while (true) {
            cout << "Select the parameter you want to edit: " << endl << "1) The status is 'under repair'" << endl << "0) Exit to menu" << endl << "Command number: ";
            m = check_int(1, 0);
            if (m == 0) {
                break;
            }
            else if (m == 1) {
                cout << "Old pipe status: under repair " << boolalpha << P.repair << endl;
                cout << "Select the new pipe status: " << endl << "0)Not in repair" << endl << "1)Under repair" << endl << "Enter the command number: ";
                P.repair = check_int(1, 0);
            }
        }
    }
    else {
        cout << "You have not added the pipe yet and cannot view its parameters. Please set up the pipe in the menu (item 1)" << endl;
    }
}

void edit_CS(Station& CS) {
    int m = 0;
    if (CS.workshops > 0) {
        while (true) {
            cout << "Select the parameter you want to edit: " << endl << "1) Number of workshops in operation" << endl << "0) Exit to the menu" << endl << "Comand number: ";
            m = check_int(1, 0);
            if (m == 0) {
                break;
            }
            else if (m == 1) {
                cout << "Total number of workshops: " << CS.workshops << "; The old number of workshops in operation: " << CS.workshopsinwork << endl;
                cout << "Enter a new number of workshops in operation: ";
                CS.workshopsinwork = check_int(CS.workshops, 0);
            }
        }
    }
    else {
        cout << "You have not added the CS yet and cannot view its parameters. Please configure the CS in the menu (item 2)" << endl;
    }
}
void SavePipe(const Pipe& P, ofstream& out)
{
    out << "data Pipe:" << endl;
    out << P.Name << endl;
    out << P.length << " " << P.diameter << " " << P.repair << endl;
}

void SaveCS(const Station& CS, ofstream& out)
{
    out << "data CS:" << endl;
    out << CS.Name << endl;
    out << CS.workshops << " " << CS.workshopsinwork << " " << CS.effectiveness << endl;;
}

void loadPipe(Pipe& P, ifstream& in)
{
    if (in.is_open()) {
        getline(in >> ws, P.Name);
        in >> P.length >> P.diameter >> P.repair;
    }
}
void loadCS(Station& CS, ifstream& in) {
    if (in.is_open()) {
        getline(in >> ws, CS.Name);
        in >> CS.workshops >> CS.workshopsinwork >> CS.effectiveness;
    }
}
void save(const Pipe& P, const Station& CS) {
    ofstream out;
    out.open("info.txt");
    if (out.is_open())
    {
        if (P.Name.empty() && CS.Name.empty()) {
            cout << "You don't have any data to record!" << endl;
            return;
        }
        if (!P.Name.empty() && CS.Name.empty()) {
            SavePipe(P, out);
            cout << "The data about the pipe is recorded!" << endl;
        }
        if (!CS.Name.empty() && P.Name.empty()) {
            SaveCS(CS, out);
            cout << "The CS data is recorded!" << endl;
        }

    }
    out.close();
}

void load(Pipe& P, Station& CS) {
    ifstream in("info.txt");
    if (!in.is_open())
    {
        cout << "not found" << endl;
        return;
    }
    P = {};
    CS = {};
    string finde;
    while (getline(in >> ws, finde)) {
        if (finde == "data Pipe:") {
            loadPipe(P, in);
            cout << "The data from the pipe file is recorded" << endl;
        }
        if (finde == "data CS:") {
            loadCS(CS, in);
            cout << "The data from the CS file is recorded" << endl;
        }
    }
}


int main() {
    Pipe P;
    Station CS;
    while (true) {
        switch (menu()) {
        case 1:
            new_pipe(P);
            break;
        case 2:
            new_ks(CS);
            break;
        case 3:
            view_all(P, CS);
            break;
        case 4:
            edit_Pipe(P);
            break;
        case 5:
            edit_CS(CS);
            break;
        case 6:
            save(P, CS);
            break;
        case 7:
            load(P, CS);
            break;
        case 0:
            return 0;
        }
    }
}