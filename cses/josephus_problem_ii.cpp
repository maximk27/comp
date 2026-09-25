#include <bits/stdc++.h>
using namespace std;

#define dbg(x) "(" << #x << "=" << x << ")"

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

void solve() {
    int n, k;
    cin >> n >> k;

    BIT bit(n + 1);
    for (int i = 0; i < n; i++) {
        bit.Add(i, 1);
    }

    auto Print = [&]() {
        int prev = 1;
        for (int i = 1; i <= n; i++) {
            int val = bit.Sum(i);
            if (val != prev) {
                cout << i << " ";
                prev = val;
            }
        }
        cout << "\n";
    };

    int pos = 0;
    vector<int> order(n);
    for (int i = 0; i < n; i++) {
        int rem = n - i;
        // used to pos + k + 1 (but -1) since shifted
        pos = (pos + k) % rem;

        int idx = pos + 1;

        int lo = 0;
        int hi = n - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (bit.Sum(mid) < idx) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }

        order[i] = lo;
        bit.Add(lo, -1);
    }

    for (int val : order)
        cout << val + 1 << " ";
    cout << "\n";
}

int main() {
    solve();
}
