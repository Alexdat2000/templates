// https://codeforces.com/edu/course/2/lesson/5/2/practice/contest/279653/problem/A
// segment tree with operations: get min on segment and add val to segment
// author: Alexdat2000

#include <iostream>
#include <climits>

#define int long long

using namespace std;


const int N = 1e5 + 100;
int tree_min[4 * N], modif[4 * N];


void push(int v, int l, int r) {
    if (modif[v] == 0)
        return;
    tree_min[v] += modif[v];
    if (r - l > 1) {
        modif[v * 2 + 1] += modif[v], modif[v * 2 + 2] += modif[v];
    }
    modif[v] = 0;
}


void mass_add(int v, int l, int r, int ql, int qr, int val) {
    push(v, l, r);

    if (ql <= l && r <= qr) {
        modif[v] += val;
        push(v, l, r);
        return;
    }

    if (l >= qr || r <= ql)
        return;

    int m = (l + r) / 2;
    mass_add(v * 2 + 1, l, m, ql, qr, val);
    mass_add(v * 2 + 2, m, r, ql, qr, val);
    tree_min[v] = min(tree_min[v * 2 + 1], tree_min[v * 2 + 2]);
}

int get_min(int v, int l, int r, int ql, int qr) {
    push(v, l, r);

    if (ql <= l && r <= qr) {
        return tree_min[v];
    }

    if (l >= qr || r <= ql)
        return LLONG_MAX / 2;

    int m = (l + r) / 2;
    return min(get_min(v * 2 + 1, l, m, ql, qr), get_min(v * 2 + 2, m, r, ql, qr));
}

signed main() {
    int n, q;
    cin >> n >> q;

    for (int _ = 1; _ <= q; _++) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r, val;
            cin >> l >> r >> val;
            mass_add(0, 0, n, l, r, val);
        } else {
            int l, r;
            cin >> l >> r;
            cout << get_min(0, 0, n, l, r) << "\n";
        }
    }
    return 0;
}
