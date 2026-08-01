#include <bits/stdc++.h>
#include <cassert>
using namespace std;

#ifndef ONLINE_JUDGE
#define dbg(x) std::cerr << "[DBG] " << #x << " = " << (x) << "\n"
#else
#define dbg(x) 42
#endif

struct FullEdge {
    int u, v;
    int64_t c;
};

struct Edge {
    int v;
    int64_t c;
};

// ========================================================================
// MIN GRAPH
// ========================================================================
namespace min_graph {
struct ItemPQ {
    int u, v;
    int64_t c;
    bool operator>(ItemPQ o) const {
        return c > o.c;
    }
};

struct Node {
    bool computed = false;
    int64_t min_dist = 0;
    vector<int> min_from;
};

struct Result {
    int64_t min_dist;
    vector<vector<int>> r_min_adjlist;
};

// get min graph
Result Get(vector<vector<Edge>> adjlist) {
    int64_t n = adjlist.size();
    vector<Node> nodes(n);
    priority_queue<ItemPQ, vector<ItemPQ>, greater<ItemPQ>> pq;
    // u=-1 dummy
    pq.push({-1, 0, 0});
    while (!pq.empty()) {
        auto [u, v, v_dist] = pq.top();
        pq.pop();

        if (nodes[v].computed) {
            if (nodes[v].min_dist == v_dist) {
                nodes[v].min_from.push_back(u);
            }
            continue;
        }

        if (u != -1) {
            // not first dummy
            nodes[v].min_from.push_back(u);
        }
        nodes[v].min_dist = v_dist;
        nodes[v].computed = true;

        for (auto [w, c] : adjlist[v]) {
            if (!nodes[w].computed) {
                pq.push(ItemPQ{
                    .u = v,
                    .v = w,
                    .c = v_dist + c,
                });
            }
        }
    }

    int64_t min_dist = nodes[n - 1].min_dist;

    vector<vector<int>> r_min_adjlist(n);
    for (int u = 0; u < n; u++) {
        const auto &it = nodes[u];
        r_min_adjlist[u] = it.min_from;
    }

    return Result{
        .min_dist = min_dist,
        .r_min_adjlist = r_min_adjlist,
    };
}

}; // namespace min_graph

// ========================================================================
// ANALYZE
// ========================================================================
namespace analyze {
constexpr const int64_t MOD = int64_t(1e9 + 7);

struct Node {
    bool computed = false;
    bool connected;
    // valid only if connected
    int min_len;
    int max_len;
    int64_t ways;
};

Node Compute(vector<vector<int>> &adjlist, vector<Node> &nodes, int u) {
    if (u == 0) {
        // base
        return nodes[u] = Node{
                   .computed = true,
                   .connected = true,
                   .min_len = 1,
                   .max_len = 1,
                   .ways = 1,
               };
    }

    if (nodes[u].computed) {
        // memo
        return nodes[u];
    }

    // rec
    bool connected = false;
    int min_len = INT_MAX;
    int max_len = 0;
    int64_t ways = 0;
    for (int v : adjlist[u]) {
        auto res = Compute(adjlist, nodes, v);
        if (res.connected) {
            min_len = min(min_len, res.min_len);
            max_len = max(max_len, res.max_len);
            ways = (ways + res.ways) % MOD;
            connected = true;
        }
    }

    return nodes[u] = Node{
               .computed = true,
               .connected = connected,
               .min_len = 1 + min_len,
               .max_len = 1 + max_len,
               .ways = ways,
           };
}

struct Result {
    int64_t ways;
    int min_len;
    int max_len;
};

Result Get(vector<vector<int>> &adjlist) {
    int64_t n = adjlist.size();
    vector<Node> nodes(n);
    auto res = Compute(adjlist, nodes, int(n - 1));
    // NOTE: You may assume that there is a route from Syrjälä to Lehmälä.
    assert(res.connected);
    return Result{
        res.ways,
        res.min_len,
        res.max_len,
    };
}

}; // namespace analyze

// ========================================================================
// SOLVE
// ========================================================================
struct Solution {
    int64_t min_dist;
    int64_t ways;
    int64_t min_len;
    int64_t max_len;
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<FullEdge> edges(m);
    for (auto &e : edges) {
        cin >> e.u >> e.v >> e.c;
        e.u--;
        e.v--;
    }

    // find min first djikstra
    // track min edges

    // create reverse min graph
    // given min graph, run dfs, track min, max, count
    vector<vector<Edge>> adjlist(n);
    for (auto [u, v, c] : edges) {
        adjlist[u].push_back(Edge{v, c});
    }

    Solution sol;
    auto [min_dist, r_min_adjlist] = min_graph::Get(adjlist);
    sol.min_dist = min_dist;

    auto [ways, min_len, max_len] = analyze::Get(r_min_adjlist);
    sol.ways = ways;
    sol.min_len = min_len - 1;
    sol.max_len = max_len - 1;

    cout << sol.min_dist << " " << sol.ways << " " << sol.min_len << " "
         << sol.max_len << "\n";
}

int main() {
    solve();
}
