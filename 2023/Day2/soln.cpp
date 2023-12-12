#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

void printVector(vector<string>& V) {
	for (const auto& element : V) {
	cout << element << endl;
	}
}

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
	return tokens;
	
	
}

bool gameViable(vector<string>& rounds) {
	int number = 0;
	string num;
	map<string, int> max;
	max["red"] = 12;
	max["green"] = 13;
	max["blue"] = 14;

	for (const auto& round : rounds) {
		for (const auto& color : max) {
			size_t position = round.find(color.first);
			while (position != string::npos) {
				num = round.substr((position-3), 3);
				number = stoi(num);
				if (number > color.second) {
					return(false);
				}
				position = round.find(color.first, position + 1);
			}
		}
	}
	return(true);
}

int parseLine (string line) {
	vector<string> splitByColon, splitBySemicolon, splitBySpace;
	int gameNumber = 0;
	string temptString;
	
	splitByColon = splitString(line, ":");
	splitBySpace = splitString(splitByColon[0], " ");
	gameNumber = stoi(splitBySpace[1]);
	splitBySemicolon = splitString(splitByColon[1], ";");
	
	if (gameViable(splitBySemicolon)){
		cout << "Game " << gameNumber << " viable."<< endl;
		return gameNumber;
	}
	else {
		return 0;
	}
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
		sum += parseLine(line);
	}
	
	cout << sum << endl;

	inputfile.close();
	return 0;
}
