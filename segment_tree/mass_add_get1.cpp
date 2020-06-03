// https://codeforces.com/edu/course/2/lesson/5/1/practice/contest/279634/problem/A
// segment tree with operations: add val to segment and get value by index
// author: Alexdat2000


#include <iostream>

using namespace std;


const int N = 1e5 + 100;
int push[4 * N];


void mass_add(int v, int l, int r, int ql, int qr, int val) {
    if (ql <= l && r <= qr) {
        push[v] += val;
        return;
    }
    if (l >= qr || r <= ql)
        return;

    int m = (l + r) / 2;
    mass_add(v * 2 + 1, l, m, ql, qr, val);
    mass_add(v * 2 + 2, m, r, ql, qr, val);
}

int get_val(int v, int l, int r, int ind) {
    if (r - l == 1)
        return push[v];

    int m = (l + r) / 2;
    if (ind < m) {
        return push[v] + get_val(v * 2 + 1, l, m, ind);
    } else {
        return push[v] + get_val(v * 2 + 2, m, r, ind);
    }
}

signed main() {
    int n, q;
    cin >> n >> q;

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r, val;
            cin >> l >> r >> val;
            mass_add(0, 0, n, l, r, val);
        } else {
            int ind;
            cin >> ind;
            cout << get_val(0, 0, n, ind) << "\n";
        }
    }
    return 0;
}
