#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

// Function to check if a string is an integer
bool isInteger(const string& token) {
    for (char c : token) {
        if (!isdigit(c))
            return false;
    }
    return true;
}

// Function to check if a string is a real number
bool isRealNumber(const string& token) {
    bool foundDot = false;
    for (char c : token) {
        if (c == '.') {
            if (foundDot) return false;
            foundDot = true;
        } else if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

int main() {
    ifstream inFile("input.txt");
    if (!inFile) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    string line;
    while (getline(inFile, line)) {
        istringstream iss(line);
        string token;

        while (iss >> token) {
            if (token == "{" || token == "}" || token == ";" || token == "(" || token == ")") {
                cout << "Delimiter: " << token << endl;
            } else if (isInteger(token)) {
                cout << "Integer: " << token << endl;
            } else if (isRealNumber(token)) {
                cout << "Real Number: " << token << endl;
            }
        }
    }

    inFile.close();
    return 0;
}
