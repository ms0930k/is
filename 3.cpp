#include <bits/stdc++.h>
using namespace std;

int P10[] = {3,5,2,7,4,10,1,9,8,6};
int P8[]  = {6,3,7,4,8,5,10,9};
int P4[]  = {2,4,3,1};
int IP[]  = {2,6,3,1,4,8,5,7};
int IP_INV[] = {4,1,3,5,7,2,8,6};
int EP[]  = {4,1,2,3,2,3,4,1};

int S0[4][4] = {
    {1,0,3,2},
    {3,2,1,0},
    {0,2,1,3},
    {3,1,3,2}
};

int S1[4][4] = {
    {0,1,2,3},
    {2,0,1,3},
    {3,0,1,0},
    {2,1,0,3}
};

string permute(string k, int arr[], int n) {
    string res = "";
    for(int i = 0; i < n; i++)
        res += k[arr[i]-1];
    return res;
}

string shift_left(string k, int shifts) {
    return k.substr(shifts) + k.substr(0, shifts);
}

string xor_op(string a, string b) {
    string res = "";
    for(int i = 0; i < a.size(); i++)
        res += (a[i] == b[i]) ? '0' : '1';
    return res;
}

string sbox_lookup(string input, int sbox[4][4]) {
    int row = (input[0]-'0')*2 + (input[3]-'0');
    int col = (input[1]-'0')*2 + (input[2]-'0');
    int val = sbox[row][col];
    return bitset<2>(val).to_string();
}

string f_function(string right, string key) {
    string expanded = permute(right, EP, 8);
    string xored = xor_op(expanded, key);

    string left = xored.substr(0,4);
    string right_part = xored.substr(4,4);

    string s0_out = sbox_lookup(left, S0);
    string s1_out = sbox_lookup(right_part, S1);

    string combined = s0_out + s1_out;
    return permute(combined, P4, 4);
}

string fk(string left, string right, string key) {
    string f_out = f_function(right, key);
    string new_left = xor_op(left, f_out);
    return new_left + right;
}

int main() {
    string key = "1010000010";
    string plaintext = "10101010";

    string p10 = permute(key, P10, 10);
    string left = p10.substr(0,5);
    string right = p10.substr(5,5);

    left = shift_left(left,1);
    right = shift_left(right,1);

    string k1 = permute(left+right, P8, 8);

    left = shift_left(left,2);
    right = shift_left(right,2);

    string k2 = permute(left+right, P8, 8);

    string ip = permute(plaintext, IP, 8);
    left = ip.substr(0,4);
    right = ip.substr(4,4);

    string temp = fk(left, right, k1);

    left = temp.substr(4,4);
    right = temp.substr(0,4);

    temp = fk(left, right, k2);

    string cipher = permute(temp, IP_INV, 8);

    cout << "Encrypted: " << cipher << endl;

    ip = permute(cipher, IP, 8);
    left = ip.substr(0,4);
    right = ip.substr(4,4);

    temp = fk(left, right, k2);

    left = temp.substr(4,4);
    right = temp.substr(0,4);

    temp = fk(left, right, k1);

    string decrypted = permute(temp, IP_INV, 8);

    cout << "Decrypted: " << decrypted << endl;

    return 0;
}