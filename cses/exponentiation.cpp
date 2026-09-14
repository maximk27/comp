#include <bits/stdc++.h>
using namespace std;

#define dbg(x) "(" << #x << "=" << x << ")"

int64_t Pow(int64_t base, int64_t exp, int64_t mod) {
    base %= mod;
    int64_t res = 1;
    while (exp >= 1) {
        if (exp % 2 == 1) {
            res = (res * base) % mod;
            exp--;
            // 1 -> 0
        }
        // 0
        exp >>= 1;
        base = (base * base) % mod;
    }
    return res;
}

void solve() {
    int n;
    cin >> n;
    int MOD = int(1e9 + 7);
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        int res = Pow(a, b, MOD);
        cout << res << "\n";
    }
}

int main() {
    solve();
}
