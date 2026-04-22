#include <bits/stdc++.h>
using namespace std;

int main()
{
    string str;
    int num;

    cout << "Enter a string: ";
    getline(cin, str);

    cout << "Enter a number: ";
    cin >> num;

    string and_string = "";
    string xor_string = "";

    // Calculate
    for (int i = 0; i < str.length(); i++)
    {
        and_string += char(str[i] & num);
        xor_string += char(str[i] ^ num);
    }

    // Final Output
    cout << "\n--- Final Output ---\n";
    cout << "AND String: " << and_string << endl;
    cout << "XOR String: " << xor_string << endl;

    return 0;
}