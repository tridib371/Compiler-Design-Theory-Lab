#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <vector>
#include <set>

using namespace std;

struct Jag {
    char index[20];
};

Jag eNFA[20][20], NFA[20][20], DFA[20][20], discuss[20];
char result[30][30], copy, copy1, states[20], symbols[20], states2[40], backup[40], cat[40], ch;
bool access = false;
int eNFA_r = 0, eNFA_c = 0, NFA_r = 0, NFA_c = 0, DFA_r = 0, DFA_c = 0, plen = -1, dlen = -1, nlen = -1, s, s1, g;

int size(const char *p) {
    return strlen(p);
}

void input_NFA() {
    int state, symbol, a;
    NFA[0][0].index[0] = '-';
    cout << "**Total number of states: ";
    cin >> state;
    cin.ignore();
    NFA_r = state;
    cout << "**Enter states with a space: ";
    for (int i = 1; i <= NFA_r; i++) {
        char x;
        cin >> x;
        NFA[i][0].index[0] = x;
        states[i - 1] = x;
    }
    cin.ignore();
    cout << "**Total number of symbols: ";
    cin >> symbol;
    cin.ignore();
    NFA_c = symbol;
    cout << "**Enter symbols with a space: ";
    for (int i = 1; i <= NFA_c; i++) {
        char x;
        cin >> x;
        NFA[0][i].index[0] = x;
        DFA[0][i].index[0] = x;
        symbols[i - 1] = x;
    }
    cin.ignore();

    for (int i = 1; i <= NFA_r; i++) {
        for (int j = 1; j <= NFA_c; j++) {
            NFA[i][j].index[0] = 'P';
        }
    }

    for (int i = 1; i <= NFA_r; i++) {
        for (int l = 1; l <= NFA_c; l++) {
            string str;
            cout << "\n**Transitions of { " << NFA[i][0].index[0] << " } with symbol { " << NFA[0][l].index[0] << " }: \nExample: X,Y,Z and PRESS <enter> for no transition.\n>> ";
            getline(cin, str);

            int s2 = size(str.c_str());
            if (s2 > nlen) {
                nlen = s2;
            }

            ofstream fptr("transition.txt", ios::app);
            for (char c : str) {
                if (c != ',') {
                    fptr << NFA[i][0].index[0] << " " << NFA[0][l].index[0] << " " << c << endl;
                }
            }
            fptr.close();

            if (!str.empty() && isalpha(str[0])) {
                strcpy(NFA[i][l].index, str.c_str());
            }
        }
    }
}

void input_eNFA() {
    int state, symbol, a;
    eNFA[0][0].index[0] = '-';
    cout << "**Total number of states: ";
    cin >> state;
    cin.ignore();
    eNFA_r = state;
    cout << "**Enter states with a space: ";
    for (int i = 1; i <= eNFA_r; i++) {
        char x;
        cin >> x;
        eNFA[i][0].index[0] = x;
        states[i - 1] = x;
    }
    cin.ignore();
    cout << "**Total number of symbols: ";
    cin >> symbol;
    cin.ignore();
    eNFA_c = symbol;
    cout << "**Enter symbols with a space: ";
    for (int i = 1; i <= eNFA_c; i++) {
        char x;
        cin >> x;
        eNFA[0][i].index[0] = x;
        symbols[i - 1] = x;
    }
    cin.ignore();

    for (int i = 1; i <= eNFA_r; i++) {
        for (int j = 1; j <= eNFA_c; j++) {
            eNFA[i][j].index[0] = 'P';
        }
    }

    for (int i = 1; i <= eNFA_r; i++) {
        for (int l = 1; l <= eNFA_c; l++) {
            string str;
            cout << "\n**Transitions of { " << eNFA[i][0].index[0] << " } with symbol { " << eNFA[0][l].index[0] << " }: \nExample: X,Y,Z and PRESS <enter> for no transition.\n>> ";
            getline(cin, str);

            int s2 = size(str.c_str());
            if (s2 > plen) {
                plen = s2;
            }

            ofstream fptr("transition.txt", ios::app);
            for (char c : str) {
                if (c != ',') {
                    fptr << eNFA[i][0].index[0] << " " << eNFA[0][l].index[0] << " " << c << endl;
                }
            }
            fptr.close();

            if (!str.empty() && (isalpha(str[0]) || isdigit(str[0]))) {
                strcpy(eNFA[i][l].index, str.c_str());
            }
        }
    }
}

void show_eNFA() {
    cout << "\n.....................................\n";
    for (int i = 0; i <= eNFA_r; i++) {
        for (int j = 0; j <= eNFA_c; j++) {
            int l = 0;
            while (eNFA[i][j].index[l] != '\0') {
                cout << (eNFA[i][j].index[l] == 'P' ? ' ' : eNFA[i][j].index[l]);
                l++;
            }
            int s2 = size(eNFA[i][j].index);
            cout << string(plen - s2 + 1, ' ');
        }
        cout << "\n";
    }
}

