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

class NumberWithPosition {
	private:
		int number;
		std::vector<std::pair<int,int>> positions;
		bool valid  = false;	
	public:
		NumberWithPosition(const std::string &sNumber, int x, int y) {
			number = std::stoi(sNumber);
			for (int i=0; i < sNumber.length(); i++) {
				positions.push_back({x,(y+i)});
			}	
		}
		void setValid() {
			this->valid=true;
		}
	
		friend std::ostream& operator<<(std::ostream& os, const NumberWithPosition& obj);
		int getNumber() {
			return(this->number);
		}
			
};

std::ostream& operator<<(std::ostream& os, const NumberWithPosition& obj) {
	os << "Number: " << obj.number << std::endl;
	os << "Valid: ";
	if (obj.valid == true) { 
		os << "True"<< std::endl;

	}
	else {

		os << "False"<< std::endl;

	}
	os << "Positions: " << std::endl;
	for (const auto& position : obj.positions) {
		os << "    - (" <<position.first << ", " << position.second <<")" << std::endl;
	}
		
	os << endl; 
	return os;
}

bool isValidChar (char c) {
	if (c != '.' && !isdigit(c)){
		return true;
	}
	return false;
}

std::vector<std::pair<int,int>> getAdjacents(int x, int y, int maxX, int maxY) {
	std::vector<std::pair<int,int>> adjacents;
	std::vector<std::pair<int,int>> potentialAdjacents;
	potentialAdjacents.push_back({x,y-1});
	potentialAdjacents.push_back({x,y+1});
	potentialAdjacents.push_back({x-1,y-1});
	potentialAdjacents.push_back({x-1,y});
	potentialAdjacents.push_back({x-1,y+1});
	potentialAdjacents.push_back({x+1,y-1});
	potentialAdjacents.push_back({x+1,y});
	potentialAdjacents.push_back({x+1,y+1});	
	for (const auto& coordinate : potentialAdjacents) {
		if (0 <= coordinate.first && coordinate.first < maxX && 0 <= coordinate.second && coordinate.second < maxY){
			adjacents.push_back({coordinate.first,coordinate.second});
		}
	}
	return adjacents;
}

int main (int argc, char *argv[] ) {
	
	ifstream inputfile(argv[1]);
	string line, numberStr;
	int sum = 0, startIndex = 0;
	bool charFound = false;
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
				vector adjacents = getAdjacents(i, j, lines[i].size(), lines[j].size());
				for (const auto& adjacent : adjacents) {
					if (isValidChar(lines[adjacent.first][adjacent.second]) && !charFound) {
						charFound = true;
					}	
				}
			} 
			else if (!numberStr.empty() && charFound){
				numbersWithPositions.push_back(NumberWithPosition(numberStr, i, j-numberStr.length()));
				numberStr = "";
				charFound = false;
			}
			else if (!numberStr.empty() && !charFound){
				numberStr= "";
			}
		}
	}
	for (NumberWithPosition np : numbersWithPositions) {
	//	cout << np.getNumber() << endl;
		sum += np.getNumber();
	}
	cout << sum << endl;
        return 0;

}
