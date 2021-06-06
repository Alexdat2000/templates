#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define endl "\n"

using namespace std;

const int N = 2e5 + 100;
int source, sink;

vector <array <int, 4>> g[N];  // to, flow, cap, pair-id
int dist[N];


bool bfs(int lim) {
    fill(dist, dist + N, -1);
    dist[source] = 0;

    deque <int> q = {source};
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();

        for (auto [i, flow, cap, _] : g[v]) {
            if (dist[i] != -1 || flow + lim > cap)
                continue;
            dist[i] = dist[v] + 1;
            q.push_back(i);
        }
    }

    return dist[sink] != -1;
}

int pointer[N];
int dfs(int v, int now, int lim) {
    if (v == sink)
        return now;

    for (int& i = pointer[v]; i < (int) g[v].size(); i++) {
        auto& e = g[v][i];

        if (dist[e[0]] != dist[v] + 1 || e[1] + lim > e[2])
            continue;

        if (int pushed = dfs(e[0], min(now, e[2] - e[1]), lim)) {
            e[1] += pushed;
            g[e[0]][e[3]][1] -= pushed;
            return pushed;
        }
    }
    return 0;
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    source = 0, sink = n - 1;

    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        g[a].push_back({b, 0, c, (int) g[b].size()});
        g[b].push_back({a, 0, 0, (int) g[a].size() - 1});
    }

    long long ans = 0;
    for (int lim = 1 << 30; lim > 0; lim >>= 1) {
        while (bfs(lim)) {
            fill(pointer, pointer + N, 0);
            while (int delta = dfs(source, INT_MAX / 2, lim)) {
                ans += delta;
            }
        }
    }
    cout << ans << endl;
    return 0;
}