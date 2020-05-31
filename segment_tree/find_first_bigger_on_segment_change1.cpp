// https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/D
// segment tree with operations: find min j >= l: a[j] >= x, change 1 element
// author: Alexdat2000

#include <iostream>

#define int long long

using namespace std;

const int N = 1e5 + 100;
int a[N], tree_max[4 * N];

void build(int v, int l, int r) {
    if (r - l == 1) {
        tree_max[v] = a[l];
        return;
    }

    int m = (l + r) / 2;
    build(v * 2 + 1, l, m);
    build(v * 2 + 2, m, r);
    tree_max[v] = max(tree_max[v * 2 + 1], tree_max[v * 2 + 2]);
}

int find_bigger(int v, int l, int r, int ql, int qr, int val) {  // find max ql <= j < qr: a[j] >= val or -1 if not exists
    if (ql >= r || qr <= l || tree_max[v] < val)
        return -1;

    if (r - l == 1)
        return l;

    int ans_l = find_bigger(v * 2 + 1, l, (l + r) / 2, ql, qr, val);
    if (ans_l != -1)
        return ans_l;
    return find_bigger(v * 2 + 2, (l + r) / 2, r, ql, qr, val);
}

void upd(int v, int l, int r, int pos, int val) {
    if (r - l == 1) {
        tree_max[v] = a[l] = val;
        return;
    }

    int m = (l + r) / 2;
    if (pos < m)
        upd(v * 2 + 1, l, m, pos, val);
    else
        upd(v * 2 + 2, m, r, pos, val);
    tree_max[v] = max(tree_max[v * 2 + 1], tree_max[v * 2 + 2]);
}

signed main() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    build(0, 0, n);

    while (q--) {
        int type;  // type = 1 - update, type = 2 - get
        cin >> type;  // 0-indexing
        if (type == 1) {
            int x, y;
            cin >> x >> y;
            upd(0, 0, n, x, y); // a[x] = y
        } else {
            int x, y;
            cin >> x >> y;
            cout << find_bigger(0, 0, n, y, n, x) << "\n";  // find min j >= l: a[j] >= val or -1 if not exists
        }
    }
    return 0;
}
