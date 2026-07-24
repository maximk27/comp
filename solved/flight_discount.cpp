#include <bits/stdc++.h>
#include <cassert>
#include <queue>
using namespace std;

constexpr const int64_t INF = int64_t(1e14);

struct Edge {
    int next;
    int64_t dist;
    bool operator<(Edge e) const {
        return dist > e.dist;
    }
};

struct FullEdge {
    int from;
    int to;
    int64_t dist;
};

vector<int64_t> SourceShortestPath(vector<vector<Edge>> &adjlist, int source) {
    int64_t n = adjlist.size();
    priority_queue<Edge> pq;
    pq.push(Edge{source, 0});
    vector<int64_t> min_dist(n, INF);
    while (!pq.empty()) {
        auto [u, u_dist] = pq.top();
        pq.pop();
        if (min_dist[u] != INF) {
            continue;
        }
        min_dist[u] = u_dist;
        for (auto [v, dist] : adjlist[u]) {
            int64_t v_dist = u_dist + dist;
            if (min_dist[v] != INF)
                continue;
            pq.push(Edge{v, v_dist});
        }
    }
    return min_dist;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<FullEdge> edges(m);
    for (int i = 0; i < m; i++) {
        int a, b;
        int64_t c;
        cin >> a >> b >> c;
        a--;
        b--;
        edges[i] = FullEdge{a, b, c};
    }

    vector<vector<Edge>> adjlist(n);
    vector<vector<Edge>> rev_adjlist(n);
    for (auto [a, b, c] : edges) {
        adjlist[a].push_back(Edge{b, c});
        rev_adjlist[b].push_back(Edge{a, c});
    }

    vector<int64_t> min_dist = SourceShortestPath(adjlist, 0);
    vector<int64_t> rev_min_dist = SourceShortestPath(rev_adjlist, n - 1);

    // include exclude on edge
    // forward min dist
    // reverse min dist
    // try edge (u, v, c)
    // min_dist[u] + c/2 + rev_min_dist[v]
    int64_t best_dist = INF;
    for (auto [u, v, dist] : edges) {
        int64_t cand = min_dist[u] + dist / 2 + rev_min_dist[v];
        best_dist = min(best_dist, cand);
    }
    cout << best_dist << "\n";
}

int main() {
    solve();
}
