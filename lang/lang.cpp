#include <string>
#include <sstream> // Для str()

using namespace std;

unsigned int llength(string line) {
	return line.length();
}

string str(int input) { // Из int в string
	stringstream ss;
	ss << "";
	ss << input;
	string str;
	ss >> str;
	return str;
}