// Informatics: 114218

#include <bits/stdc++.h>
using namespace std;

vector <int> h, a, ans;
int num, n, q, l, r, k = 350, m;
int w;

struct seg {
    int l, r, i;
    seg()= default;
    seg(int l, int r, int i): l(l), r(r), i(i) {};
};

bool operator< (seg& o, seg& p) {
    return make_pair(o.l / k, o.r) < make_pair(p.l / k, p.r);
}

void del(int i) {
    int x = a[i];
    if (h[x] == w)
        num--;
    h[x]--;
    if (h[x] == w)
        num++;
}

void add(int i) {
    int x = a[i];
    if (h[x] == w)
        num--;
    h[x]++;
    if (h[x] == w)
        num++;
}

int main() {
    cin >> n >> m >> q >> w;
    a.resize(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    h.assign(m + 1, 0);

    vector <seg> s;
    s.resize(q);
    for (int i = 0; i < q; i++) {
        cin >> s[i].l >> s[i].r;
        s[i].i = i;
    }

    sort(s.begin(), s.end());
    num = 0, l = 0, r = -1;
    if (w == 0)
        num = m;
    ans.resize(q);

    for (int i = 0; i < q; i++) {
        int L = s[i].l - 1, R = s[i].r - 1;
        while (L < l)
            add(--l);

        while (L > l)
            del(l++);

        while (R < r)
            del(r--);

        while (R > r)
            add(++r);
        ans[s[i].i] = num;
    }
    for (int i : ans)
        cout << i << endl;
    return 0;
}
