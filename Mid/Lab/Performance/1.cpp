#include <iostream>
#include <stack>
#include <string>

bool isValidCharacter(char c) {
    return (c >= '0' && c <= '9') || c == ' ' || c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')';
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isBalancedParentheses(const std::string& expression) {
    std::stack<char> parentheses;
    for (char c : expression) {
        if (c == '(') {
            parentheses.push(c);
        } else if (c == ')') {
            if (parentheses.empty() || parentheses.top() != '(') {
                return false;
            }
            parentheses.pop();
        }
    }
    return parentheses.empty();
}

bool isValidExpression(const std::string& expression) {
    if (!isBalancedParentheses(expression)) {
        return false;
    }

    bool lastWasOperator = true;
    for (char c : expression) {
        if (!isValidCharacter(c)) {
            return false;
        }
        if (c >= '0' && c <= '9') {
            lastWasOperator = false;
        } else if (isOperator(c)) {
            if (lastWasOperator) {
                return false;
            }
            lastWasOperator = true;
        } else if (c == '(') {
            lastWasOperator = true;
        } else if (c == ')') {
            if (lastWasOperator) {
                return false;
            }
        }
    }
    return !lastWasOperator;
}

int main() {
    std::string expression;
    char choice;

    do {
        std::cout << "Enter a mathematical expression: ";
        std::getline(std::cin, expression);

        if (isValidExpression(expression)) {
            std::cout << "The expression is valid." << std::endl;
        } else {
            std::cout << "The expression is invalid." << std::endl;
        }

        std::cout << "Do you want to check another expression? (y/n): ";
        std::cin >> choice;
        std::cin.ignore();
    }
     while (choice == 'y' || choice == 'Y');

    return 0;
}
