#include <bits/stdc++.h>
using namespace std;

const constexpr int64_t INF = int64_t(1e12);

struct Query {
    int u, v;
};

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    // adjmatrix
    vector<vector<int64_t>> adjmatrix(n, vector<int64_t>(n, INF));
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        adjmatrix[a][b] = adjmatrix[b][a] = min(int64_t(c), adjmatrix[a][b]);
    }
    vector<Query> queries(q);
    for (Query &it : queries) {
        cin >> it.u >> it.v;
        it.u--;
        it.v--;
    }

    // dist=1, dist=2, dist=3...
    // n^2 over max dist which is n
    // overall n^3
    vector<vector<int64_t>> min_dist = std::move(adjmatrix);
    for (int i = 0; i < n; i++) {
        min_dist[i][i] = 0;
    }

    for (int mid = 0; mid < n; mid++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                int64_t prev = min_dist[u][v];
                int64_t cand = min_dist[u][mid] + min_dist[mid][v];
                int64_t res = min(prev, cand);
                min_dist[u][v] = min_dist[v][u] = res;
            }
        }
    }

    for (auto [u, v] : queries) {
        int64_t res = min_dist[u][v] != INF ? min_dist[u][v] : -1;
        cout << res << "\n";
    }
}

int main() {
    solve();
}
