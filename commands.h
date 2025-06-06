#pragma once
#include <string>
#include <vector>
#include <map>

void load_trams();
void create_tram(const std::string& tram_name, const std::vector<std::string>& stops);
void trams_in_stop(const std::string& stop);
void stops_in_tram(const std::string& tram_name);
void trams();