#include <bits/stdc++.h>

#define endl "\n"
#define all(x) (x).begin(), (x).end()

using namespace std;

struct node {
    int nx[26]{}, link, pre, len{};

    node() {
        for (auto &i : nx)
            i = -1;
        link = -1, pre = -1;
    }
};

const int N = 2e5 + 100;
node s[N]{};
int fre = 1;

long long add(long long a, long long ch) {
    long long b = fre++;

    s[b].pre = a;
    s[b].len = s[a].len + 1;
    s[b].link = 0;

    for (; a != -1; a = s[a].link) {
        if (s[a].nx[ch] == -1) {
            s[a].nx[ch] = b;
            continue;
        }

        long long c = s[a].nx[ch];
        if (s[c].pre == a) {
            s[b].link = c;
            break;
        }

        long long d = fre++;

        s[d].link = s[c].link;
        s[c].link = d;
        s[b].link = d;

        if (s[a].nx[ch] == c) {
            s[d].pre = a;
            s[d].len = s[a].len + 1;
        }

        for (long long i = 0; i < 26; i++)
            s[d].nx[i] = s[c].nx[i];

        for (; a != -1 && s[a].nx[ch] == c; a = s[a].link) {
            s[a].nx[ch] = d;
        }
        break;
    }
    return s[s[b].pre].nx[ch];
}

vector <int> term;


signed main() {
    string t;
    long long a = 0;
    for (char c : t) {
        a = add(a, c - 'a');
    }

    term.assign(fre, 0);
    while (a != -1) {
        term[a] = true;
        assert(a != s[a].link);
        a = s[a].link;
    }
}
