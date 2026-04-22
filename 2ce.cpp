#include <bits/stdc++.h>
using namespace std;

string columnar_encrypt(string text, string key) {
    int col = key.length();
    int row = ceil((float)text.length() / col);

    vector<vector<char>> grid(row, vector<char>(col, 'X'));

    int k = 0;
    for (int i = 0; i < row && k < text.length(); i++) {
        for (int j = 0; j < col && k < text.length(); j++) {
            grid[i][j] = text[k++];
        }
    }

    vector<pair<char, int>> key_map;
    for (int i = 0; i < col; i++) {
        key_map.push_back({key[i], i});
    }
    sort(key_map.begin(), key_map.end());

    string result = "";
    for (auto it : key_map) {
        int col_idx = it.second;
        for (int i = 0; i < row; i++) {
            result += grid[i][col_idx];
        }
    }

    return result;
}

int main() {
    string text = "HELLOWORLD";
    string key = "ZEBRA";

    cout << "Encrypted: " << columnar_encrypt(text, key);
}