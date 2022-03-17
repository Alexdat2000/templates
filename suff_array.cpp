#include <bits/stdc++.h>

#define len(x) (int) (x).size()
#define all(x) (x).begin(), (x).end()
#define endl "\n"

using namespace std;


vector <int> count_sort(const vector <int>& order, const vector <int>& cl) {
    int n = len(order);
    vector <int> cnt(n);
    for (int i : cl) {
        cnt[i]++;
    }

    vector <int> pref_sum(n);
    for (int i = 1; i < n; i++) {
        pref_sum[i] = pref_sum[i - 1] + cnt[i - 1];
    }

    vector <int> ans(n);
    for (int i : order) {
        ans[pref_sum[cl[i]]++] = i;
    }
    return ans;
}


int n;
int mod(int x) {
    if (x < 0) {
        x += n;
    }
    if (x >= n) {
        x -= n;
    }
    return x;
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    s += '$';
    n = len(s);

    vector <int> order(n), cl(n);
    iota(all(order), 0);
    sort(all(order), [&](const int a, const int b) {return s[a] < s[b];});

    for (int i = 1; i < n; i++) {
        if (s[order[i]] != s[order[i - 1]]) {
            cl[order[i]] = cl[order[i - 1]] + 1;
        } else {
            cl[order[i]] = cl[order[i - 1]];
        }
    }

    for (int ln = 1; ln < n; ln <<= 1) {
        for (int i = 0; i < n; i++) {
            order[i] = mod(order[i] - ln);
        }
        order = count_sort(order, cl);

        vector <int> new_cl(n);
        for (int i = 1; i < n; i++) {
            pair <int, int> pre = {cl[order[i - 1]], cl[mod(order[i - 1] + ln)]};
            pair <int, int> now = {cl[order[i]], cl[mod(order[i] + ln)]};
            if (pre == now) {
                new_cl[order[i]] = new_cl[order[i - 1]];
            } else {
                new_cl[order[i]] = new_cl[order[i - 1]] + 1;
            }
        }
        cl = new_cl;
    }

    for (int i : order) {
        cout << i << " ";
    }
    cout << endl;

    vector <int> lcp(n);
    int k = 0;
    for (int i = 0; i < n - 1; i++) {
        int pos = cl[i];
        while (s[i + k] == s[order[pos - 1] + k]) {
            k++;
        }
        lcp[pos] = k;
        k = max(0, k - 1);
    }
    for (int i = 1; i < n; i++) {
        cout << lcp[i] << " ";
    }
    cout << endl;
    return 0;
}
