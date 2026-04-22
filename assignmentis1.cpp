#include <iostream>
using namespace std;

int main() {
    char str[] = "Hello World";

    cout << "Original String: " << str << endl;

    cout << "After AND with 127: ";
    for (int i = 0; str[i] != '\0'; i++) {
        char ch = str[i] & 127;
        cout << ch;
    }
    cout << endl;

    cout << "After XOR with 127: ";
    for (int i = 0; str[i] != '\0'; i++) {
        char ch = str[i] ^ 127;
        cout << ch;
    }
    cout << endl;

    return 0;
}