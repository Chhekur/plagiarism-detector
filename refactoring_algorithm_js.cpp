#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
	fstream file;
	file.open(argv[1], ios::in);
	if(file.is_open()) {
		string line;
		while(getline(file, line)) {
			cout<<line<<"\n";
		}
	}
}