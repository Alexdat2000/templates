#include <iostream>
#include <vector>

using namespace std;


vector <int> z_function(const string& s) { // Informatics: 1324
    vector <int> z(s.size());
    z[0] = s.size();

    int l = 0, r = 0;
    for (int i = 1; i < (int) s.size(); i++) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < (int) s.size() && s[i + z[i]] == s[z[i]])
            z[i]++;
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}


vector <int> prefix_function(string s) { // Informatics: 1323
    vector <int> p(s.size(), 0);
    for (int i = 1; i < (int) s.size(); i++) {
        int j = p[i - 1];
        while (j && s[j] != s[i])
            j = p[j - 1];
        p[i] = j + (s[i] == s[j]);
    }
    return p;
}
