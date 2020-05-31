// https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/B
// segment tree with operations: get min on segment and change 1 element
// author: Alexdat2000

#include <iostream>

#define int long long

using namespace std;

const int N = 1e5 + 100;
int a[N], tree_min[4 * N];

void build(int v, int l, int r) {
    if (r - l == 1) {
        tree_min[v] = a[l];
        return;
    }

    int m = (l + r) / 2;
    build(v * 2 + 1, l, m);
    build(v * 2 + 2, m, r);
    tree_min[v] = min(tree_min[v * 2 + 1], tree_min[v * 2 + 2]);
}

int get_min(int v, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return tree_min[v];
    if (l >= qr || r <= ql)
        return INT_MAX;

    int m = (l + r) / 2;
    return min(get_min(v * 2 + 1, l, m, ql, qr), get_min(v * 2 + 2, m, r, ql, qr));
}

void upd(int v, int l, int r, int pos, int val) {
    if (r - l == 1) {
        tree_min[v] = a[l] = val;
        return;
    }

    int m = (l + r) / 2;
    if (pos < m)
        upd(v * 2 + 1, l, m, pos, val);
    else
        upd(v * 2 + 2, m, r, pos, val);
    tree_min[v] = min(tree_min[v * 2 + 1], tree_min[v * 2 + 2]);
}

signed main() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    build(0, 0, n);

    while (q--) {
        int type, x, y;  // type = 1 - update, type = 2 - get
        cin >> type >> x >> y;  // 0-indexing
        if (type == 1) {
            upd(0, 0, n, x, y); // a[x] = y
        } else {
            cout << get_min(0, 0, n, x, y) << "\n";  // min(a[x], a[x + 1], \ldots, a[y - 1])
        }
    }
    return 0;
}
