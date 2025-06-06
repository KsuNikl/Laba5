#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <map>
#include <fstream>
#include <limits>

using namespace std;

struct Cell {
    string product = "";
    int count = 0;
};

map<string, Cell> cells;

void load_cells() {
    ifstream in("cells.txt");
    string address, product;
    int count;
    while (in >> address >> product >> count) {
        cells[address] = Cell{product, count};
    }
}

void save_cells() {
    ofstream out("cells.txt", ios::trunc);
    for (const auto& [address, cell] : cells) {
        if (cell.count > 0) {
            out << address << " " << cell.product << " " << cell.count << "\n";
        }
    }
}

// Инициализация всех ячеек по ТЗ
void init_cells() {
    for (char zone : string("ABC")) {
        for (int stell = 1; stell <= 14; stell++) {
            for (int vert = 1; vert <= 6; vert++) {
                for (int polka = 1; polka <= 20; polka++) {
                    ostringstream os;
                    os << zone
                       << setw(2) << setfill('0') << stell
                       << vert
                       << setw(2) << setfill('0') << polka;
                    cells.emplace(os.str(), Cell{});
                }
            }
        }
    }
}

string add_product(const string& product, int count, const string& address) {
    if (!cells.count(address)) {
        return "Такого адреса не существует!";
    }
    auto& cell = cells.at(address);
    if (!cell.product.empty() && cell.product != product) {
        return "Ячейка занята другим товаром!";
    } else if (count <= 0) {
        return "Количество должно быть больше 0!";
    } else if (count > (10 - cell.count)) {
        return "Недостаточно места!";
    }
    cell.product = product;
    cell.count += count;
    return "Успешно!";
}

string remove_product(const string& product, int count, const string& address) {
    if (!cells.count(address)) {
        return "Такого адреса не существует!";
    }
    auto& cell = cells.at(address);
    if (cell.product.empty()) {
        return "Ячейка пуста!";
    } else if (cell.product != product) {
        return "В ячейке находится другой товар!";
    } else if (count <= 0) {
        return "Количество должно быть больше 0!";
    } else if (count > cell.count) {
        return "Недостаточно товара для удаления!";
    }
    cell.count -= count;
    if (cell.count == 0) {
        cell.product = "";
    }
    return "Успешно!";
}

void get_info() {
    int product_count = 0;
    map<string, Cell> non_empty_cells;
    vector<string> empty_cells;
    for (const auto& [address, cell] : cells) {
        product_count += cell.count;
        if (cell.count > 0) {
            non_empty_cells.emplace(address, cell);
        } else {
            empty_cells.push_back(address);
        }
    }
    cout << "\nСклад загружен на " << product_count * 100 / (cells.size() * 10)
         << "% (" << product_count << "/" << (cells.size() * 10) << ")" << endl;
    cout << "\nЗанятые ячейки:" << endl;
    for (const auto& [address, cell] : non_empty_cells) {
        cout << address << ": " << cell.product << " " << cell.count << " шт." << endl;
    }
    cout << "\nПустые ячейки:" << endl;
    for (size_t i = 0; i < empty_cells.size(); i++) {
        cout << empty_cells[i] << ((i % 20 == 19) ? "\n" : " ");
    }
    cout << endl;
}

int main() {
    cout << "СКЛАД\n\n"
            "Добавить товар - ADD\n"
            "Удалить товар - REMOVE\n"
            "Информация - INFO\n"
            "Выход - EXIT" << endl;

    string cmd, product, address;
    int count;

    init_cells();
    load_cells();
while (true) {
        cout << "    Введите команду > ";
        cin >> cmd;
        if (cmd == "ADD") {
            if (cin >> product >> count >> address) {
                cout << add_product(product, count, address) << endl;
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Неверный формат команды! Нужно: <товар> <кол-во> <адрес>\n";
            }
        } else if (cmd == "REMOVE") {
            if (cin >> product >> count >> address) {
                cout << remove_product(product, count, address) << endl;
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Неверный формат команды! Нужно: <товар> <кол-во> <адрес>\n";
            }
        } else if (cmd == "INFO") {
            get_info();
        } else if (cmd == "EXIT") {
            save_cells();
            return 0;
        } else {
            cout << "Введена неверная команда!\nПопробуйте снова!" << endl;
        }
    }
}