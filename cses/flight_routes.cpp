#include <bits/stdc++.h>
using namespace std;

struct FullEdge {
    int u, v;
    int64_t c;
};

struct Edge {
    int v;
    int64_t c;

    bool operator<(Edge e) const {
        return c > e.c;
    }
};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<FullEdge> edges(m);
    for (int i = 0; i < m; i++) {
        auto &a = edges[i];
        cin >> a.u >> a.v >> a.c;
        a.u--;
        a.v--;
    }

    vector<vector<Edge>> adjlist(n);
    for (auto [u, v, c] : edges) {
        adjlist[u].push_back(Edge{v, c});
    }

    // k is small
    // djikstra kD is possible
    // ensure min_dists[i].size() <= k
    vector<multiset<int64_t>> min_dists(n);

    priority_queue<Edge> pq;
    pq.push({0, 0});
    while (!pq.empty()) {
        auto [u, u_dist] = pq.top();
        pq.pop();
        auto &u_dists = min_dists[u];
        if (u_dists.size() == size_t(k)) {
            // already filled
            continue;
        }
        u_dists.insert(u_dist);
        for (auto [v, c] : adjlist[u]) {
            int64_t v_dist = u_dist + c;
            auto &v_dists = min_dists[v];
            if (v_dists.size() < size_t(k)) {
                pq.push(Edge{v, v_dist});
            }
        }
    }

    auto n_dists = min_dists[n - 1];
    for (int64_t val : n_dists) {
        cout << val << " ";
    }
    cout << "\n";
}

int main() {
    solve();
}
