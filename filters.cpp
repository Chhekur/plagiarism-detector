#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include "read_file.cpp"
#include "conf_filters.cpp"

using namespace std;

extern map<string, bool> no_identifiers, word_list;
extern vector<string> multi_line, single_line;
bool multi_line_type = false;
bool single_line_exist = false;

// void switch_text() {
// 	text_to_process = filterd_text;
// 	filterd_text = "";
// }

string replace_identifiers(string line) {
	string filterd_text = "";
	line = trim(line);
	vector<string> tokens = split(line, ' ');

	string new_line = "";
	bool text_modified = false;

	regex reg_identifier1("^[a-z|_]\\w*$");
	regex reg_identifier2("^[a-z|_]$");

	if(!no_identifiers[tokens[0]]) {
		text_modified = true;
		for(string word : tokens) {
			if(regex_match(word, reg_identifier1) || regex_match(word, reg_identifier2)) {
				if(!word_list[word]) {
					word = "v";
				}
			}
			new_line += " " + word + " ";
		}
	}

	if(text_modified) {
		filterd_text += new_line + "\n";
	} else {
		filterd_text += line + "\n";
	}
	return filterd_text;
}

string remove_comments(string line) {
	string filterd_text = "";
	if(multi_line_type) {
		if(line.find(multi_line[1]) != string::npos) {
			multi_line_type = false;
		}
		return "";
	}

	for(string comment : single_line) {
		string prefix = line.substr(0, comment.length());
		if(prefix == comment) {
			single_line_exist = true;
			break;
		}

		if(line.find(comment) != string::npos) {
			line = line.substr(0, line.find(comment));
		}
	}

	line = trim(line);

	//multiple commend in mid

	if(line.find(multi_line[0]) != string::npos && line.find(multi_line[1]) != string::npos) {
		line = line.substr(0, line.find(multi_line[0])) + line.substr(line.find(multi_line[1]) + 2, line.length());
	}

	// multiline comment
	string prefix = line.substr(0, multi_line[0].length());
	if(prefix == multi_line[0]) {
		multi_line_type = true;
	}

	if(single_line_exist == false && multi_line_type == false) {
		filterd_text += line + "\n";
	}

	if(multi_line_type == true) {
		if(line.find(multi_line[1]) != string::npos) {
			multi_line_type = false;
		}
	}
	return filterd_text;
}

string attact_bracket(string line) {
	regex reg("*\\(");
	line = regex_replace(line, reg, "( ");
	return line;
}

void space_tokens() {

}