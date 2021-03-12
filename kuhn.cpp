#include <bits/stdc++.h>

using namespace std;

const int N = 155;
vector <int> g[N];
int mt[N];
bool used[N];

bool kuhn(int v) {
    if (used[v])
        return false;

    used[v] = true;
    for (int i : g[v]) {
        if (mt[i] == -1 || kuhn(mt[i])) {
            mt[i] = v;
            return true;
        }
    }
    return false;
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fill(mt, mt + N, -1);

    int n = 150;

    for (int i = 0; i < n; i++) {
        fill(used, used + N, false);
        kuhn(i);
    }

    vector <pair <int, int>> match;
    for (int i = 0; i < m; i++) {
        if (mt[i] != -1) {
            match.emplace_back(mt[i], i);
        }
    }
    return 0;
}
