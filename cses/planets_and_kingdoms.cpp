#include <bits/stdc++.h>
using namespace std;

#define dbg(x) "(" << #x << "=" << x << ")"

/*
    number of strongly connected componetns
    dsu type, where kingsdoms merged
    - since if a-b and b-c, then a-c

    some type of dfs with time tracking (so know point where cycle began)
    - ex: a,b,c,d,b (here a would be excluded, merge b,c,d)

    formally, tarjan's algorithm
    dfs, maintain tin, low, processed
    tin[u] = low[u] = timer++
    for v in adjlist[u]
        if processed[v],
            continue
        if not tin (not visited ever), try inherit whatever descendant finds
            dfs
            inherit low
        else if not processed (visited in this stack)
            inherit its tin

    if low == tin, then start and end of scc (outermost)
        while not closed
            color with new component
*/

// { num_scc, scc_mapping }
pair<int, vector<int>> GetSCC(vector<vector<int>> &adjlist) {
    int n = adjlist.size();

    // name components [1...n], pre increment
    int components_size = 0;
    // time [1...n], pre increment
    int timer = 0;

    vector<int> components(n, 0);
    vector<int> tins(n, 0);
    vector<int> lows(n);
    stack<int> st;
    auto Dfs = [&](auto &&self, int v) -> void {
        tins[v] = lows[v] = ++timer;
        st.push(v);
        for (int w : adjlist[v]) {
            if (!tins[w]) {
                self(self, w);
                lows[v] = min(lows[v], lows[w]);
            } else if (!components[w]) {
                // w unprocessed and still on the stack
                lows[v] = min(lows[v], tins[w]);
            }
        }
        if (lows[v] == tins[v]) {
            // is [a,b,v,x,y,z] -> [a,b] where v,x,y,z scc
            int id = ++components_size;
            while (true) {
                int curr = st.top();
                st.pop();
                components[curr] = id;
                if (curr == v)
                    break;
            }
        }
    };

    for (int node = 0; node < n; node++) {
        if (!components[node]) {
            Dfs(Dfs, node);
        }
    }
    return {components_size, components};
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adjlist(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adjlist[u].push_back(v);
    }
    auto [scc_n, scc] = GetSCC(adjlist);
    cout << scc_n << '\n';
    for (int val : scc)
        cout << val << ' ';
    cout << '\n';
}

int main() {
    solve();
}
