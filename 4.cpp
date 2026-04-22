#include <bits/stdc++.h>
using namespace std;

// Function to calculate gcd
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Fast modular exponentiation
long long mod_exp(long long base, long long exp, long long mod) {
    long long res = 1;
    while (exp > 0) {
        if (exp % 2 == 1)
            res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

// Modular inverse using brute (ok for small values)
int mod_inverse(int e, int phi) {
    for (int d = 1; d < phi; d++) {
        if ((e * d) % phi == 1)
            return d;
    }
    return -1;
}

int main() {
    // Step 1: Choose 2 primes
    int p = 61, q = 53;

    // Step 2: Compute n and phi
    int n = p * q;
    int phi = (p - 1) * (q - 1);

    // Step 3: Choose e
    int e = 17;
    while (gcd(e, phi) != 1) e++;

    // Step 4: Compute d
    int d = mod_inverse(e, phi);

    cout << "Public Key (e, n): (" << e << ", " << n << ")\n";
    cout << "Private Key (d, n): (" << d << ", " << n << ")\n";

    // Step 5: Read input file
    ifstream fin("input.txt");
    ofstream fout("encrypted.txt");

    string text;
    getline(fin, text);

    // Step 6: Encrypt
    for (char ch : text) {
        int m = (int)ch;
        long long c = mod_exp(m, e, n);
        fout << c << " ";
    }

    fin.close();
    fout.close();

    cout << "Encryption done -> encrypted.txt\n";

    // Step 7: Decrypt
    ifstream fin_enc("encrypted.txt");
    ofstream fout_dec("decrypted.txt");

    long long num;
    while (fin_enc >> num) {
        long long m = mod_exp(num, d, n);
        fout_dec << (char)m;
    }

    fin_enc.close();
    fout_dec.close();

    cout << "Decryption done -> decrypted.txt\n";

    return 0;
}