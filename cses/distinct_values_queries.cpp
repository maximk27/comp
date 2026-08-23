#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
#define dbg(x) std::cerr << "[DBG] " << #x << " = " << (x) << "\n"
#else
#define dbg(x) 42
#endif

int BLOCK_SIZE;

struct Query {
    int l, r, idx;
    bool operator<(Query q) const {
        return make_pair(l / BLOCK_SIZE, r) < make_pair(q.l / BLOCK_SIZE, q.r);
    }
};

void Compress(vector<int> &nums) {
    vector<int> vals = nums;
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    for (int i = 0; i < nums.size(); i++) {
        nums[i] =
            int(lower_bound(begin(vals), end(vals), nums[i]) - begin(vals));
    }
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> nums(n);
    for (int &val : nums)
        cin >> val;

    Compress(nums);

    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        auto &curr = queries[i];
        cin >> curr.l >> curr.r;
        curr.l--;
        curr.r--;
        curr.idx = i;
    }

    BLOCK_SIZE = max(1, int(sqrt(n)));

    int distinct = 0;
    vector<int> w_freqs(n, 0);

    auto Get = [&]() -> int { return distinct; };

    auto Add = [&](int idx) {
        if (++w_freqs[nums[idx]] == 1) {
            distinct++;
        }
    };
    auto Remove = [&](int idx) {
        if (--w_freqs[nums[idx]] == 0) {
            distinct--;
        }
    };

    sort(queries.begin(), queries.end());
    // range [l, r]
    int l = 0;
    int r = -1;
    vector<int> ans(q);
    for (Query curr : queries) {
        // expand
        while (l > curr.l) {
            l--;
            Add(l);
        }
        while (r < curr.r) {
            r++;
            Add(r);
        }
        // shrink
        while (l < curr.l) {
            Remove(l);
            l++;
        }
        while (r > curr.r) {
            Remove(r);
            r--;
        }
        ans[curr.idx] = Get();
    }

    for (int val : ans) {
        cout << val << "\n";
    }
}

int main() {
    solve();
}
