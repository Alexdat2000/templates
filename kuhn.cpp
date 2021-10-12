#include <bits/stdc++.h>

#include <random>

#define all(x) (x).begin(), (x).end()
#define ll long long
#define endl "\n"

using namespace std;


int n, m;
const int N = 510;
vector <pair <int, ll>> g[N];
bool used[N], used1[N];
vector <int> pr;

ll ds;

bool dfs(int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (auto [i, ln] : g[v]) {
        if (ln > ds)
            break;

        if (pr[i] == -1) {
            pr[i] = v;
            used1[v] = true;
            return true;
        }
    }
    for (auto [i, ln] : g[v]) {
        if (ln > ds)
            break;

        if (dfs(pr[i])) {
            pr[i] = v;
            used1[v] = true;
            return true;
        }
    }
    return false;
}

vector <int> order;

bool kuhn() {
    pr.assign(m, -1);
    fill(used1, used1 + n, false);
    for (int v : order) {
        for (auto [i, ln] : g[v]) {
            if (ln > ds)
                break;

            if (pr[i] == -1) {
                pr[i] = v;
                used1[v] = true;
                break;
            }
        }
    }

    bool run = true;
    while (run) {
        run = false;
        fill(used, used + n, false);
        for (int i : order) {
            if (!used1[i] && dfs(i))
                run = true;
        }
    }
    return !count(used1, used1 + n, false);
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie();


    return 0;
}
