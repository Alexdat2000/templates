// https://codeforces.com/edu/course/2/lesson/4/3/practice/contest/274545/problem/B
// get array by number of inversions with every element
// author: Alexdat2000

#include <iostream>
#include <vector>

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
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        a[i] = 1;
    build(0, 0, n);

    vector <int> ind(n), ans;
    for (int& i : ind)
        cin >> i;

    for (int i = n - 1; i > -1; i--) {
        int x = get_kth_one(0, 0, n, n - ind[i] - (n - i - 1) - 1);
        ans.push_back(x);
        reverse(0, 0, n, x);
    }
    for (int i = n - 1; i > -1; i--)
        cout << ans[i] + 1 << " ";
    cout << endl;
    return 0;
}
