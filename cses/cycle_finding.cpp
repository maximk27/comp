#include <bits/stdc++.h>
using namespace std;

struct FullEdge {
    int u, v;
    int64_t c;
};

constexpr const int64_t INF = int64_t(1e14);

void solve() {
    int n, m;
    cin >> n >> m;
    vector<FullEdge> edges(m);
    for (int i = 0; i < m; i++) {
        auto &a = edges[i];
        cin >> a.u >> a.v >> a.c;
        a.u--;
        a.v--;
    }

    vector<int> min_from(n, -1);
    vector<int64_t> min_dist(n, 0);

    int cycle_start = -1;
    for (int i = 0; i < n; i++) {
        // try improve n times
        bool improve = false;
        for (auto [u, v, c] : edges) {
            int64_t cand = min_dist[u] + c;
            if (cand < min_dist[v]) {
                min_dist[v] = cand;
                min_from[v] = u;
                improve = true;

                if (i == n - 1) {
                    // exists neg cycle
                    cycle_start = v;
                    break;
                }
            }
        }

        if (!improve || cycle_start != -1) {
            break;
        }
    }

    if (cycle_start == -1) {
        cout << "NO\n";
        return;
    }

    // ensure we are inside the loop
    for (int i = 0; i < n; i++) {
        cycle_start = min_from[cycle_start];
    }

    vector<int> cycle;
    int node = cycle_start;
    do {
        cycle.push_back(node);
        node = min_from[node];
    } while (node != cycle_start);
    cycle.push_back(node);

    // 2 4 1 2
    // 1,-3, 1, = -1
    reverse(begin(cycle), end(cycle));
    cout << "YES\n";
    for (int val : cycle) {
        cout << val + 1 << " ";
    }
    cout << "\n";
}

int main() {
    solve();
}
