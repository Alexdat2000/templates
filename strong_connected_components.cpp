#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

const int N = 3e5 + 100;
vector <int> g[N];
int comp[N];
bitset <N> used;
vector <int> topsort;

void topsort_dfs(int v) {
    used.set(v);
    for (int i : g[v])
        if (!used[i])
            topsort_dfs(i);
    topsort.push_back(v);
}

void comp_dfs(int v, int com) {
    comp[v] = com;
    used.set(v);

    for (int i : g[v])
        if (!used[i])
            comp_dfs(i, com);
}

signed main() {
    // reading graph

    for (int i = 0; i < n; i++)
        if (!used[i])
            topsort_dfs(i);

    used.reset();
    int com = 0;
    for (int i = n - 1; i > -1; i--) {
        if (!used[topsort[i]]) {
            comp_dfs(topsort[i], com);
            com++;
        }
    }
    return 0;
}
