#pragma once
#include <iostream>
#include <string>

using namespace std;

string trim(string line){
    const char* WHITE_SPACE = " \t\v\r\n";
    size_t start = line.find_first_not_of(WHITE_SPACE);
    size_t end = line.find_last_not_of(WHITE_SPACE);
    return start == end ? string() : line.substr(start, end - start + 1);
}

vector<string> split(string line, char delim) {
	vector<string> words;
	string word = "";
	for(int i = 0; i < line.length(); i++) {
		if(line[i] == delim) {
			words.push_back(word);
			word = "";
			continue;
		}
		word += line[i];
	}
	words.push_back(word);
	return words;
}