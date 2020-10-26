//#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

using namespace std;


const int N = 6e6 + 100;
int p[N];
vector<int> primes;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 2; i < N; i++) {
        if (p[i] == 0) {
            p[i] = i;
            primes.push_back(i);
        }
        for (int x : primes) {
            if (x > p[i] || 1LL * x * i >= N)
                break;
            p[x * i] = x;
        }
    }

    cout << primes.size() << endl;
    return 0;
}
