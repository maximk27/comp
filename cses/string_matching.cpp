#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
#define dbg(x) std::cerr << "[DBG] " << #x << " = " << (x) << "\n"
#else
#define dbg(x) 42
#endif

class PrefixHash {
    static constexpr int P = 9973;
    static constexpr int M = 1e9 + 9;

    vector<int64_t> pref;
    vector<int64_t> pow;

public:
    PrefixHash(const string &s) {
        int n = s.size();
        pref.resize(n + 1, 0);
        pow.resize(n + 1, 1);

        for (int i = 0; i < n; i++) {
            pow[i + 1] = (pow[i] * P) % M;
            pref[i + 1] = (pref[i] * P + (s[i] - 'a' + 1)) % M;
        }
    }

    // [l, r] 0 indexed
    int64_t query(int l, int r) const {
        int64_t res = (pref[r + 1] - (pref[l] * pow[r - l + 1]) % M) % M;
        return (res + M) % M;
    }
};

void solve() {
    string s, p;
    cin >> s >> p;

    int n = s.size();
    int m = p.size();

    PrefixHash s_hash(s), p_hash(p);
    int64_t target = p_hash.query(0, m - 1);

    int64_t count = 0;
    for (int i = 0; i + m - 1 < n; i++) {
        int j = i + m - 1;
        if (s_hash.query(i, j) == target) {
            count++;
        }
    }
    cout << count << '\n';
}

int main() {
    solve();
}
