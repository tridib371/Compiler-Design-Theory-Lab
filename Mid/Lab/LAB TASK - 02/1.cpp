#include <iostream>
#include <cstring>

using namespace std;

bool isOperator(char ch) {

    char operators[] = {'+', '-', '*', '/', '=', '<', '>', '!', '%', '&', '|', '^', '~'};
    for (int i = 0; i < sizeof(operators); i++) {
        if (ch == operators[i]) {
            return true;
        }
    }
    return false;
}

int main() {
    char input[100];
    char operators[100];
    int operatorCount = 0;

    cout << "Enter the input string: ";
    cin.getline(input, 100);

    int length = strlen(input);
    for (int i = 0; i < length; i++) {
        if (isOperator(input[i])) {
            operators[operatorCount++] = input[i];
        }
    }

    for (int i = 0; i < operatorCount; i++) {
        cout << "operator" << i + 1 << ":" << operators[i] << endl;
    }
    cout << "number of operators=" << operatorCount << endl;

    return 0;
}
