#include <bits/stdc++.h>

#define int long long

#define all(x) (x).begin(), (x).end()
#define endl "\n"

using namespace std;

const int N = 100;
int source = 0, sink;

vector<array<int, 6>> g[N];  // flow, cap, cost, to, id, seg_id

void add_edge(int a, int b, int cap, int cost, int id) {
    g[a].push_back({0, cap, cost, b, (int) g[b].size(), id});
    g[b].push_back({0, 0, -cost, a, (int) g[a].size() - 1, -1});
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    sink = n - 1;

    for (int i = 0; i < k; i++) {
        int a, b, cap, cost;
        cin >> a >> b >> cap >> cost;
        add_edge(a - 1, b - 1, cap, cost, i);
    }

    int ans = 0;
    while (true) {
        vector <int> dist(N, LLONG_MAX), from(N, -1), from_edge(N, -1);
        dist[source] = 0;

        deque <int> q = {source};
        while (!q.empty()) {
            int v = q.front();
            q.pop_front();

            for (auto& [flow, cap, cost, to, id, _] : g[v]) {
                if (flow == cap || dist[to] <= dist[v] + cost)
                    continue;
                dist[to] = dist[v] + cost;
                from[to] = v;
                from_edge[to] = g[to][id][4];
                q.push_back(to);
            }
        }

        if (dist[sink] == LLONG_MAX) {
            break;
        }

        int v = sink;
        int flow = LLONG_MAX;
        while (from[v] != -1) {
            int u = from[v], id = from_edge[v];
            flow = min(flow, g[u][id][1] - g[u][id][0]);
            v = u;
        }
        ans += dist[sink] * flow;

        v = sink;
        while (from[v] != -1) {
            int u = from[v], id = from_edge[v];
            g[u][id][0] += flow;
            g[v][g[u][id][4]][0] -= flow;
            v = u;
        }
    }
    cout << ans << endl;
    return 0;
}
