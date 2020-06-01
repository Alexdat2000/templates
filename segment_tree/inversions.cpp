// https://codeforces.com/edu/course/2/lesson/4/3/practice/contest/274545/problem/A
// number of inversions for every element of array, O(nlogn)
// author: Alexdat2000

#include <iostream>
#include <vector>

#define int long long

using namespace std;

const int N = 1e5 + 100;
int a[N], tree_sm[4 * N];

void build(int v, int l, int r) {
    if (r - l == 1) {
        tree_sm[v] = a[l];
        return;
    }

    int m = (l + r) / 2;
    build(v * 2 + 1, l, m);
    build(v * 2 + 2, m, r);
    tree_sm[v] = tree_sm[v * 2 + 1] + tree_sm[v * 2 + 2];
}

int get_sum(int v, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return tree_sm[v];
    if (l >= qr || r <= ql)
        return 0;

    int m = (l + r) / 2;
    return get_sum(v * 2 + 1, l, m, ql, qr) + get_sum(v * 2 + 2, m, r, ql, qr);
}

void inc(int v, int l, int r, int pos) {
    if (r - l == 1) {
        tree_sm[v]++;
        return;
    }

    int m = (l + r) / 2;
    if (pos < m)
        inc(v * 2 + 1, l, m, pos);
    else
        inc(v * 2 + 2, m, r, pos);
    tree_sm[v]++;
}

signed main() {
    int n;
    cin >> n;
    vector <int> line(n);
    for (int& i : line)
        cin >> i;

    for (auto i : line) {
        cout << get_sum(0, 0, n, i, n) << " ";
        inc(0, 0, n, i - 1);
    }
    cout << endl;
    return 0;
}
