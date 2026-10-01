#include <bits/stdc++.h>
#include <sstream>
using namespace std;

#define dbg(x) "(" << #x << "=" << x << ")"

void solve() {
    /*
        traveling tsp ish with constraint
        consider dp[mask, i] where
        mask is bitmask over caught pokemon
        i means ended on ith stop

        from mask,i, extend by considering every j next stop
        n_mask = mask ^ (1 << pokemon[j])
        n_i = j
        n_dp = dp[mask,i] + dist(point[i], point[j])
    */
}

int main() {
    solve();
}
