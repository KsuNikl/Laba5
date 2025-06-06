#include "commands.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

enum class CommandType {
    CREATE_TRAM,
    TRAMS_IN_STOP,
    STOPS_IN_TRAM,
    TRAMS,
    EXIT
};

CommandType parseCommand(const string& s) {
    if (s == "CREATE_TRAM") return CommandType::CREATE_TRAM;
    if (s == "TRAMS_IN_STOP") return CommandType::TRAMS_IN_STOP;
    if (s == "STOPS_IN_TRAM") return CommandType::STOPS_IN_TRAM;
    if (s == "TRAMS") return CommandType::TRAMS;
    if (s == "EXIT") return CommandType::EXIT;
    throw runtime_error("Неизвестная команда: " + s);
}

int main() {
    load_trams();
    while (true) {
        string strcmd;
        cout << "   Введите команду > ";
        cin >> strcmd;

        CommandType cmd;
        try {
            cmd = parseCommand(strcmd);
        } catch (const exception& e) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << e.what() << endl;
            continue;
        }

        switch (cmd) {
            case CommandType::CREATE_TRAM: {
                string tram_name;
                int stops_count;
                vector<string> stops;
                cin >> tram_name >> stops_count;
                for (int nstop = 0; nstop < stops_count; nstop++) {
                    string stop_name;
                    cin >> stop_name;
                    if (find(stops.begin(), stops.end(), stop_name) == stops.end()) {
                        stops.push_back(stop_name);
                    }
                }
                try {
                    if (stops.empty()) {
                        cout << "Ошибка: нельзя создать такой трамвай" << endl;
                    } else if (stops.size() < 2) {
                        cout << "Ошибка: трамвай должен иметь не менее двух остановок." << endl;
                    } else {
                        create_tram(tram_name, stops);
                    }
                } catch (const exception& e) {
                    cerr << e.what() << endl;
                }
                break;
            }
            case CommandType::TRAMS_IN_STOP: {
                string stop_name;
                cin >> stop_name;
                try {
                    trams_in_stop(stop_name);
                } catch (const exception& e) {
                    cerr << e.what() << endl;
                }
                break;
            }
            case CommandType::STOPS_IN_TRAM: {
                string tram_name;
                cin >> tram_name;
                try {
                    stops_in_tram(tram_name);
                } catch (const exception& e) {
                    cerr << e.what() << endl;
                }
                break;
            }
            case CommandType::TRAMS: {
                try {
                    trams();
                } catch (const exception& e) {
                    cerr << e.what() << endl;
                }
                break;
            }
            case CommandType::EXIT: {
                return 0;
            }
        }
    }
}