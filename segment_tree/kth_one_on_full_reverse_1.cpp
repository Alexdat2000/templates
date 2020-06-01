// https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/B
// segment tree on (a_i ∈{0,1}) with operations: get k-th 1 on full array and reverse one element (a[i] = 1 - a[i])
// author: Alexdat2000

#include <iostream>

#define int long long

using namespace std;

const int N = 1e5 + 100;
int a[N];
int tree_one[4 * N];  // how many 1 on segment


void build(int v, int l, int r) {
    if (r - l == 1) {
        tree_one[v] = (a[l] == 1);
        return;
    }

    int m = (l + r) / 2;
    build(v * 2 + 1, l, m);
    build(v * 2 + 2, m, r);
    tree_one[v] = tree_one[v * 2 + 1] + tree_one[v * 2 + 2];
}

int get_kth_one(int v, int l, int r, int k) {
    if (r - l == 1)
        return l;
    if (tree_one[v * 2 + 1] > k) {
        return get_kth_one(v * 2 + 1, l, (l + r) / 2, k);
    } else {
        return get_kth_one(v * 2 + 2, (l + r) / 2, r, k - tree_one[v * 2 + 1]);
    }
}

void reverse(int v, int l, int r, int pos) {  // reverse a[pos]
    if (r - l == 1) {
        a[l] = 1 - a[l];
        tree_one[v] = (a[l] == 1);
        return;
    }

    int m = (l + r) / 2;
    if (pos < m)
        reverse(v * 2 + 1, l, m, pos);
    else
        reverse(v * 2 + 2, m, r, pos);
    tree_one[v] = tree_one[v * 2 + 1] + tree_one[v * 2 + 2];
}

signed main() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    build(0, 0, n);

    while (q--) {
        int type, x;  // type = 1 - update, type = 2 - get_sum
        cin >> type >> x;  // 0-indexing
        if (type == 1) {
            reverse(0, 0, n, x); // a[x] = y
        } else {
            cout << get_kth_one(0, 0, n, x) << "\n";  // k-th 1 on full a
        }
    }
    return 0;
}
