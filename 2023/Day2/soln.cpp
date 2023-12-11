#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;



vector<string> splitString(const string& str, const string& pattern) {
	vector<string> tokens;
	size_t start = 0;
	size_t found = str.find(pattern, start);

	while (found != string::npos) {
		tokens.push_back(str.substr(start, found - start));
		start = found + pattern.length();
		found = str.find(pattern, start);
	}
	tokens.push_back(str.substr(start));
	
//	for ( const auto& token : tokens) {
//		cout << token << endl;
//	}
	return tokens;
	
	
}

int parseLine (string line) {
	vector<string> result;
	int gameNumber = 0;
	
	result = splitString(line, ":");
	result = splitString(result[0], " ");
	gameNumber = stoi(result[1]);
	cout << gameNumber << endl;
	return 0;
}




int main (int argc, char *argv[] ) {
	
	if (argc != 2) {
		cout << "Usage " << argv[0] << "<filename>" << endl;
		return 1;
	}
	
	ifstream inputfile(argv[1]);
	string line;
	int sum = 0;
		
	if (!inputfile.is_open()) {
		cout << "Failed to open input file." << endl;
	}
	while(getline(inputfile, line)) {
		//do the thing
		//cout << line << endl;
		sum += parseLine(line);
	}
	
	cout << sum << endl;

	inputfile.close();
	return 0;
}
	


