#include <bits/stdc++.h>
using namespace std;

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

long long power_mod(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;

        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

long long mod_inverse(long long e, long long phi) {
    for (long long d = 1; d < phi; d++) {
        if ((e * d) % phi == 1)
            return d;
    }
    return -1;
}

int main() {
    long long p = 61, q = 53;
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    long long e = 17;
    if (gcd(e, phi) != 1) {
        cout << "Invalid e value!" << endl;
        return 0;
    }

    long long d = mod_inverse(e, phi); 

    cout << "Public Key (e, n): (" << e << ", " << n << ")" << endl;
    cout << "Private Key (d, n): (" << d << ", " << n << ")" << endl;

    // File input
    ifstream fin("input.txt");
    ofstream fout_enc("encrypted.txt");
    ofstream fout_dec("decrypted.txt");

    string text;
    getline(fin, text);

    vector<long long> encrypted;
    for (char c : text) {
        long long enc = power_mod((int)c, e, n);
        encrypted.push_back(enc);
        fout_enc << enc << " ";
    }
    for (long long val : encrypted) {
        char dec = (char)power_mod(val, d, n);
        fout_dec << dec;
    }

    fin.close();
    fout_enc.close();
    fout_dec.close();

    cout << "\nEncryption & Decryption done. Check files." << endl;

    return 0;
}