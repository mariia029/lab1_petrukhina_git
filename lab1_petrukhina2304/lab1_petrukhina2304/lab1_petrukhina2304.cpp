#include <iostream> //для вводы и вывода
#include <string> //для работ со строками
#include <vector> //для работы с динам массивами
#include <fstream> //для файлов

using namespace std;

// Структура для описания трубы
struct Pipe {
    string name;
    double length;
    double diameter;
    bool inRepair;

    // Чтение данных о трубе с консоли
    void input() {
        cout << "Enter pipe name: ";
        cin >> name;
        cout << "Enter pipe length: ";
        cin >> length;
        cout << "Enter pipe diameter: ";
        cin >> diameter;
        inRepair = false;  // По умолчанию труба не в ремонте
    }

    // Вывод данных о трубе на консоль
    void output() const {
        cout << "Pipe name: " << name << endl;
        cout << "Pipe length: " << length << endl;
        cout << "Pipe diameter: " << diameter << endl;
        cout << "Repair status: " << (inRepair ? "In repair" : "Not in repair") << endl;
    }

    // Редактирование состояния ремонта
    void toggleRepair() {
        inRepair = !inRepair;
        cout << "Repair status changed to: " << (inRepair ? "In repair" : "Not in repair") << endl;
    }
};

// структура для описания компрессорной станции
struct KS {
    string name;
    int numShops; // обшее кол-во цехов
    int workingShops; // кол-во рабочих цехов
    double efficiency; // эффективность КС

    // чтение данных о КС с консоли
    void input() {
        cout << "Enter KS name: ";
        cin >> name;
        cout << "Enter number of shops: ";
        cin >> numShops;
        cout << "Enter number of working shops: ";
        cin >> workingShops;
        while (workingShops > numShops || workingShops < 0) {
            cout << "Number of working shops cannot exceed total or be negative. Try again: ";
            cin >> workingShops;
        }
        cout << "Enter KS efficiency: ";
        cin >> efficiency;
    }

    // Вывод данных о КС на консоль
    void output() const {
        cout << "KS name: " << name << endl;
        cout << "Total shops: " << numShops << endl;
        cout << "Working shops: " << workingShops << endl;
        cout << "Efficiency: " << efficiency << endl;
    }

    // Запуск цеха
    void startShop() {
        if (workingShops < numShops) {
            workingShops++;
            cout << "Shop started. Now working shops: " << workingShops << endl;
        }
        else {
            cout << "All shops are already working." << endl;
        }
    }

    // Остановка цеха
    void stopShop() {
        if (workingShops > 0) {
            workingShops--;
            cout << "Shop stopped. Now working shops: " << workingShops << endl;
        }
        else {
            cout << "No working shops." << endl;
        }
    }
};

// функции для работы с файлами
void saveData(const vector<Pipe>& pipes, const vector<KS>& stations, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        // сохраняем трубы
        file << pipes.size() << endl;
        for (const Pipe& pipe : pipes) {
            file << pipe.name << " " << pipe.length << " " << pipe.diameter << " " << pipe.inRepair << endl;
        }

        // сохраняем КС
        file << stations.size() << endl;
        for (const KS& station : stations) {
            file << station.name << " " << station.numShops << " " << station.workingShops << " " << station.efficiency << endl;
        }

        file.close();
        cout << "Data saved to file " << filename << endl;
    }
    else {
        cout << "Error opening file!" << endl;
    }
}

void loadData(vector<Pipe>& pipes, vector<KS>& stations, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        pipes.clear();
        stations.clear();

        // чтение труб
        size_t pipeCount;
        file >> pipeCount;
        for (size_t i = 0; i < pipeCount; i++) {
            Pipe p;
            file >> p.name >> p.length >> p.diameter >> p.inRepair;
            pipes.push_back(p);
        }

        // чтение КС
        size_t ksCount;
        file >> ksCount;
        for (size_t i = 0; i < ksCount; i++) {
            KS ks;
            file >> ks.name >> ks.numShops >> ks.workingShops >> ks.efficiency;
            stations.push_back(ks);
        }

        file.close();
        cout << "Data loaded from file " << filename << endl;
    }
    else {
        cout << "Error opening file!" << endl;
    }
}

// Основное меню программы
void showMenu() {
    cout << "1. Add pipe\n";
    cout << "2. Add KS\n";
    cout << "3. View all objects\n";
    cout << "4. Edit pipe\n";
    cout << "5. Edit KS\n";
    cout << "6. Save data\n";
    cout << "7. Load data\n";
    cout << "0. Exit\n";
}

int main() {
    vector<Pipe> pipes;
    vector<KS> stations;
    string filename = "lab1_file.txt";
    int choice;

    do {
        showMenu();
        cout << "Choose an action: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            Pipe p;
            p.input();
            pipes.push_back(p);
            break;
        }
        case 2: {
            KS ks;
            ks.input();
            stations.push_back(ks);
            break;
        }
        case 3:
            cout << "Pipes:\n";
            for (const Pipe& p : pipes) {
                p.output();
            }
            cout << "Compressor stations:\n";
            for (const KS& ks : stations) {
                ks.output();
            }
            break;
        case 4: {
            cout << "Enter the index of the pipe to edit (starting from 1): ";
            size_t index;
            cin >> index;
            if (index > 0 && index <= pipes.size()) {
                pipes[index - 1].toggleRepair();
            }
            else {
                cout << "Invalid index!" << endl;
            }
            break;
        }

        case 5: {
            cout << "Enter the index of the KS to edit (starting from 1): ";
            size_t index;
            cin >> index;
            if (index > 0 && index <= stations.size()) {
                cout << "1. Start shop\n2. Stop shop\n";
                int subChoice;
                cin >> subChoice;
                if (subChoice == 1) {
                    stations[index - 1].startShop();
                }
                else if (subChoice == 2) {
                    stations[index - 1].stopShop();
                }
                else {
                    cout << "Invalid choice!" << endl;
                }
            }
            else {
                cout << "Invalid index!" << endl;
            }
            break;
        }

        case 6:
            saveData(pipes, stations, filename);
            break;
        case 7:
            loadData(pipes, stations, filename);
            break;
        case 0:
            cout << "Exiting the program.\n";
            break;
        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);

    return 0;
}
