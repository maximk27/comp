#include <bits/stdc++.h>
#include <cassert>
#include <cstdint>
using namespace std;

struct Edge {
    int u, v;
};

struct Node {
    bool computed = false; // finalized
    bool connected;
    // invalid if not connected
    int height;
    int from;
};

Node Compute(vector<vector<int>> &adjlist, vector<Node> &nodes, int u) {
    if (u == 0) {
        // is leaf node
        return Node{
            .computed = true,
            .connected = true,
            .height = 1,
            .from = -1,
        };
    }

    if (nodes[u].computed) {
        // is computed
        return nodes[u];
    }

    int prev_height = -1;
    int from = -1;
    for (int v : adjlist[u]) {
        auto res = Compute(adjlist, nodes, v);
        // connected and longer path
        if (res.connected && res.height > prev_height) {
            prev_height = res.height;
            from = v;
        }
    }

    return nodes[u] = Node{
               .computed = true,
               .connected = from != -1,
               .height = prev_height + 1,
               .from = from,
           };
}

void solve() {
    // no directed cycles
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
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

    // given dag, calculate max height to node=0 from root=n-1
    // track the path
    vector<Node> nodes(n);
    Compute(r_adjlist, nodes, n - 1);
    if (!nodes[n - 1].connected) {
        cout << "IMPOSSIBLE\n";
        return;
    }

    vector<int> res;
    int u = n - 1;
    while (u != 0) {
        res.push_back(u);
        u = nodes[u].from;
    }
    res.push_back(0);

    reverse(begin(res), end(res));
    cout << res.size() << "\n";
    for (int val : res)
        cout << val + 1 << " ";
    cout << "\n";
}

int main() {
    solve();
}
