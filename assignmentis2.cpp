#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

string encrypt(string text, int key) {
    int len = text.length();
    int rows = ceil((double)len / key);

    vector<vector<char>> grid(rows, vector<char>(key, 'X'));

    int k = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < key; j++) {
            if (k < len)
                grid[i][j] = text[k++];
        }
    }

    string cipher = "";
    for (int j = 0; j < key; j++) {
        for (int i = 0; i < rows; i++) {
            cipher += grid[i][j];
        }
    }

    return cipher;
}


string decrypt(string cipher, int key) {
    int len = cipher.length();
    int rows = ceil((double)len / key);

    vector<vector<char>> grid(rows, vector<char>(key));

    int k = 0;
    for (int j = 0; j < key; j++) {
        for (int i = 0; i < rows; i++) {
            if (k < len)
                grid[i][j] = cipher[k++];
        }
    }

    string text = "";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < key; j++) {
            text += grid[i][j];
        }
    }

    return text;
}

int main() {
    string text = "HELLOWORLD";
    int key = 4;

    cout << "Original Text: " << text << endl;

    string cipher = encrypt(text, key);
    cout << "Encrypted Text: " << cipher << endl;

    string decrypted = decrypt(cipher, key);
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}