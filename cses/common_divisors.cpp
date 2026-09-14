#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

#define dbg(x) "(" << #x << "=" << x << ")"

void solve() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int &val : nums)
        cin >> val;

    int MAX_X = *max_element(begin(nums), end(nums));
    vector<int> numfreqs(MAX_X + 1, 0);
    for (int val : nums)
        numfreqs[val]++;

    for (int d = MAX_X; d >= 1; d--) {
        int count_divs = 0;
        for (int val = d; val <= MAX_X; val += d) {
            if (count_divs >= 2)
                break;
            count_divs += numfreqs[val];
        }

        if (count_divs >= 2) {
            cout << d << "\n";
            return;
        }
    }
    // guaranteed hit since at least 2 elements and 1 divides all
}

int main() {
    solve();
}
