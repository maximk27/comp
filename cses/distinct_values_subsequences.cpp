#include <bits/stdc++.h>
using namespace std;

#define dbg(x) "(" << #x << "=" << x << ")"

void solve() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int &val : nums)
        cin >> val;
    sort(begin(nums), end(nums));

    vector<int> freqs;
    {
        int count = 1;
        for (int i = 1; i < n; i++) {
            if (nums[i - 1] != nums[i]) {
                freqs.push_back(count);
                count = 0;
            }
            count++;
        }
        freqs.push_back(count);
    }

    int MOD = 1e9 + 7;
    int64_t total = 1;
    for (int freq : freqs) {
        total = (total + total * freq % MOD) % MOD;
    }
    // exclude empty subseq
    cout << total - 1 << '\n';
}

int main() {
    solve();
}
