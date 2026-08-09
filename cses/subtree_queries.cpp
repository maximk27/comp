#include <bits/stdc++.h>
#include <cassert>
using namespace std;

#ifndef ONLINE_JUDGE
#define dbg(x) std::cerr << "[DBG] " << #x << " = " << (x) << "\n"
#else
#define dbg(x) 42
#endif

class BIT {
    vector<int64_t> tree;

private:
    int GetLSB(int val) {
        return val & (-val);
    }

public:
    BIT(int n) : tree(n + 1, 0) {
    }

    // [0, k]
    int64_t Sum(int k) {
        k++;
        int64_t sum = 0;
        while (k >= 1) {
            sum += tree[k];
            k -= GetLSB(k);
        }
        return sum;
    }

    // [l, r]
    int64_t Sum(int l, int r) {
        return Sum(r) - Sum(l - 1);
    }

    void Add(int k, int64_t d) {
        k++;
        while (k < tree.size()) {
            tree[k] += d;
            k += GetLSB(k);
        }
    }
};

struct EulerRange {
    int t_in;
    int t_out;
};
vector<EulerRange> EulerTour(vector<vector<int>> &adjlist, int start) {
    int n = adjlist.size();
    vector<EulerRange> ranges(n);

    int time = -1;
    auto Dfs = [&](auto &&self, int prev, int curr) -> void {
        int t_in = ++time;
        for (int next : adjlist[curr]) {
            if (next != prev)
                self(self, curr, next);
        }
        int t_out = time;
        ranges[curr] = EulerRange{
            t_in,
            t_out,
        };
    };
    Dfs(Dfs, -1, start);

    return ranges;
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> values(n);
    for (int &val : values)
        cin >> val;

    vector<vector<int>> adjlist(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adjlist[a].push_back(b);
        adjlist[b].push_back(a);
    }

    // rooted at 0
    vector<EulerRange> euler_ranges = EulerTour(adjlist, 0);

    // diff array
    BIT bit(n);
    for (int node = 0; node < n; node++) {
        int val = values[node];
        auto [t_in, t_out] = euler_ranges[node];
        bit.Add(t_in, val);
    }

    for (int i = 0; i < q; i++) {
        int op, s;
        cin >> op >> s;
        s--;

        auto [t_in, t_out] = euler_ranges[s];
        if (op == 1) {
            // node s value to x
            int x;
            cin >> x;
            bit.Add(t_in, x - values[s]);
            values[s] = x;
        } else if (op == 2) {
            // calc sum of values in subtree s
            int64_t sum_val = bit.Sum(t_in, t_out);
            cout << sum_val << "\n";
        } else {
            assert(false);
        }
    }
}

int main() {
    solve();
}
