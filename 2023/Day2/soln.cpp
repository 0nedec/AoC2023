#include <iostream>
#include <fstream>

using namespace std;

int main (int argc, char *argv[] ) {
	
	if (argc != 2) {
		cout << "Usage " << argv[0] << "<filename>" << endl;
		return 1;
	}
	
	ifstream inputfile(argv[1]);
	string line;
		
	if (!inputfile.is_open()) {
		cout << "Failed to open input file." << endl;
	}
	while(getline(inputfile, line)) {
	//do the thing
	cout << line << endl;
	}
	
	inputfile.close();
	return 0;
}
	

