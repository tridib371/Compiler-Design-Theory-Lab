#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

// Function to check if a given character is a valid identifier character
bool isIdentifierChar(char c) {
    return (std::isalnum(c) || c == '_');
}

// Function to check if the identifier (function name or variable name) is valid
bool isValidIdentifier(const std::string &name) {
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

// Function to check if a function definition is valid
bool isValidFunctionDefinition(const std::string &definition) {
    // Supported return types
    std::vector<std::string> returnTypes = {"void", "int", "float", "double", "char", "bool"};

    // Find the first space which separates the return type from the function name
    size_t spacePos = definition.find(' ');
    if (spacePos == std::string::npos) {
        return false;
    }

    // Extract the return type and the rest of the definition
    std::string returnType = definition.substr(0, spacePos);
    std::string rest = definition.substr(spacePos + 1);

    // Check if the return type is valid
    if (std::find(returnTypes.begin(), returnTypes.end(), returnType) == returnTypes.end()) {
        return false;
    }

    // Find the opening parenthesis for the parameter list
    size_t openParenPos = rest.find('(');
    if (openParenPos == std::string::npos) {
        return false;
    }

    // Extract the function name
    std::string functionName = rest.substr(0, openParenPos);
    // Trim whitespace
    functionName.erase(functionName.find_last_not_of(" \t\n\r\f\v") + 1);

    // Check if the function name is valid
    if (!isValidIdentifier(functionName)) {
        return false;
    }

    // Find the closing parenthesis for the parameter list
    size_t closeParenPos = rest.find(')');
    if (closeParenPos == std::string::npos || closeParenPos < openParenPos) {
        return false;
    }

    // Ensure there is an opening curly brace after the parameter list
    size_t openBracePos = rest.find('{', closeParenPos);
    if (openBracePos == std::string::npos) {
        return false;
    }

    // Ensure there is a closing curly brace after the opening curly brace
    size_t closeBracePos = rest.find('}', openBracePos);
    if (closeBracePos == std::string::npos) {
        return false;
    }

    return true;
}

int main() {
    // Test cases
    std::vector<std::string> testCases = {
        "void myFunction() { }",                    // valid
        "int add(int a, int b) { return a + b; }",  // valid
        "float computeArea(float radius) { return 3.14 * radius * radius; }", // valid
        "double calculate(double x) { return x * x; }", // valid
        "char getInitial() { return 'A'; }",        // valid
        "bool isValid() { return true; }",          // valid
        "void 123invalid() { }",                    // invalid
        "int1 invalidFuncName(int a) { return a; }", // invalid
        "float compute(,",                          // invalid
        "double calc)double x( { return x; }",      // invalid
        "char { return 'A'; }",                     // invalid
        "bool is_valid( { return true; }"           // invalid
    };

    // Check each test case
    for (const auto &test : testCases) {
        std::cout << "Checking: " << test << " -> ";
        if (isValidFunctionDefinition(test)) {
            std::cout << "Valid" << std::endl;
        } else {
            std::cout << "Invalid" << std::endl;
        }
    }

    return 0;
}
