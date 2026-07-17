#include <bits/stdc++.h>
using namespace std;

struct Item {
    int a, b, c;
};

// by end time
bool ItemVsItem(Item a, Item b) {
    return a.b < b.b;
};
bool ItemVsInt(Item a, int b) {
    return a.b < b;
};

bool IntVsItem(int a, Item b) {
    return a < b.b;
};

void solve() {
    int n;
    cin >> n;
    vector<Item> items(n);
    for (auto &it : items) {
        cin >> it.a >> it.b >> it.c;
    }
    sort(begin(items), end(items), ItemVsItem);
    // include vs exclude day

    // dp[i] most make for items[0...i]
    vector<int64_t> dp(n, 0);
    dp[0] = items[0].c;
    for (int i = 1; i < n; i++) {
        auto [a, b, c] = items[i];
        auto it = lower_bound(begin(items), end(items), a, ItemVsInt);
        int prev_idx = int(it - begin(items) - 1);
        int64_t prev_make = prev_idx >= 0 ? dp[prev_idx] : 0;
        int64_t include = prev_make + c;
        int64_t exclude = dp[i - 1];
        dp[i] = max(include, exclude);
    }
    cout << dp[n - 1] << "\n";
}

int main() {
    solve();
}
