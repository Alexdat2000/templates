// Informatics: 113706
// HLD with operations: max on path and change element


#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int N = 5e4 + 100;
int heights[N], level[N], sz[N], link[N], parent[N];
vector <int> g[N];
int tree_index[N];
int fre = 0, n;
int tree[4 * N];


void tree_update(int v, int l, int r, int pos, int val) {
    if (r - l == 1) {
        tree[v] = val;
        return;
    }

    int m = (l + r) / 2;
    if (pos < m) {
        tree_update(v * 2 + 1, l, m, pos, val);
    } else {
        tree_update(v * 2 + 2, m, r, pos, val);
    }
    tree[v] = max(tree[v * 2 + 1], tree[v * 2 + 2]);
}

int tree_get(int ql, int qr, int v = 0, int l = 0, int r = n) {
    if (l >= qr || r <= ql)
        return INT_MIN / 2;
    if (ql <= l && r <= qr)
        return tree[v];

    int m = (l + r) / 2;
    return max(tree_get(ql, qr, v * 2 + 1, l, m), tree_get(ql, qr, v * 2 + 2, m, r));
}

void tree_count_dfs(int v, int par) {
    sz[v] = 1;
    parent[v] = par;
    for (int i : g[v]) {
        if (i == par)
            continue;
        level[i] = level[v] + 1;
        tree_count_dfs(i, v);
        sz[v] += sz[i];
    }
}

void build_paths_dfs(int v, int start) {
    tree_index[v] = fre++;
    tree_update(0, 0, n, tree_index[v], heights[v]);
    link[v] = start;

    int heavy = -1;
    for (int i : g[v]) {
        if (i == parent[v])
            continue;

        if (sz[i] * 2 >= sz[v]) {
            heavy = i;
            break;
        }
    }

    if (heavy != -1) {
        build_paths_dfs(heavy, start);
    }
    for (int i : g[v]) {
        if (i == parent[v] || i == heavy)
            continue;
        build_paths_dfs(i, i);
    }
}

void init_hld() {
    tree_count_dfs(0, -1);
    build_paths_dfs(0, 0);
}

int hld(int u, int v) {
    int p1 = link[u], p2 = link[v];

    if (p1 == p2) {
        int lc = v;
        if (level[u] <= level[v])
            lc = u;
        return max(tree_get(tree_index[lc], tree_index[u] + 1), tree_get(tree_index[lc], tree_index[v] + 1));
    }

    if (level[p1] < level[p2]) {
        return max(hld(u, parent[p2]), tree_get(tree_index[p2], tree_index[v] + 1));
    } else {
        return max(hld(parent[p1], v), tree_get(tree_index[p1], tree_index[u] + 1));
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> heights[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    init_hld();

    int q;
    cin >> q;
    while (q--) {
        char type;
        int i, j;
        cin >> type >> i >> j;
        if (type == '!') {
            tree_update(0, 0, n, tree_index[i - 1], j);
        } else {
            cout << hld(i - 1, j - 1) << "\n";
        }
    }
    return 0;
}
