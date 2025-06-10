#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <cctype>

bool isValidIdentifier(const std::string& identifier) {
    if (identifier.empty() || (!std::isalpha(identifier[0]) && identifier[0] != '_')) {
        return false;
    }
    for (char c : identifier) {
        if (!std::isalnum(c) && c != '_') {
            return false;
        }
    }
    return true;
}

bool isKeyword(const std::string& word) {
    static const std::unordered_set<std::string> keywords = {
        "break", "case", "char", "const", "do", "double",
        "else", "enum", "float", "for", "if", "int", "long",
        "return", "short", "signed", "sizeof", "static", "struct", "switch",
        "union", "unsigned", "void",  "while"
    };
    return keywords.find(word) != keywords.end();
}

bool isOperator(const std::string& op) {
    static const std::unordered_set<std::string> operators = {
        "+", "-", "*", "/", "%", "++", "--", "==", "!=", ">", "<", ">=", "<=", "&&", "||",
        "!", "&", "|", "^", "~", "<<", ">>", "=", "+=", "-=", "*=", "/=", "%=", "&=", "|=",
        "^=", "<<=", ">>="
    };
    return operators.find(op) != operators.end();
}

int main() {
    std::ifstream file("t.txt");
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        while (iss >> token) {
            if (isKeyword(token)) {
                std::cout << token << " is a keyword." << std::endl;
            }
            else if (isOperator(token)) {
                std::cout << token << " is an operator." << std::endl;
            }
            else if (isValidIdentifier(token)) {
                std::cout << token << " is a valid identifier." << std::endl;
            }

        }
    }

    return 0;
}
