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

// Function to check if a function declaration is valid
bool isValidFunctionDeclaration(const std::string &declaration) {
    // Supported return types
    std::vector<std::string> returnTypes = {"void", "int", "float", "double", "char", "bool"};

    // Find the first space which separates the return type from the function name
    size_t spacePos = declaration.find(' ');
    if (spacePos == std::string::npos) {
        return false;
    }

    // Extract the return type and the rest of the declaration
    std::string returnType = declaration.substr(0, spacePos);
    std::string rest = declaration.substr(spacePos + 1);

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

    // Extract the parameter list
    std::string parameters = rest.substr(openParenPos + 1, closeParenPos - openParenPos - 1);

    // Ensure the declaration ends correctly (either with a semicolon for forward declarations or nothing for definitions)
    std::string endPart = rest.substr(closeParenPos + 1);
    // Trim whitespace
    endPart.erase(endPart.find_last_not_of(" \t\n\r\f\v") + 1);
    if (!endPart.empty() && endPart != ";") {
        return false;
    }

    return true;
}

int main() {
    // Test cases
    std::vector<std::string> testCases = {
        "void myFunction();",               // valid
        "int add(int a, int b);",           // valid
        "float computeArea(float radius);", // valid
        "double calculate(double x);",      // valid
        "char getInitial();",               // valid
        "bool isValid();",                  // valid
        "void 123invalid();",               // invalid
        "int1 invalidFuncName(int a);",     // invalid
        "float compute(,",                  // invalid
        "double calc)double x(;",           // invalid
        "char;",                            // invalid
        "bool is_valid("                    // invalid
    };

    // Check each test case
    for (const auto &test : testCases) {
        std::cout << "Checking: " << test << " -> ";
        if (isValidFunctionDeclaration(test)) {
            std::cout << "Valid" << std::endl;
        } else {
            std::cout << "Invalid" << std::endl;
        }
    }

    return 0;
}
