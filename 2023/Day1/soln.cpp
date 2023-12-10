#include <iostream>
#include <cstdio>
#include <fstream>

using namespace std;

int getCoordinateFromLine(string currentString) {
	int first = 0, last = 0, coordinate = 0;
	for ( int ii = 0; ii < currentString.length(); ii++) {
		if (isdigit(currentString[ii])){
			if (first == 0) {
				first = stoi(string(1,currentString[ii]));
			}
			else {
				last = stoi(string(1,currentString[ii]));

			}
		}
	}
	if (last == 0) {
		last = first;
	}
	coordinate = ((first*10)+last);
	return coordinate;

}

int main (int argc, char *argv[]) {
	if (argc != 2) {
		cout << "Usage " << argv[0] << " <filename>" << endl;
	}
	
	uint32_t sum = 0;
	
	ifstream inputfile(argv[1]);
	string line;

	if (!inputfile.is_open()) {
		cout << "Failed to open input file." << endl;
	}
	
	while(getline(inputfile, line)){
		cout << line.c_str() << endl;
		sum += getCoordinateFromLine(line.c_str());
	}
	cout << sum << endl;

	inputfile.close();

	
}


