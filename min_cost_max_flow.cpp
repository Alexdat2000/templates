#include <iostream>
#include <vector>
#include <memory.h>
#include <array>
#include <climits>

#define int long long

using namespace std;


namespace flow {
    const int MAXN = 1010;
    const int INF = 1e12 + 100;

    struct edge {
        int a, b, cap, flow, cost;
    };

    int n, s = 0, t = 1;
    vector<edge> e;
    vector<int> g[MAXN];
    vector <int> dist, prev, flo;

    void add_edge(int a, int b, int cap, int cost) {
        edge e1 = {a, b, cap, 0, cost};
        edge e2 = {b, a, 0, 0, -cost};
        g[a].push_back((int) e.size());
        e.push_back(e1);
        g[b].push_back((int) e.size());
        e.push_back(e2);
    }

    int ford() {
        dist.assign(n, INF);
        prev.assign(n, -1);
        flo.assign(n, 0);

        dist[s] = 0;
        flo[s] = INF;

        bool ch = true;
        while (ch) {
            ch = false;
            for (int q = 0; q < (int) e.size(); q++) {
                auto i = e[q];
                int from = i.a, to = i.b, cost = i.cost, flow = i.cap - i.flow;
                if (flow > 0 && dist[from] != INF && dist[to] > dist[from] + cost) {
                    ch = true;
                    dist[to] = dist[from] + cost;
                    prev[to] = q;
                    flo[to] = min(flo[from], flow);
                }
            }
        }
        return flo[t];
    }

    int mincost() {
        int flow = 0, cost = 0;
        while (int pushed = ford()) {
            flow += pushed;
            cost += dist[t] * pushed;
            int p = prev[t];
            while (p != -1) {
                e[p].flow += pushed;
                e[p ^ 1].flow -= pushed;
                p = prev[e[p].a];
            }
        }
        return cost;
    }
}


signed main() {
    int m;
    cin >> flow::n >> m;

    for (int i = 0; i < m; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        flow::add_edge(a - 1, b - 1, c, d);
    }

//    for (auto i : flow::e) {
//        cout << i.a << " " << i.b << " " << i.cost << endl;
//    }
    cin >> flow::s >> flow::t;
    flow::s--, flow::t--;

    cout << flow::mincost() << endl;
    return 0;
}
