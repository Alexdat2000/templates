// https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/A
// segment tree with operations: get max sum of subsequence and change 1 element
// author: Alexdat2000

#include <iostream>
#include <algorithm>

#define int long long

using namespace std;

struct node {
    int pref_max, suf_max, ans, sm;

    explicit node(int v) {
        if (v >= 0)
            pref_max = suf_max = ans = sm = v;
        else
            pref_max = suf_max = ans = 0, sm = v;
    }
    node() = default;
};

const int N = 1e5 + 100;
int a[N];
node tree[4 * N];

node merge(node l, node r) { // merge 2 segments and returns answer
    node ans{};
    ans.ans = max({l.ans, r.ans, l.suf_max + r.pref_max});
    ans.pref_max = max(l.pref_max, l.sm + r.pref_max);
    ans.suf_max = max(r.suf_max, r.sm + l.suf_max);
    ans.sm = l.sm + r.sm;
    return ans;
}


void build(int v, int l, int r) {
    if (r - l == 1) {
        tree[v] = node(a[l]);
        return;
    }

    int m = (l + r) / 2;
    build(v * 2 + 1, l, m);
    build(v * 2 + 2, m, r);
    tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
}


node get_max_sum(int v, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return tree[v];
    if (l >= qr || r <= ql)
        return node(0);

    int m = (l + r) / 2;
    return merge(get_max_sum(v * 2 + 1, l, m, ql, qr), get_max_sum(v * 2 + 2, m, r, ql, qr));
}

void upd(int v, int l, int r, int pos, int val) {
    if (r - l == 1) {
        a[l] = val;
        tree[v] = node(a[l]);
        return;
    }

    int m = (l + r) / 2;
    if (pos < m)
        upd(v * 2 + 1, l, m, pos, val);
    else
        upd(v * 2 + 2, m, r, pos, val);
    tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
}

signed main() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    build(0, 0, n);

    cout << get_max_sum(0, 0, n, 0, n).ans << "\n"; // answer on full $a$

    while (q--) {  // q changes of elements
        int pos, val;
        cin >> pos >> val;
        upd(0, 0, n, pos, val);
        cout << get_max_sum(0, 0, n, 0, n).ans << "\n";
    }
    return 0;
}
