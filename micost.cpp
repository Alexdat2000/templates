#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define endl "\n"
#define int long long

using namespace std;

const int N = 22, H = 10, INF = 1e9;
int source = N - 2, sink = N - 1;

struct edge {
    int pr{}, to{}, left{}, cost{};

    edge(int to, int cap, int cost, int pr) : pr(pr), to(to), left(cap), cost(cost) {};

    edge() = default;
};

vector<edge> g[N];

void add_edge(int a, int b, int cap, int cost) {
    g[a].emplace_back(b, cap, cost, g[b].size());
    g[b].emplace_back(a, 0, -cost, g[a].size() - 1);
}


pair<vector<int>, vector<pair<int, int>>> ford() {  // dist, from
    vector<int> dist(N, INT_MAX / 2);
    vector<pair<int, int>> from(N, {-1, -1});
    dist[source] = 0;

    deque<int> q = {source};
    vector<int> in_q(N, 0);
    in_q[source] = 1;

    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        in_q[v] = 0;

        for (int i = 0; i < (int) g[v].size(); i++) {
            auto x = g[v][i];
            int to = x.to;
            if (x.left == 0 || dist[to] <= dist[v] + x.cost) {
                continue;
            }
            dist[to] = dist[v] + x.cost;
            from[to] = {v, i};
            if (!in_q[to]) {
                q.push_back(to);
                in_q[to] = 1;
            }
        }
    }
    return {dist, from};
}


vector<int> delta;

pair<vector<int>, vector<pair<int, int>>> dijkstra() {
    vector<int> dist(N, INT_MAX / 2);
    vector<int> used(N, 0);
    vector<pair<int, int>> from(N, {-1, -1});
    dist[source] = 0;

    while (true) {
        int v = -1;
        for (int i = 0; i < N; i++) {
            if (!used[i] && dist[i] != INT_MAX / 2 && (v == -1 || dist[i] < dist[v])) {
                v = i;
            }
        }
        if (v == -1)
            break;
        used[v] = true;

        for (int i = 0; i < (int) g[v].size(); i++) {
            auto x = g[v][i];
            int to = x.to;
            if (x.left == 0 || dist[to] <= dist[v] + x.cost + delta[v] - delta[to]) {
                continue;
            }

            from[to] = {v, i};
            dist[to] = dist[v] + x.cost + delta[v] - delta[to];
        }
    }
    return {dist, from};
}

pair<int, int> mincost() {  // cost, flow
    int ans = 0, fl = 0;
    vector<pair<int, int>> from;
    {
        auto[t1, t2] = ford();
        delta = t1;
        from = t2;
    }

    while (true) {
        if (from[sink] == pair<int, int>{-1, -1})
            break;

        vector<pair<int, int>> path;
        int v = sink, flow = INT_MAX;
        while (v != source) {
            path.push_back(from[v]);
            flow = min(flow, g[from[v].first][from[v].second].left);
            v = from[v].first;
        }
        for (auto[a, b] : path) {
            auto &x = g[a][b];
            x.left -= flow;
            g[x.to][x.pr].left += flow;
            ans += flow * x.cost;
        }
        fl += flow;

        {
            auto[t1, t2] = dijkstra();
            for (int i = 0; i < N; i++)
                delta[i] += t1[i];
            from = t2;
        }
    }
    return {ans, fl};
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector <int> cnt(n);
    for (int& i : cnt)
        cin >> i;
    int sm = accumulate(all(cnt), 0);
    if (sm % 2 != 0) {
        cout << -1 << endl;
        return 0;
    }

    vector<vector<int>> mat(n, vector<int>(n));
    for (auto &i : mat) {
        for (auto &j : i) {
            cin >> j;
        }
    }

    int ans = INF;
    for (int mask = 0; mask < (1 << n); mask++) {
        for (auto & i : g)
            i.clear();

        for (int i = 0; i < n; i++) {
            if ((mask >> i) & 1) {
                add_edge(source, i, cnt[i] / 2, 0);
                add_edge(i + H, sink, (cnt[i] + 1) / 2, 0);
            } else {
                add_edge(source, i, (cnt[i] + 1) / 2, 0);
                add_edge(i + H, sink, cnt[i] / 2, 0);
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                add_edge(i, j + H, INF, mat[i][j]);
        }
        auto [cost, flow] = mincost();
        if (flow == sm / 2)
            ans = min(ans, cost);
    }
    cout << ans << endl;
    return 0;
}