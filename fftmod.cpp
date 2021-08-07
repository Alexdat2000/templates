#include <bits/stdc++.h>

using namespace std;
#define all(x) begin(x), end(x)
#define endl "\n"
#define int long long

vector<int> w;
const int MOD = 7340033, DEG = 18, LEN = (1 << DEG);

int po(int a, int n) {
    int ans = 1;
    while (n) {
        if (n & 1) {
            ans = ans * a % MOD;
        }
        a = a * a % MOD;
        n >>= 1;
    }
    return ans;
}

const int LEN_REV = po(LEN, MOD - 2);

void fft(vector<int>& a) {
    for (int i = 0; i < LEN; i++) {
        int x = 0;
        for (int j = 0; j < DEG; j++) {
            x += ((i >> j) & 1) << (DEG - j - 1);
        }
        if (i < x) {
            swap(a[i], a[x]);
        }
    }

    for (int ln = 2; ln <= LEN; ln <<= 1) {
        for (int i = 0; i < LEN; i += ln) {
            for (int j = 0; j < ln / 2; j++) {
                int u = a[i + j], v = a[i + j + ln / 2] * w[LEN / ln * j] % MOD;
                a[i + j] = (u + v) % MOD, a[i + j + ln / 2] = (u - v + MOD) % MOD;
            }
        }
    }
}


vector <int> mul(vector <int> a, vector <int> b) {
    fft(a), fft(b);
    vector<int> c(LEN);
    for (int i = 0; i < LEN; i++)
        c[i] = a[i] * b[i] % MOD;
    fft(c);

    for (auto& i : c)
        i = i * LEN_REV % MOD;
    reverse(1 + all(c));
    return c;
}

vector <int> mul(vector <int> a) {
    fft(a);
    vector<int> c(LEN);
    for (int i = 0; i < LEN; i++)
        c[i] = a[i] * a[i] % MOD;
    fft(c);

    for (auto& i : c)
        i = i * LEN_REV % MOD;
    reverse(1 + all(c));
    return c;
}

vector <int> neg(vector <int> a) {
    for (int& i : a)
        i = (MOD - i % MOD) % MOD;
    return a;
}

vector <int> add(vector <int> a, const vector <int>& b) {
    for (int i = 0; i < LEN; i++)
        a[i] = (a[i] + b[i]) % MOD;
    return a;
}

vector <int> mul(vector <int> a, int x) {
    for (int& i : a)
        i = i * x % MOD;
    return a;
}


signed main() {
    w.resize(LEN);
    w[0] = 1;
    int k = po(3, (MOD - 1) / LEN);
    for (int i = 1; i < LEN; i++)
        w[i] = (w[i - 1] * k) % MOD;

    return 0;
}