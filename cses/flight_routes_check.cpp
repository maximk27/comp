#include <bits/stdc++.h>
using namespace std;

#define dbg(x) "(" << #x << "=" << x << ")"

// -1 if all reachable
// else violating vertice
int UnreachableEdge(vector<vector<int>> &adjlist, int src) {
    vector<bool> visited(adjlist.size(), false);
    auto Dfs = [&](auto &&self, int v) {
        if (visited[v])
            return;
        visited[v] = true;
        for (int w : adjlist[v]) {
            self(self, w);
        }
    };
    Dfs(Dfs, src);
    for (int i = 0; i < adjlist.size(); i++) {
        if (!visited[i]) {
            return i;
        }
    }
    return -1;
}

void solve() {
    // directed connectivity check
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adjlist(n);
    vector<vector<int>> r_adjlist(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adjlist[a].push_back(b);
        r_adjlist[b].push_back(a);
    }

    /*
    assuming all vertice can reach any other vertice then
    pick some src=0
    - src -> all others
    - all -> src
    otherwise exists pair (x, src) or (src, x) cannot talk

    these 2 properties -> all vertice can reach all others
    proves exists all -> src -> all
    */

    int src = 0;

    int out = UnreachableEdge(adjlist, src);
    if (out != -1) {
        cout << "NO\n";
        cout << src + 1 << ' ' << out + 1 << '\n';
        return;
    }

    int in = UnreachableEdge(r_adjlist, 0);
    if (in != -1) {
        cout << "NO\n";
        cout << in + 1 << ' ' << src + 1 << '\n';
        return;
    }
    cout << "YES\n";
}

int main() {
    solve();
}
