#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
#include <limits>

using namespace std;

map<string, string> regions;

void change(const string& region, const string& center) {
    if (regions.find(region) != regions.end()) {
        // Переименование центра
        if (regions[region] == center) {
            throw runtime_error("Невозможно переименовать " + center + " в " + center);
        } else {
            string old_center = regions[region];
            regions[region] = center;
            cout << "Region " << region << " has changed its administrative center from "
                 << old_center << " to " << center << endl;
        }
    } else {
        // Создание нового региона
        regions[region] = center;
        cout << "New region " << region << " with administrative center " << center << endl;
    }
}

void rename(const string& old_region, const string& new_region) {
    if (regions.find(old_region) == regions.end()) {
        throw runtime_error("Региона с названием " + old_region + " не существует!");
    } else if (regions.find(new_region) != regions.end()) {
        throw runtime_error("Регион с названием " + new_region + " уже существует!");
    } else {
        string center = regions[old_region];
        regions.erase(old_region);
        regions[new_region] = center;
        cout << old_region << " has been renamed to " << new_region << endl;
    }
}

void about(const string& region) {
    if (regions.find(region) != regions.end()) {
        cout << region << " has administrative center " << regions[region] << endl;
    } else {
        throw runtime_error("Региона с названием " + region + " не существует!");
    }
}

void all() {
    if (!regions.empty()) {
        cout << "Список регионов:" << endl;
        for (map<string, string>::const_iterator it = regions.begin(); it != regions.end(); ++it) {
            cout << it->first << " - " << it->second << endl;
        }
    } else {
        throw runtime_error("Список регионов пуст!");
    }
}

int main() {
    int N;
    cout << "Введите количество запросов > ";
    cin >> N;

    for (int i = 0; i < N; ++i) {
        string cmd;
        cout << "   Введите команду > ";
        cin >> cmd;

        try {
            if (cmd == "CHANGE") {
                string region, center;
                cin >> region >> center;
                change(region, center);
            } else if (cmd == "RENAME") {
                string old_region, new_region;
                cin >> old_region >> new_region;
                rename(old_region, new_region);
            } else if (cmd == "ABOUT") {
                string region;
                cin >> region;
                about(region);
            } else if (cmd == "ALL") {
                all();
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Введена неверная команда!" << endl;
            }
        } catch (const exception& e) {
            cerr << e.what() << endl;
        }
    }

   return 0;
}