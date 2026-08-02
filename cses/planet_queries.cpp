#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
#define dbg(x) std::cerr << "[DBG] " << #x << " = " << (x) << "\n"
#else
#define dbg(x) 42
#endif

// ========================================================================
// BINARY LIFTING
// ========================================================================
vector<vector<int>> Get(vector<int> &ps, int l) {
    int64_t n = ps.size();
    vector<vector<int>> parents(n, vector<int>(l, 0));
    for (int node = 0; node < n; node++) {
        parents[node][0] = ps[node];
    }

    for (int d = 1; d < l; d++) {
        for (int i = 0; i < n; i++) {
            parents[i][d] = parents[parents[i][d - 1]][d - 1];
        }
    }

    return parents;
}

int jump(vector<vector<int>> &parents, int x, int k, int l) {
    for (int i = 0; i < l; i++) {
        if (k & (1 << i)) {
            x = parents[x][i];
        }
    }
    return x;
}

struct Query {
    int x, k;
};

void solve() {
    // tree (exactly one parent)
    // find kth ancestor from node x

    int n, q;
    cin >> n >> q;
    vector<int> parents(n);
    for (int &val : parents) {
        cin >> val;
        val--;
    }

    int max_k = 0;
    vector<Query> queries(q);
    for (auto &it : queries) {
        cin >> it.x >> it.k;
        it.x--;
        max_k = max(max_k, it.k);
    }

    int l = int(log2(max_k) + 1);
    auto res = Get(parents, l);
    for (auto [x, k] : queries) {
        int node = jump(res, x, k, l);
        cout << node + 1 << "\n";
    }
}

int main() {
    solve();
}
