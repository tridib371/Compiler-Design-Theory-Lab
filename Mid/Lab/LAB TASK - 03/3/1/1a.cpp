#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

// Set of C++ keywords
set<string> keywords = {"auto", "break", "case", "char", "const", "continue", "default",
                        "do", "double", "else", "enum", "extern", "float", "for",
                        "goto", "if", "int", "long", "register", "return", "short",
                        "signed", "sizeof", "static", "struct", "switch", "typedef",
                        "union", "unsigned", "void", "volatile", "while"};

// Function to check if a string is a valid identifier
bool isValidIdentifier(const string& token) {
    if (!isalpha(token[0]) && token[0] != '_')
        return false;

    for (size_t i = 1; i < token.length(); ++i) {
        if (!isalnum(token[i]) && token[i] != '_')
            return false;
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
            if (keywords.find(token) != keywords.end()) {
                cout << "Keyword: " << token << endl;
            } else if (isValidIdentifier(token)) {
                cout << "Identifier: " << token << endl;
            } else {
                cout << "Operator or unknown: " << token << endl;
            }
        }
    }

    inFile.close();
    return 0;
}
