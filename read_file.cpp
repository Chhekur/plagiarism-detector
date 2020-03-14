#pragma once
#include <iostream>
#include <fstream>
#include <functional>

using namespace std;

void read_file(string filepath, function<void(string)> callback) {
	fstream file;
	file.open(filepath, ios::in);
	if(file.is_open()) {
		string line;
		while(getline(file, line)) {
			// cout<<line<<"\n";
			callback(line);
		}
	}
}