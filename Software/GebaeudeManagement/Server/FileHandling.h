#pragma once
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int loadCSV(const char* filename, vector<string>& data);
int writeCSV(ostream& out, string data);