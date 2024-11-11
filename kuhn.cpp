#include <bits/stdc++.h>

#include <random>

#define all(x) (x).begin(), (x).end()
#define ll long long
#define endl "\n"

using namespace std;


int n, m;  // left half size, right half size
const int N = 1e5;
vector <int> g[N];  // n
bool used[N], used1[N];  // n, n
int pr[N]; // m


bool dfs(int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (int i : g[v]) {
        if (pr[i] == -1) {
            pr[i] = v;
            used1[v] = true;
            return true;
        }
    }
    for (int i : g[v]) {
        if (dfs(pr[i])) {
            pr[i] = v;
            used1[v] = true;
            return true;
        }
    }
    return false;
}

int kuhn() {
    fill(used1, used1 + n, false);
    fill(pr, pr + m, -1);
    // for (int v = 0; v < n; v++) {
    //     for (int i : g[v]) {
    //         if (pr[i] == -1) {
    //             pr[i] = v;
    //             used1[v] = true;
    //             break;
    //         }
    //     }
    // }

    bool run = true;
    while (run) {
        run = false;
        fill(used, used + n, false);
        for (int i = 0; i < n; i++) {
            if (!used1[i] && dfs(i))
                run = true;
        }
    }
    return count(used1, used1 + n, true);  // returns matching size
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);


    return 0;
}
