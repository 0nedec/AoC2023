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
/*
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
*/

class NumberWithPosition {
	private:
		int number;
		std::vector<std::pair<int,int>> positions;
	
	public:
		NumberWithPosition(const std::string &sNumber, int x, int y) {
			number = std::stoi(sNumber);
			for (int i=0; i < sNumber.length(); i++) {
				positions.push_back({x,(y+i)});
			}	
		}
	
		friend std::ostream& operator<<(std::ostream& os, const NumberWithPosition& obj);
	
};

std::ostream& operator<<(std::ostream& os, const NumberWithPosition& obj) {
	os << "Number: " << obj.number << std::endl;
	os << "Positions: " << std::endl;
	for (const auto& position : obj.positions) {
		os << "- (" <<position.first << ", " << position.second <<")" << std::endl;
	}
	return os;
}
/*
class CharWithLocation {
	public:
		char symbol;
		std::vector<std::pair<int, int> positions;
		std::vector<std::pair<int, int> adjacents;
}
*/
int main (int argc, char *argv[] ) {
	
	ifstream inputfile(argv[1]);
	string line, numberStr;
	int sum = 0, startIndex = 0;
	vector<vector<char>> lines;    
	vector<NumberWithPosition> numbersWithPositions;

//usage:
	if (argc != 2) {
        	cout << "Usage " << argv[0] << "<filename>" << endl;
        	return 1;
    	}
//try to open file:
	if (!inputfile.is_open()) {
        	cout << "Failed to open input file." << endl;
    	}

//challenge logic 

    	while(getline(inputfile, line)) {
		vector<char> chars(line.begin(), line.end());
		lines.push_back(chars);
    	}
    	inputfile.close();
	
	for(int i = 0; i < lines.size(); i++) {
		for (int j = 0; j < lines[i].size(); j++) {
			if (isdigit(lines[i][j])) {
				numberStr += lines[i][j];
			}
			else if (!numberStr.empty()){
			//	cout << numberStr << endl;

				numbersWithPositions.push_back(NumberWithPosition(numberStr, i, j-numberStr.length()));
				numberStr = "";
			}
		}
	}
	for (NumberWithPosition np : numbersWithPositions) {
		cout << np;
	}
        return 0;

}
