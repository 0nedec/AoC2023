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

    }
    
    cout << sum << endl;
    inputfile.close();

    return 0;

}