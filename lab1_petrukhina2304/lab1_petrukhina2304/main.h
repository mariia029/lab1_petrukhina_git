#pragma once
#pragma once
#include <unordered_map>
#include <fstream>

void write_data(std::ofstream& fout, const std::unordered_map<int, pipe>& pipemap);

