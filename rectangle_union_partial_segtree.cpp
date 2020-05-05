#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;


struct node {
    int mn, mn_cnt, p, l_ch;

    node(int len) {
        mn = 0, mn_cnt = len, p = 0, l_ch = -1;
    }
    node()= default;
};

node tree[(int) 12e6];
int fre = 1;

void push(node &x, int l, int r) {
    if (x.l_ch == -1) {
        int m = (l + r) / 2;
        tree[fre] = node(m - l);
        tree[fre + 1] = node(r - m);
        x.l_ch = fre;
        fre += 2;
    }

    if (x.p == 0)
        return;

    x.mn += x.p;
    if (r - l > 1) {
        tree[x.l_ch].p += x.p;
        tree[x.l_ch + 1].p += x.p;
    }
    x.p = 0;
}

void upd(node& x, int l, int r, int ql, int qr, int delta) {
    push(x, l, r);
    if (ql <= l && r <= qr) {
        x.p += delta;
        push(x, l, r);
        return;
    }

    if (l >= qr || r <= ql)
        return;

    int m = (l + r) / 2;
    upd(tree[x.l_ch], l, m, ql, qr, delta);
    upd(tree[x.l_ch + 1], m, r, ql, qr, delta);
    push(x, l, r);

    node lc = tree[x.l_ch], rc = tree[x.l_ch + 1];
    if (lc.mn == rc.mn)
        x.mn = lc.mn, x.mn_cnt = lc.mn_cnt + rc.mn_cnt;
    else if (lc.mn < rc.mn)
        x.mn = lc.mn, x.mn_cnt = lc.mn_cnt;
    else
        x.mn = rc.mn, x.mn_cnt = rc.mn_cnt;
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int L = -1e9 - 100, R = 1e9 + 100;

    int n;
    cin >> n;
    tree[0] = node(R - L);

    vector<array<int, 4>> events;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        events.push_back({1, min(x1, x2) - 1, 0, 0});
        events.push_back({0, min(x1, x2), min(y1, y2), max(y1, y2)});
        events.push_back({1, max(x1, x2), 0, 0});
        events.push_back({2, max(x1, x2), min(y1, y2), max(y1, y2)});
    }
    sort(events.begin(), events.end(),
         [](const array<int, 4> &a, const array<int, 4> &b) { return make_pair(a[1], a[0]) < make_pair(b[1], b[0]); });

    int last = L;
    long long ans = 0;
    for (const auto &i : events) {
        if (i[0] == 1) {
            ans += (long long) (i[1] - last) * (R - L - tree[0].mn_cnt * (tree[0].mn == 0));
            last = i[1];
        } else if (i[0] == 0) {
            upd(tree[0], L, R, i[2], i[3] + 1, 1);
        } else {
            upd(tree[0], L, R, i[2], i[3] + 1, -1);
        }
    }
    cout << ans << endl;
    return 0;
}
