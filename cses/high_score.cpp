#include <bits/stdc++.h>
#include <cassert>
using namespace std;

constexpr const int64_t INF = int64_t(1e13);

struct Edge {
    int a, b;
    int64_t x;
};

void dfs(vector<bool> &reached, vector<vector<int>> &adjlist, int u) {
    reached[u] = true;
    for (int v : adjlist[u]) {
        if (!reached[v]) {
            dfs(reached, adjlist, v);
        }
    }
}

// Bellman Ford
void solve() {
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        int a, b;
        int64_t x;
        cin >> a >> b >> x;
        a--;
        b--;
        edges[i] = Edge{a, b, x};
    }

    // generate graphs
    vector<vector<int>> adjlist(n);
    vector<vector<int>> rev_adjlist(n);
    for (auto [a, b, x] : edges) {
        adjlist[a].push_back(b);
        rev_adjlist[b].push_back(a);
    }
    vector<bool> reachable(n, false);
    dfs(reachable, adjlist, 0);

    vector<bool> rev_reachable(n, false);
    dfs(rev_reachable, rev_adjlist, n - 1);

    bool pos_cycle = false;
    vector<int64_t> max_dist(n, -INF);
    max_dist[0] = 0;
    for (int i = 0; i < n; i++) {
        // try improve n times
        bool improve = false;
        for (auto [a, b, x] : edges) {
            int64_t cand = max_dist[a] + x;
            int64_t prev = max_dist[b];
            if (prev < cand) {
                max_dist[b] = cand;
                improve = true;

                // improved n times and connected to 1 and n
                if (i == n - 1 && reachable[b] && rev_reachable[b]) {
                    pos_cycle = true;
                    break;
                }
            }
        }
        if (!improve) {
            break;
        }
    }
    cout << (pos_cycle ? -1 : max_dist[n - 1]) << '\n';
}

int main() {
    solve();
}
