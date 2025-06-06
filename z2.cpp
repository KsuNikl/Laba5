#include <iostream>
#include <map>
#include <string>
#include <random>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <vector>

using namespace std;

void distribute(vector<pair<string, int>> clients, int windows_count) {
    for (auto& [talon, time] : clients) {
        if (time <= 0) {
            cerr << "Предупреждение: талон " << talon << " имеет недопустимое время (" << time << ").\n";
            time = 0;
        }
    }
    sort(clients.begin(), clients.end(), [](auto &a, auto &b) {
        return a.second > b.second;
    });
    vector<int> windows_load(windows_count, 0);
    vector<vector<string>> windows_clients(windows_count);

    for (auto &[talon, time] : clients) {
        int min_idx = 0;
        for (int i = 1; i < windows_count; i++) {
            if (windows_load[i] < windows_load[min_idx]) min_idx = i;
        }
        windows_load[min_idx] += time;
        windows_clients[min_idx].push_back(talon);
    }

    for (int i = 0; i < windows_count; i++) {
        cout << "Окно " << i + 1 << " (" << windows_load[i] << " минут): ";
        for (size_t j = 0; j < windows_clients[i].size(); j++) {
            cout << windows_clients[i][j];
            if (j != windows_clients[i].size() - 1) cout << ", ";
        }
        cout << "\n";
    }
}

int main() {
    int windows_count, talon_count = 0;
    vector<pair<string, int>> clients;

    cout << "Введите кол-во окон: ";
    cin >> windows_count;
    while (true) {
        int time;
        string cmd, window;

        cout << "   Введите команду > ";
        cin >> cmd;

        if (cmd == "ENQUEUE") {
            cin >> time;
            if (time <= 0) {
                cerr << "Ошибка: время должно быть положительным (получено " << time << ")\n";
                continue;
            }
            talon_count += 1;

            ostringstream os;
            os << "T" << setw(3) << setfill('0') << talon_count;
            clients.push_back(make_pair(os.str(), time));
            cout << os.str() << endl;
        } else if (cmd == "DISTRIBUTE") {
            distribute(clients, windows_count);
            return 0;
        } else {
            cout << "Введена неверная команда!" << endl;
        }
    }
}