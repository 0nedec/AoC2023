#include <iostream>
#include <cstdio>
#include <fstream>
#include <map>

using namespace std;

int getCoordinateFromLineWithStrings(string currentString) {
	int first = 0, last = 0, firstPos = 999, lastPos=-1, coordinate = 0;
	map<string, string> numbers;
	numbers["one"] = "1";
	numbers["two"] = "2";
	numbers["three"] = "3";
	numbers["four"] = "4";
	numbers["five"] = "5";
	numbers["six"] = "6";
	numbers["seven"] = "7";
	numbers["eight"] = "8";
	numbers["nine"] = "9";
	numbers["1"] = "1";
	numbers["2"] = "2";
	numbers["3"] = "3";
	numbers["4"] = "4";
	numbers["5"] = "5";
	numbers["6"] = "6";
	numbers["7"] = "7";
	numbers["8"] = "8";
	numbers["9"] = "9";
	
	for (const auto& pair : numbers) {
		size_t position = currentString.find(pair.first);
		if ( position != std::string::npos) {
			if ( static_cast<int>(position) < firstPos) {
				first = stoi(pair.second);
				firstPos = static_cast<int>(position);
			}
		}
		position = currentString.rfind(pair.first);
		if ( position != std::string::npos) {
			if (static_cast<int>(position) > lastPos) {
				last = stoi(pair.second);
				lastPos = static_cast<int>(position);
			}
		}
			
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
		sum += getCoordinateFromLineWithStrings(line.c_str());
	}
	cout << sum << endl;

	inputfile.close();

	return 0;
}



