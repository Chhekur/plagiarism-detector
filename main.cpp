#include <iostream>
#include "filters.cpp"

using namespace std;

string filterd_text = "";

int main(int argc, char** argv) {

	init_filter("conf/cpp.conf");
	
	read_file("conf_filters.cpp", [](string line) {
		string text = replace_identifiers(line);
		filterd_text += remove_comments(text);
	});
	
	cout<<filterd_text<<"\n";
}