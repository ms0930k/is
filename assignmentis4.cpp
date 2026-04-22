#include <bits/stdc++.h>
using namespace std;

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

long long mod_exp(long long base, long long exp, long long mod) {
    long long res = 1;
    while(exp) {
        if(exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

long long mod_inverse(long long e, long long phi) {
    for(long long d = 1; d < phi; d++)
        if((e * d) % phi == 1) return d;
    return -1;
}

int main() {
    long long p = 61, q = 53;
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);

    long long e = 17;
    long long d = mod_inverse(e, phi);

    string text = "Hello world!";

    vector<long long> encrypted;

    cout << "\nEncrypted: ";
    for(char c : text) {
        long long val = mod_exp(c, e, n);
        encrypted.push_back(val);
        cout << val << " ";
    }

    cout << "\nDecrypted: ";
    for(long long val : encrypted) {
        char c = (char)mod_exp(val, d, n);
        cout << c;
    }

    cout << endl;
}