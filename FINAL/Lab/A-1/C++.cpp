#include <iostream>
#include <cstring>
using namespace std;

#define MATCH cout << "\nThe Text Matches The Regular Expression";
#define NOTMATCH cout << "\nThe Text Doesn't match the Regular Expression";

char reg[20], text[20];

bool match(char reg[], char text[]) {
    int rlen = strlen(reg);
    int tlen = strlen(text);
    int i = 0, j = 0;

    while (i < rlen && j < tlen) {
        if (reg[i] == text[j] || reg[i] == '.') {  // Match single character or .
            i++;
            j++;
        } else if (reg[i] == '*') {  // Match zero or more preceding characters
            if (i == 0) return false;  // * cannot be the first character
            while (j < tlen && (text[j] == reg[i-1] || reg[i-1] == '.')) {
                j++;
            }
            i++;
        } else if (reg[i] == '+') {  // Match one or more preceding characters
            if (i == 0) return false;  // + cannot be the first character
            if (text[j] != reg[i-1] && reg[i-1] != '.') return false;
            while (j < tlen && (text[j] == reg[i-1] || reg[i-1] == '.')) {
                j++;
            }
            i++;
        } else if (reg[i] == '?') {  // Match zero or one preceding character
            if (i == 0) return false;  // ? cannot be the first character
            if (text[j] == reg[i-1] || reg[i-1] == '.') {
                j++;
            }
            i++;
        } else {
            return false;  // No match
        }
    }

    // Check if both strings are fully traversed
    return (i == rlen && j == tlen);
}

int main() {
    char ans;
    do {
        cout << "\nEnter the Regular Expression: ";
        cin.getline(reg, 20);
        cout << "\nEnter the text: ";
        cin.getline(text, 20);

        if (match(reg, text)) {
            MATCH;
        } else {
            NOTMATCH;
        }

        cout << "\nDo you want to continue? (Y/N): ";
        cin >> ans;
        cin.ignore();  // Clear the newline character from the input buffer
    } while (ans == 'Y' || ans == 'y');

    return 0;
}
