// FOR FILE HANDLING REFER TO http://www.cplusplus.com/doc/tutorial/files/
#pragma once
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

bool txt_read(const char* filename, vector<string> &data);
bool txt_truncate(const char* filename, vector<string>& data);
bool txt_putLine(const char* filename, string &line);
bool txt_exists(const char* filename);