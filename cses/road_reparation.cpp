#include <bits/stdc++.h>
using namespace std;

#define dbg(x) "(" << #x << "=" << x << ")"

class DSU {
public:
    vector<int> rep;
    int count = 0;

    DSU(int n) {
        rep.resize(n);
        count = n;
        iota(begin(rep), end(rep), 0);
    }

    int find(int a) {
        if (rep[a] == a)
            return a;
        return rep[a] = find(rep[a]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b)
            return false;
        count--;
        rep[b] = a;
        return true;
    }
};

void solve() {
    // mst building
    int n, m;
    cin >> n >> m;

    // { cost, u, v }
    using FullEdge = tuple<int64_t, int, int>;
    vector<FullEdge> edges(m);
    for (auto &[cost, u, v] : edges) {
        cin >> u >> v >> cost;
        u--;
        v--;
    }

    DSU dsu(n);
    sort(edges.begin(), edges.end());
    int64_t total = 0;
    for (auto [cost, u, v] : edges) {
        if (dsu.unite(u, v)) {
            total += cost;
        }
    }
    // clang-format off
    string res = dsu.count == 1
        ? to_string(total)
        : "IMPOSSIBLE";
    // clang-format on
    cout << res << '\n';
}

int main() {
    solve();
}
