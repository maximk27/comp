#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
#define dbg(x) std::cerr << "[DBG] " << #x << " = " << (x) << "\n"
#else
#define dbg(x) 42
#endif

void solve() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int &val : nums)
        cin >> val;

    // -1 if not exists
    vector<int> prevs(n, -1);
    {
        map<int, int> prev_idx;
        for (int i = 0; i < n; i++) {
            if (prev_idx.count(nums[i])) {
                prevs[i] = prev_idx[nums[i]];
            }
            prev_idx[nums[i]] = i;
        }
    }

    int64_t total = 0;
    int l = 0;
    for (int r = 0; r < n; r++) {
        l = max(l, prevs[r] + 1);
        total += r - l + 1;
    }
    cout << total << '\n';
}
// track [l, r] largest distinct subarry
// iter over r, advance l to maintain
//   total += r - l + 1
//   l = max(l, prev[r] + 1)
//
// maintain closest prev per idx
// where advanced to prev[r] + 1 if nums[r] is dup
// else keep l if nums[r] is a just a new value

int main() {
    solve();
}
