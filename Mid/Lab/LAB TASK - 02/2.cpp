#include <iostream>
using namespace std;

int main() {
    char input[100];
    cin.getline(input, 100);

    int length = 0;
    while (input[length] != '\0') {
        length++;
    }

    if (input[0] == '/' && input[1] == '/') {
        cout << "This is a single line comment." << endl;
    }

    else if (input[0] == '/' && input[1] == '*' && input[length - 2] == '*' && input[length - 1] == '/') {
        cout << "This is a multi line comment." << endl;
    }
    else {
        cout << "This is not a comment." << endl;
    }

    return 0;
}
