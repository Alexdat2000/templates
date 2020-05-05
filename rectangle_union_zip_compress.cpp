#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

const int N = 2e5 + 100;
int mn[4 * N], mn_cnt[4 * N], p[4 * N];
vector <int> values;
map <int, int> indexes;

void push(int v, int l, int r) {
    if (!p[v])
        return;

    mn[v] += p[v];
    if (r - l > 1) {
        p[v * 2 + 1] += p[v];
        p[v * 2 + 2] += p[v];
    }
    p[v] = 0;
}

void upd(int v, int l, int r, int ql, int qr, int delta) {
    push(v, l, r);
    if (ql <= l && r <= qr) {
        p[v] += delta;
        push(v, l, r);
        return;
    }

    if (l >= qr || r <= ql)
        return;

    int m = (l + r) / 2;
    upd(v * 2 + 1, l, m, ql, qr, delta);
    upd(v * 2 + 2, m, r, ql, qr, delta);
    push(v, l, r);

    if (mn[v * 2 + 1] == mn[v * 2 + 2])
        mn[v] = mn[v * 2 + 1], mn_cnt[v] = mn_cnt[v * 2 + 1] + mn_cnt[v * 2 + 2];
    else if (mn[v * 2 + 1] < mn[v * 2 + 2])
        mn[v] = mn[v * 2 + 1], mn_cnt[v] = mn_cnt[v * 2 + 1];
    else
        mn[v] = mn[v * 2 + 2], mn_cnt[v] = mn_cnt[v * 2 + 2];
}

void build(int v, int l, int r) {
    if (r - l == 1) {
        mn[v] = 0, mn_cnt[v] = values[r] - values[l];
        return;
    }

    int m = (l + r) / 2;
    build(v * 2 + 1, l, m);
    build(v * 2 + 2, m, r);
    mn_cnt[v] = mn_cnt[v * 2 + 1] + mn_cnt[v * 2 + 2];
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    set <int> y_coords;
    vector<array<int, 4>> events;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2)
            swap(x1, x2);
        if (y1 > y2)
            swap(y1, y2);

        events.push_back({1, x1 - 1, 0, 0});  // precount
        events.push_back({0, x1, y1, y2 + 1});  // open
        events.push_back({1, x2, 0, 0});  // recount
        events.push_back({2, x2, y1, y2 + 1});  // close
        y_coords.insert(y1);
        y_coords.insert(y2 + 1);
    }
    sort(events.begin(), events.end(),
         [](const array<int, 4> &a, const array<int, 4> &b) { return make_pair(a[1], a[0]) < make_pair(b[1], b[0]); });

    for (int i : y_coords)
        values.push_back(i);
    for (int i = 0; i < (int) values.size(); i++) {
        indexes[values[i]] = i;
    }
    build(0, 0, (int) values.size() - 1);
    int len = values.back() - values.front();

    int last = -1e9 - 100;
    long long ans = 0;
    for (const auto &i : events) {
        if (i[0] == 1) {
            ans += (long long) (i[1] - last) * (len - mn_cnt[0] * (mn[0] == 0));
            last = i[1];
        } else if (i[0] == 0) {
            upd(0, 0, (int) values.size() - 1, indexes[i[2]], indexes[i[3]], 1);
        } else {
            upd(0, 0, (int) values.size() - 1, indexes[i[2]], indexes[i[3]], -1);
        }
    }
    cout << ans << endl;
    return 0;
}
