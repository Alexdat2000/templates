// CF: 940F

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

const int N = 1e5 + 100, K = 2160;

vector <array <int, 3>> upd;
vector <int> cnt;
int a[N];
int counts[N];

int find_mex() {
    int i = 0;
    while (counts[i])
        i++;
    return i;
}

void add(int ind) {
    int val = a[ind];

    counts[cnt[val]]--;
    cnt[val]++;
    counts[cnt[val]]++;
}

void del(int ind) {
    int val = a[ind];
    counts[cnt[val]]--;
    cnt[val]--;
    counts[cnt[val]]++;
}

void forward(int ind, int l, int r) {
    auto [index, from, to] = upd[ind - 1];
    upd[ind - 1][1] = from = a[index];

    a[index] = to;

    if (l <= index && index <= r) {
        counts[cnt[from]]--;
        cnt[from]--;
        counts[cnt[from]]++;

        counts[cnt[to]]--;
        cnt[to]++;
        counts[cnt[to]]++;
    }
}

void rewind(int ind, int l, int r) {
    auto [index, from, to] = upd[ind - 1];

    a[index] = from;

    if (l <= index && index <= r) {
        counts[cnt[to]]--;
        cnt[to]--;
        counts[cnt[to]]++;

        counts[cnt[from]]--;
        cnt[from]++;
        counts[cnt[from]]++;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector <int> nums;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        nums.push_back(a[i]);
    }

    vector <array <int, 3>> req(q);
    for (auto& i : req) {
        cin >> i[0] >> i[1] >> i[2];
        if (i[0] == 2)
            nums.push_back(i[2]);
    }
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    for (int i = 0; i < n; i++)
        a[i] = lower_bound(nums.begin(), nums.end(), a[i]) - nums.begin();

    vector <array <int, 4>> seg;
    int change_cnt = 0;
    counts[0] = (int) nums.size() + 1;

    for (int _ = 0; _ < q; _++) {
        auto i = req[_];

        if (i[0] == 1) {
            seg.push_back({change_cnt, i[1] - 1, i[2] - 1, _ - change_cnt});
        } else {
            i[2] = lower_bound(nums.begin(), nums.end(), i[2]) - nums.begin();
            upd.push_back({i[1] - 1, -1, i[2]});
            change_cnt++;
        }
    }

    sort(seg.begin(), seg.end(), [](const array <int, 4>& a, const array <int, 4>& b) {
        return array <int, 3> {a[0] / K, a[1] / K, a[2]} < array <int, 3> {b[0] / K, b[1] / K, b[2]};
    });

    int l = 0, r = -1, t = 0;
    cnt.resize(nums.size());
    vector <int> ans(q - change_cnt);

    for (auto [T, L, R, seg_number] : seg) {
        while (R > r)
            add(++r);

        while (L < l)
            add(--l);

        while (R < r)
            del(r--);

        while (L > l)
            del(l++);

        while (T < t)
            rewind(t--, l, r);
        while (T > t)
            forward(++t, l, r);

        ans[seg_number] = find_mex();
    }

    for (int i : ans)
        cout << i << "\n";
    return 0;
}
