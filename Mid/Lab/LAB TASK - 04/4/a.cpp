#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

// Function to check if a given character is a valid identifier character
bool isIdentifierChar(char c) {
    return (std::isalnum(c) || c == '_');
}

// Function to check if the variable name is valid
bool isValidVariableName(const std::string &name) {
    if (name.empty() || (!std::isalpha(name[0]) && name[0] != '_')) {
        return false;
    }
    for (char c : name) {
        if (!isIdentifierChar(c)) {
            return false;
        }
    }
    return true;
}

// Function to check if a variable declaration is valid
bool isValidVariableDeclaration(const std::string &declaration) {
    // Supported types
    std::vector<std::string> types = {"int", "float", "double", "char", "bool"};

    // Find the first space which separates the type from the variable name
    size_t spacePos = declaration.find(' ');
    if (spacePos == std::string::npos) {
        return false;
    }

    // Extract the type and the rest of the declaration
    std::string type = declaration.substr(0, spacePos);
    std::string rest = declaration.substr(spacePos + 1);

    // Check if the type is valid
    if (std::find(types.begin(), types.end(), type) == types.end()) {
        return false;
    }

    // Check if the rest ends with a semicolon
    if (rest.back() != ';') {
        return false;
    }

    // Remove the semicolon for further checks
    rest.pop_back();

    // Find the equals sign, if any
    size_t equalPos = rest.find('=');

    // Extract the variable name
    std::string variableName = (equalPos == std::string::npos) ? rest : rest.substr(0, equalPos);
    // Trim whitespace
    variableName.erase(variableName.find_last_not_of(" \t\n\r\f\v") + 1);

    // Check if the variable name is valid
    return isValidVariableName(variableName);
}

int main() {
    // Test cases
    std::vector<std::string> testCases = {
        "int a;",             // valid
        "float number;",      // valid
        "double value = 3.14;", // valid
        "char letter = 'A';", // valid
        "bool isValid = true;", // valid
        "int 123invalid;",    // invalid
        "double 1value;",     // invalid
        "char@variable;",     // invalid
        "float;",             // invalid
        "int valid_var = 1"   // invalid
    };

    // Check each test case
    for (const auto &test : testCases) {
        std::cout << "Checking: " << test << " -> ";
        if (isValidVariableDeclaration(test)) {
            std::cout << "Valid" << std::endl;
        } else {
            std::cout << "Invalid" << std::endl;
        }
    }

    return 0;
}
