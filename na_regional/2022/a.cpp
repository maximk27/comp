#include <bits/stdc++.h>
#include <sstream>
using namespace std;

#define dbg(x) "(" << #x << "=" << x << ")"

void solve() {
    vector<unordered_map<string, int>> elem_freqs;
    string line;
    while (true) {
        getline(cin, line);
        if (line[0] == 0) {
            break;
        }

        stringstream ss(line);
        char sign;
        ss >> sign;
        int n;
        ss >> n;
        unordered_map<string, int> &elem_freq = elem_freqs.emplace_back();
        for (int i = 0; i < n; i++) {
            string elem;
            ss >> elem;
            int count;
            ss >> count;

            // clang-format off
            elem_freq[elem] += sign == '+'
                ? count
                : -count;
            // clang-format on
        }
    }

    /*
        linear program
        different equation for every constraint
        take gcd final coeffs
    */
}

int main() {
    solve();
}
