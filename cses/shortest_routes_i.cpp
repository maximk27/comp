#include <bits/stdc++.h>
#include <queue>
using namespace std;

const constexpr int64_t INF = int64_t(1e14);

// shortest routes i
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adjlist(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        adjlist[a].push_back({b, c});
    }
    priority_queue<pair<int64_t, int>, vector<pair<int64_t, int>>,
                   greater<pair<int64_t, int>>>
        pq;

    vector<int64_t> min_dist(n, INF);
    pq.push({0, 0});
    while (!pq.empty()) {
        auto [dist_u, u] = pq.top();
        pq.pop();
        if (min_dist[u] != INF) {
            // stale
            continue;
        }
        // this must be min to c
        min_dist[u] = dist_u;
        for (auto [v, c] : adjlist[u]) {
            int64_t dist_v = dist_u + c;
            if (dist_v < min_dist[v]) {
                pq.push({dist_v, v});
            }
        }
    }
    for (int64_t val : min_dist) {
        cout << val << " ";
    }
    cout << "\n";
}

int main() {
    solve();
}
