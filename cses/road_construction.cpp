#include <bits/stdc++.h>
#include <cassert>
using namespace std;

#define dbg(x) "(" << #x << "=" << x << ")"

class DSU {
public:
    vector<int> rep;
    multiset<int> sorted_sizes;
    unordered_map<int, int> component_sizes;

    DSU(int n) {
        rep.resize(n);
        iota(begin(rep), end(rep), 0);
        for (int i = 0; i < n; i++) {
            sorted_sizes.insert(1);
            component_sizes[i] = 1;
        }
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

        // update a
        sorted_sizes.erase(sorted_sizes.find(component_sizes[a]));
        component_sizes[a] += component_sizes[b];
        sorted_sizes.insert(component_sizes[a]);

        // update b
        sorted_sizes.erase(sorted_sizes.find(component_sizes[b]));
        component_sizes.erase(b);

        rep[b] = a;
        return true;
    }

    int max_size() {
        // clang-format off
        return !sorted_sizes.empty()
            ? *prev(sorted_sizes.end())
            : 0;
        // clang-format on
    }

    int component_count() {
        return sorted_sizes.size();
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    // { u, v }
    using Edge = pair<int, int>;
    vector<Edge> edges(m);
    for (auto &e : edges) {
        cin >> e.first >> e.second;
        e.first--;
        e.second--;
    }

    DSU dsu(n);
    // { num_components, max_component_size }
    using Ans = pair<int, int>;
    vector<Ans> ans(m);
    for (int i = 0; i < m; i++) {
        auto [u, v] = edges[i];
        dsu.unite(u, v);
        ans[i] = Ans{dsu.component_count(), dsu.max_size()};
    }

    for (auto [a, b] : ans) {
        cout << a << " " << b << '\n';
    }
}

int main() {
    solve();
}
