#include <iostream>
#include <vector>

using namespace std;

int n, tim = 0;
const int N = 1e5 + 100, LG = 20;
int tin[N], tout[N];
vector<int> g[N];

int bin[LG][N]; // 2^i-th ancestor of j

void dfs(int v, int p) {
    tin[v] = ++tim;
    bin[0][v] = p;
    for (int i = 1; i < LG; i++)
        bin[i][v] = bin[i - 1][bin[i - 1][v]];

    for (int i : g[v]) {
        if (i == p)
            continue;
        dfs(i, v);
    }
    tout[v] = ++tim;
}

bool is_upper(int v, int u) { // if v an ancestor of u
    return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int get_lca(int a, int b) {
    if (is_upper(a, b))
        return a;
    if (is_upper(b, a))
        return b;
    for (int i = LG - 1; i >= 0; i--)
        if (!is_upper(bin[i][a], b))
            a = bin[i][a];
    return bin[0][a];
}

signed main() {
    // read

    int root = 0;

    dfs(root, root); // build dfs

    // solve

    return 0;
}
