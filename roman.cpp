#include <bits/stdc++.h>

using namespace std;


string to_roman(int n) {
    string ans;

    vector<int> digits = {n / 1000, n / 100 % 10, n / 10 % 10, n % 10};
    vector<array<char, 3>> value_chars = {{'M', '-', '-'},
                                          {'C', 'D', 'M'},
                                          {'X', 'L', 'C'},
                                          {'I', 'V', 'X'}};
    for (int pos = 0; pos < 4; pos++) {
        if (digits[pos] < 4) {
            ans += string(digits[pos], value_chars[pos][0]);
        } else if (digits[pos] == 4) {
            ans += string(1, value_chars[pos][0]) + string(1, value_chars[pos][1]);
        } else if (digits[pos] < 9) {
            ans += string(1, value_chars[pos][1]) + string(digits[pos] - 5, value_chars[pos][0]);
        } else {
            ans += string(1, value_chars[pos][0]) + string(1, value_chars[pos][2]);
        }
    }
    return ans;
}


vector<int> roman_digit_values = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 500, 0, 0, 0, 0, 1, 0, 0, 50, 1000, 0, 0, 0,
                                  0, 0, 0, 0, 0, 5, 0, 10, 0, 0};


int from_roman(string roman) {
    int num = 0;
    for (size_t i = 0; i < roman.size(); i++) {
        if (roman.substr(i, 2) == "CM") {
            num += 900;
            i++;
        } else if (roman.substr(i, 2) == "CD") {
            num += 400;
            i++;
        } else if (roman.substr(i, 2) == "XC") {
            num += 90;
            i++;
        } else if (roman.substr(i, 2) == "XL") {
            num += 40;
            i++;
        } else if (roman.substr(i, 2) == "IX") {
            num += 9;
            i++;
        } else if (roman.substr(i, 2) == "IV") {
            num += 4;
            i++;
        } else {
            num += roman_digit_values[roman[i]];
        }
    }
    return num;
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < 4000; i++) {
        assert(i == from_roman(to_roman(i)));
    }
    return 0;
}
