#include <bits/stdc++.h>
#include <cassert>
#include <expected>
using namespace std;

struct Edge {
    int u, v;
};

enum State {
    Unvisited = 0,
    Visited = 1,
    Processed = 2,
};

// return true if exists cycle
bool dfs(vector<vector<int>> &adjlist, vector<State> &states, int u,
         vector<int> &ordering) {

    if (states[u] == Visited) {
        return true;
    }
    if (states[u] == Processed) {
        return false;
    }
    // else unvisited
    states[u] = Visited;

    for (int v : adjlist[u]) {
        if (dfs(adjlist, states, v, ordering)) {
            return true;
        }
    }
    ordering.push_back(u);
    states[u] = Processed;
    return false;
}

expected<vector<int>, string> TopologicalSort(vector<vector<int>> &adjlist) {
    int n = adjlist.size();
    vector<State> states(n);
    vector<int> ordering;
    for (int node = 0; node < n; node++) {
        if (dfs(adjlist, states, node, ordering)) {
            return unexpected("IMPOSSIBLE");
        }
    }
    reverse(begin(ordering), end(ordering));
    return ordering;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        auto &e = edges[i];
        cin >> e.u >> e.v;
        e.u--;
        e.v--;
    }

    // topological sort
    vector<vector<int>> adjlist(n);
    for (auto [u, v] : edges) {
        adjlist[u].push_back(v);
    }
    auto order = TopologicalSort(adjlist);
    if (!order) {
        cout << order.error() << "\n";
        return;
    }

    for (int val : *order)
        cout << val + 1 << " ";
    cout << "\n";
}

int main() {
    solve();
}
