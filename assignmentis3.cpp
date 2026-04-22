#include <bits/stdc++.h>
using namespace std;

// Permutations
int P10[] = {3,5,2,7,4,10,1,9,8,6};
int P8[]  = {6,3,7,4,8,5,10,9};
int IP[]  = {2,6,3,1,4,8,5,7};
int IP_INV[] = {4,1,3,5,7,2,8,6};
int EP[] = {4,1,2,3,2,3,4,1};
int P4[] = {2,4,3,1};

int S0[4][4] = {{1,0,3,2},{3,2,1,0},{0,2,1,3},{3,1,3,2}};
int S1[4][4] = {{0,1,2,3},{2,0,1,3},{3,0,1,0},{2,1,0,3}};

string permute(string k, int *arr, int n) {
    string res = "";
    for(int i=0;i<n;i++) res += k[arr[i]-1];
    return res;
}

string shift_left(string k, int shifts) {
    rotate(k.begin(), k.begin()+shifts, k.end());
    return k;
}

string XOR(string a, string b) {
    string res = "";
    for(int i=0;i<a.size();i++)
        res += (a[i] == b[i]) ? '0' : '1';
    return res;
}

string sbox(string input) {
    int row = (input[0]-'0')*2 + (input[3]-'0');
    int col = (input[1]-'0')*2 + (input[2]-'0');
    return bitset<2>(S0[row][col]).to_string();
}

string sbox1(string input) {
    int row = (input[0]-'0')*2 + (input[3]-'0');
    int col = (input[1]-'0')*2 + (input[2]-'0');
    return bitset<2>(S1[row][col]).to_string();
}

string fk(string left, string right, string key) {
    string temp = permute(right, EP, 8);
    temp = XOR(temp, key);

    string left_s = sbox(temp.substr(0,4));
    string right_s = sbox1(temp.substr(4,4));

    string combined = permute(left_s + right_s, P4, 4);
    return XOR(left, combined);
}

pair<string,string> generate_keys(string key) {
    key = permute(key, P10, 10);
    string left = key.substr(0,5), right = key.substr(5,5);

    left = shift_left(left,1);
    right = shift_left(right,1);
    string k1 = permute(left+right, P8, 8);

    left = shift_left(left,2);
    right = shift_left(right,2);
    string k2 = permute(left+right, P8, 8);

    return {k1, k2};
}

string encrypt(string pt, string k1, string k2) {
    pt = permute(pt, IP, 8);
    string left = pt.substr(0,4), right = pt.substr(4,4);

    string left1 = fk(left, right, k1);
    swap(left1, right);

    string left2 = fk(left1, right, k2);
    return permute(left2 + right, IP_INV, 8);
}

int main() {
    string key = "1010000010";
    string plaintext = "10101010";

    auto keys = generate_keys(key);
    string cipher = encrypt(plaintext, keys.first, keys.second);

    cout << "Cipher: " << cipher << endl;
}