#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = int64_t(1e9 + 7);

struct FullEdge {
    int u, v;
};

struct Node {
    bool computed = false;
    bool connected;
    int64_t ways;
};

Node ComputeRoutes(vector<Node> &nodes, vector<vector<int>> &adjlist, int u) {
    if (u == 0) {
        // base
        return Node{
            .computed = true,
            .connected = true,
            .ways = 1,
        };
    }

    if (nodes[u].computed) {
        // memo
        return nodes[u];
    }

    // recursive
    // sneaky mod edge case on ways=0 meaning unconnected
    bool connected = false;
    int64_t ways = 0;
    for (int v : adjlist[u]) {
        auto res = ComputeRoutes(nodes, adjlist, v);
        if (res.connected) {
            ways = (ways + res.ways) % MOD;
            connected = true;
        }
    }

    return nodes[u] = Node{
               .computed = true,
               .connected = connected,
               .ways = ways,
           };
}

void solve() {
    // no cycles, count ways
    // rev graph, find ways into n that connect from level 1

    int n, m;
    cin >> n >> m;
    vector<FullEdge> edges(m);
    for (int i = 0; i < m; i++) {
        auto &e = edges[i];
        cin >> e.u >> e.v;
        e.u--;
        e.v--;
    }

    vector<vector<int>> r_adjlist(n);
    for (auto [u, v] : edges) {
        r_adjlist[v].push_back(u);
    }
    vector<Node> nodes(n);
    ComputeRoutes(nodes, r_adjlist, n - 1);
    int64_t res = nodes[n - 1].ways;
    cout << res << "\n";
}

int main() {
    solve();
}