void show_NFA() {
    cout << "\n     \"\"Inputed NFA\"\"\n";
    cout << ".....................................\n";

    for (int i = 0; i <= NFA_r; i++) {
        for (int j = 0; j <= NFA_c; j++) {
            int l = 0;
            while (NFA[i][j].index[l] != '\0') {
                cout << (NFA[i][j].index[l] == 'P' ? ' ' : NFA[i][j].index[l]);
                l++;
            }
            int s2 = size(NFA[i][j].index);
            cout << string(nlen - s2 + 1, ' ');
        }
        cout << "\n";
    }
}

void show_DFA() {
    cout << "\n   \"\"Displaying Converted DFA\"\"\n";
    cout << ".....................................\n";

    DFA[0][0].index[0] = '-';
    for (int i = 0; i <= DFA_r + 1; i++) {
        for (int j = 0; j <= DFA_c + 1; j++) {
            int l = 0;
            int fl = 0;
            int s2 = size(DFA[i][j].index);
            while (DFA[i][j].index[l] != '\0') {
                if (DFA[i][j].index[l] == 'P') {
                    cout << ' ';
                } else if (DFA[i][j].index[l] == ',') {
                    fl++;
                } else {
                    cout << DFA[i][j].index[l];
                }
                l++;
            }
            s2 -= fl;
            cout << string(dlen - s2 + 2, ' ');
        }
        cout << "\n";
    }
}

void append(char a, int n, int r) {
    result[n][r] = a;
}

void append1(char a, int r) {
    states2[r] = a;
}

void append_dfa(char a, int r) {
    backup[r] = a;
}

char* removeDuplicates(char arr[], int n) {
    set<char> unique_chars(arr, arr + n);
    int i = 0;
    for (char c : unique_chars) {
        arr[i++] = c;
    }
    arr[i] = '\0';
    return arr;
}

void display() {
    for (int j = 0; j < s; j++) {
        int col = size(result[j]);
        cout << "\n**Epsilon closure of " << states[j] << " = { ";
        for (int i = 0; i < col; i++) {
            cout << " " << result[j][i];
            if (result[j][i + 1] == '\0') {
                cout << " ";
            } else {
                cout << ",";
            }
        }
        cout << " }";
    }
    cout << "\n.....................................";
}

int check(char c, char *p, int col) {
    for (int i = 0; i <= col; i++) {
        if (c == p[i]) {
            return 0;
        }
    }
    return 1;
}

int check_symbol(char c, char *p) {
    for (int i = 0; i <= dlen; i++) {
        if (c == p[i]) {
            return 0;
        }
    }
    return 1;
}

void concatenate(char *res, char *b) {
    strcat(res, ",");
    strcat(res, b);
}

void add_states(char *p, char *res) {
    char temp[20];
    int i = 0;
    while (p[i] != '\0') {
        if (check(p[i], res, strlen(res))) {
            strncat(res, &p[i], 1);
        }
        i++;
    }
}

void get_epsilon_closure(int index) {
    for (int i = 1; i <= eNFA_r; i++) {
        if (eNFA[i][0].index[0] == states[index]) {
            strcat(result[index], eNFA[i][eNFA_c].index);
            for (int j = 1; j <= strlen(eNFA[i][eNFA_c].index); j++) {
                for (int k = 1; k <= eNFA_r; k++) {
                    if (eNFA[k][0].index[0] == eNFA[i][eNFA_c].index[j - 1]) {
                        strcat(result[index], eNFA[k][eNFA_c].index);
                    }
                }
            }
        }
    }
    removeDuplicates(result[index], strlen(result[index]));
}

void epsilon_closure() {
    for (int i = 0; i < s; i++) {
        strcat(result[i], states + i);
        get_epsilon_closure(i);
    }
}

void nfa_to_dfa() {
    DFA[1][0].index[0] = states[0];
    DFA_r++;
    for (int i = 1; i <= DFA_r; i++) {
        for (int j = 1; j <= NFA_c; j++) {
            char res[20] = "";
            for (int k = 0; DFA[i][0].index[k] != '\0'; k++) {
                int x;
                for (x = 1; x <= NFA_r; x++) {
                    if (NFA[x][0].index[0] == DFA[i][0].index[k]) {
                        break;
                    }
                }
                strcat(res, NFA[x][j].index);
            }
            removeDuplicates(res, strlen(res));
            if (strlen(res) > 0) {
                strcpy(DFA[i][j].index, res);
                bool check_new_state = true;
                for (int m = 1; m <= DFA_r; m++) {
                    if (strcmp(DFA[m][0].index, res) == 0) {
                        check_new_state = false;
                        break;
                    }
                }
                if (check_new_state) {
                    DFA_r++;
                    strcpy(DFA[DFA_r][0].index, res);
                }
            }
        }
    }
}

void run() {
    input_eNFA();
    show_eNFA();
    epsilon_closure();
    display();
    input_NFA();
    show_NFA();
    nfa_to_dfa();
    show_DFA();
}

int main() {
    run();
    return 0;
}
