#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "read_file.cpp"
#include "utils.cpp"

using namespace std;

map<string, bool> no_identifiers, word_list;
vector<string> multi_line, single_line;

void init_filter(string filepath) {
	bool in_comment_section = false;
	bool in_multi_comment_section = false;

	read_file(filepath, [&in_comment_section, &in_multi_comment_section](string line) {
		line = trim(line);
		if(line == "Essay:") exit(0);
		if(line == "Keywords:" || line == "Code:") return;

		vector<string> tokens = split(line, ' ');

		if(tokens[0] == "NoIdentifier:") {
			in_comment_section = true;
			for(int i = 1; i < tokens.size(); i++) no_identifiers[tokens[i]] = 1;
		}

		if(line == "Comments:") {
			in_comment_section = true;
			return;
		}

		if(line == "Multi:") {
			in_multi_comment_section = true;
		}

		if(!in_comment_section) word_list[line] = 1;
		if(in_comment_section && !in_multi_comment_section) single_line.push_back(line);
		if(in_multi_comment_section) {
			multi_line = split(line, ' ');
		}
	});
}