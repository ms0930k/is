#include <bits/stdc++.h>
using namespace std;

string fake_md5(string input) {
    long long hash_val = 0;

    for (char c : input) {
        hash_val = (hash_val * 31 + c) % 1000000007;
    }

    stringstream ss;
    ss << hex << hash_val;
    string hash = ss.str();

    while (hash.length() < 8)
        hash = "0" + hash;

    return hash;
}

int main() {
    string data;
    int difficulty;

    cout << "Enter data: ";
    getline(cin, data);

    cout << "Enter difficulty (number of leading zeros): ";
    cin >> difficulty;

    string target(difficulty, '0');
    int nonce = 83808000;


    while (true) {
        string input = data + to_string(nonce);
        string hash = fake_md5(input);

        if (hash.substr(0, difficulty) == target) {
            cout << "\nBlock Mined!\n";
            cout << "Data: " << data << endl;
            cout << "Nonce: " << nonce << endl;
            cout << "Hash: " << hash << endl;
            break;
        }

        if (nonce % 100000 == 0) {
            cout << "Trying nonce: " << nonce << " | Hash: " << hash << endl;
        }

        nonce++;
    }

    return 0;
}