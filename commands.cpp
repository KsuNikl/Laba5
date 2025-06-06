#include "commands.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <stdexcept>
#include <fstream>

using namespace std;

map<string, vector<string>> trams_stops;
map<string, vector<string>> stops_trams;

void load_trams() {
    cout << "Загружаю список трамваев для теста..." << endl;
    ifstream in("trams.txt");

    string tram;
    int stops_count;

    while (in >> tram >> stops_count) {
        vector<string> stops;
        for (int i = 0; i < stops_count; i++) {
            string stop;
            in >> stop;
            stops.push_back(stop);
        }
        create_tram(tram, stops);
    }


}

void create_tram(const string& tram_name, const vector<string>& stops) {
#if __cplusplus >= 202002L
    if (trams_stops.contains(tram_name)) {
#else
    if (trams_stops.find(tram_name) != trams_stops.end()) {
#endif
        throw runtime_error("Трамвай №" + tram_name + " уже существует!");
    } else if (stops.size() < 0) {
        throw runtime_error("Не указано количество остановок трамвая!");
    } else if (stops.size() < 2) {
        throw runtime_error("Трамвай должен иметь не менее двух остановок");
    } else {
        trams_stops.emplace(tram_name, stops);
        for (const auto& stop : stops) {
            stops_trams[stop].push_back(tram_name);
        }
        cout << "Успешно создан трамвай № " << tram_name << endl;
    }
}

void trams_in_stop(const string& stop_name) {
#if __cplusplus >= 202002L
    if (stops_trams.contains(stop_name)) {
#else
    if (stops_trams.find(stop_name) != stops_trams.end()) {
#endif
        cout << "Трамваи на остановке " << stop_name << ":";
        for (const auto& tram : stops_trams[stop_name]) {
            cout << " " << tram;
        }
        cout << endl;
    } else {
        throw runtime_error("Остановки " + stop_name + " не существует!");
    }
}

void stops_in_tram(const string& tram_name) {
#if __cplusplus >= 202002L
    if (trams_stops.contains(tram_name)) {
#else
    if (trams_stops.find(tram_name) != trams_stops.end()) {
#endif
        cout << "Остановки трамвая №" << tram_name << ":" << endl;
        int c = 1;
        for (const auto& stop : trams_stops[tram_name]) {
            cout << c << ". Stop " << stop << ": ";
            for (const auto& tram : stops_trams[stop]) {
                if (!(tram == tram_name)) {
                    cout << tram << " ";
                }
            }
            cout << endl;
            c += 1;
        }
    } else {
        throw runtime_error("Трамвая " + tram_name + " не существует!");
    }
}

void trams() {
    if (trams_stops.size() > 0) {
        for (const auto& [tram, stops] : trams_stops) {
            cout << "TRAM " << tram << ":";
            for (const auto& stop : stops) {
                cout << " " << stop;
            }
            cout << endl;
        }
    } else {
        throw runtime_error("Список трамваев пуст.");
    }
}