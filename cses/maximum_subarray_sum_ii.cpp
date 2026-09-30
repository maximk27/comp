#include <bits/stdc++.h>
#include <cassert>
using namespace std;

#define dbg(x) "(" << #x << "=" << x << ")"

void solve() {
    int n, a, b;
    cin >> n >> a >> b;
    vector<int64_t> nums(n);
    for (int64_t &val : nums)
        cin >> val;

    vector<int64_t> presum = nums;
    for (int i = 1; i < n; i++) {
        presum[i] += presum[i - 1];
    }

    auto Get = [&](int idx) {
        // clang-format off
        return idx == -1
            ? 0
            : presum[idx];
        // clang-format on
    };

    /*
    let len = i - j + 1
    sorted on presum[j]
    set for all points j s.t a<=len<=b

    choose min from set 1, check the subarray
    compare to max

    push i - a + 1 to set
    pop i - b + 1 from set
    */

    deque<int> dq = {-1};
    int64_t most = INT64_MIN;
    for (int i = a - 1; i < n; i++) {
        assert(!dq.empty());

        int j = dq.front();

        int len = i - j;
        assert(len >= a && len <= b);

        int64_t curr = Get(i) - Get(j);
        most = max(most, curr);

        int a_idx = i - a + 1;
        while (!dq.empty() && Get(a_idx) <= Get(dq.back())) {
            dq.pop_back();
        }
        dq.push_back(a_idx);

        int b_idx = i - b;
        if (dq.front() == b_idx) {
            dq.pop_front();
        }
    }

    cout << most << '\n';
}

int main() {
    solve();
}
