#include <bits/stdc++.h>
#include <openssl/md5.h>
using namespace std;

string md5(string input) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5((unsigned char*)input.c_str(), input.size(), digest);

    stringstream ss;
    for(int i=0;i<MD5_DIGEST_LENGTH;i++)
        ss << hex << setw(2) << setfill('0') << (int)digest[i];
    return ss.str();
}

int main() {
    string data = "hello";
    string target = "0000";
    int nonce = 0;

    while(true) {
        string input = data + to_string(nonce);
        string hash = md5(input);

        if(hash.substr(0, target.size()) == target) {
            cout << "Nonce: " << nonce << endl;
            cout << "Hash: " << hash << endl;
            break;
        }
        nonce++;
    }
}