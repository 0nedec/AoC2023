//todo: create list of stars
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm> 

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
		int getValue() const { return(this->number);}
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
		int getNumber() const {
			return(this->number);
		}
			
};

class Star{
	private:
		int numberCount;
		std::pair<int, int> pos;
	public:
		std::vector<NumberWithPosition> Numbers;


	Star(int x, int y, NumberWithPosition number){
		this->pos.first = x;
		this->pos.second = y;
		this->numberCount = 1;
		Numbers.push_back(number);
	}

	void addNumber(const NumberWithPosition& num) {
		Numbers.push_back(num);
		numberCount++;
	}
	
	std::pair<int,int> getPosition() const {
		return pos;
	}

	int getNumberCount() const {
		return numberCount;
	}
	friend std::ostream& operator<<(std::ostream& os, const Star& obj);

};

std::ostream& operator<<(std::ostream& os, const Star& obj) {
	os << "Number count: " << obj.numberCount << std::endl;
	os << "Positions: " << std::endl;
	os << "    - (" << obj.pos.first << ", " << obj.pos.second <<")" << std::endl;
	for (const auto& n : obj.Numbers) {
		os << "Numbers:" << std::endl;
		os << n.getNumber() << std::endl;
	}
	return os;
}

bool isValidChar (char c) {
	if (c == '*'){
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

std::vector<Star> findPairs( std::vector<Star> stars){
	std::map<std::pair<int,int>, Star> starMap;
	std::vector<Star> pairedStars;
	
	for (const Star& s : stars) {
		auto it = starMap.find(s.getPosition());
		if (it != starMap.end()){
			//position already exists, merge Numbers
			it ->second.addNumber(s.Numbers[0]);

		}
		else {
		//	starMap[s.getPosition()] = s;
			starMap.insert(std::make_pair(s.getPosition(), s));
		}
	}
	//find stars with numberCount 2 return that as a vector
	for (const auto& pair : starMap ) {
		if (pair.second.getNumberCount() == 2) {
			pairedStars.push_back(pair.second);
		}	
	}
	
	return pairedStars;

}
	

int main (int argc, char *argv[] ) {
	
	ifstream inputfile(argv[1]);
	string line, numberStr;
	int sum = 0, startIndex = 0;
	bool charFound = false;
	vector<vector<char>> lines;
	vector<Star> stars, pairedStars;
	std::pair<int, int> starPos;

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
						starPos.first = adjacent.first;
						starPos.second = adjacent.second;
					//	cout << "StarPos: " << starPos.first << ","; 
					//	cout << starPos.second << endl;
					} 	
				} 
			}  
			else if (!numberStr.empty() && charFound){
				NumberWithPosition number(numberStr, i, j-numberStr.length());
				numberStr = "";
				charFound = false;
				stars.push_back(Star(starPos.first, starPos.second, number));
			} 		

			else if (!numberStr.empty() && !charFound){
				numberStr= "";
			} 
		}
	} cout << "Finished iterating through lines." << endl; 
	pairedStars = findPairs(stars);
	for (const auto& st : pairedStars) {
		cout << st << endl;
		sum += (st.Numbers[0].getValue()*st.Numbers[1].getValue());
	}
	cout << sum << endl;
        return 0;

}
