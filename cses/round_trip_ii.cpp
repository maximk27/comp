#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct FullEdge {
    int u, v;
};

// true if found cycle
bool Dfs(vector<int> &state, vector<int> &ordering,
         vector<vector<int>> &adjlist, int u) {

    if (state[u] == 2) {
        return false;
    }

    if (state[u] == 1) {
        ordering.push_back(u);
        return true;
    }

    // else state = 0, unvisited
    state[u] = 1;
    ordering.push_back(u);

    for (int v : adjlist[u]) {
        if (Dfs(state, ordering, adjlist, v)) {
            return true;
        }
    }

    state[u] = 2;
    ordering.pop_back();

    return false;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<FullEdge> edges(m);
    for (int i = 0; i < m; i++) {
        auto &e = edges[i];
        cin >> e.u >> e.v;
        e.u--;
        e.v--;
    }
    vector<vector<int>> adjlist(n);
    for (auto [u, v] : edges) {
        adjlist[u].push_back(v);
    }

    vector<int> ordering, state(n, 0);
    for (int i = 0; i < n; i++) {
        if (Dfs(state, ordering, adjlist, i)) {
            break;
        }
    }

    if (ordering.empty()) {
        cout << "IMPOSSIBLE\n";
        return;
    }

    int back = ordering.back();
    int i = 0;
    while (ordering[i] != back) {
        i++;
    }
    cout << ordering.size() - i << "\n";
    while (i < ordering.size()) {
        cout << ordering[i] + 1 << " ";
        i++;
    }
    cout << "\n";
}

int main() {
    solve();
}
