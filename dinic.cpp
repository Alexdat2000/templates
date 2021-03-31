#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define endl "\n"

using namespace std;


const int N = 110;
struct edge {
    int to, flow, cap;
    edge(int a, int b, int c): to(a), flow(b), cap(c) {};
};

vector <edge> edges;
vector <int> g[N];
vector <int> dist;

void add_undirected_edge(int a, int b, int c) {
    g[a].push_back(edges.size());
    edges.emplace_back(b, 0, c);
    g[b].push_back(edges.size());
    edges.emplace_back(a, 0, c);
}

void add_directed_edge(int a, int b, int c) {
    g[a].push_back(edges.size());
    edges.emplace_back(b, 0, c);
    g[b].push_back(edges.size());
    edges.emplace_back(a, 0, 0);
}

int source = 0, sink = 0, n;
int pointer[N];

bool bfs() {
    dist.assign(n, INT_MAX);
    dist[source] = 0;

    deque <int> q = {source};
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        for (int i : g[v]) {
            if (dist[edges[i].to] == INT_MAX && edges[i].flow < edges[i].cap) {
                dist[edges[i].to] = dist[v] + 1;
                q.push_back(edges[i].to);
            }
        }
    }
    return dist[sink] != INT_MAX;
}

int dfs(int v, int now) {
    if (!now)
        return 0;
    if (v == sink)
        return now;

    for (int i = pointer[v]; i < (int) g[v].size(); i++, pointer[v]++) {
        auto &e = edges[g[v][i]];
        if (dist[e.to] != dist[v] + 1)
            continue;

        int pushed = dfs(e.to, min(now, e.cap - e.flow));
        if (pushed) {
            edges[g[v][i]].flow += pushed;
            edges[g[v][i] ^ 1].flow -= pushed;
            return pushed;
        }
    }
    return 0;
}

signed main() {
    int flow = 0;
    while (bfs()) {
        fill(pointer, pointer + N, 0);
        while (int delta = dfs(source, INT_MAX)) {
            flow += delta;
        }
    }
    return 0;
}
