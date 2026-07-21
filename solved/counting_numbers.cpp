#include <bits/stdc++.h>
using namespace std;

int to_digit(char c) {
    return int(c - '0');
}

int64_t count_lte(vector<vector<vector<vector<int64_t>>>> &dp,
                  const string &digits, int prev_digit, int idx,
                  bool is_started, bool is_tight) {
    int64_t n = digits.size();
    if (idx == n) {
        return 1;
    }

    if (int64_t found = dp[prev_digit][idx][is_started][is_tight];
        found != -1) {
        return found;
    }

    int curr_digit = to_digit(digits[idx]);

    int digit_limit;
    if (!is_tight) {
        // choose any
        digit_limit = 9;
    } else {
        // must stay lte from now on
        digit_limit = curr_digit;
    }

    int64_t total_lte = 0;
    for (int digit = 0; digit <= digit_limit; digit++) {
        if (is_started && digit == prev_digit)
            continue;

        bool next_started = is_started || digit > 0;
        bool next_tight = is_tight && digit == curr_digit;

        total_lte +=
            count_lte(dp, digits, digit, idx + 1, next_started, next_tight);
    }
    return dp[prev_digit][idx][is_started][is_tight] = total_lte;
}

int64_t CountLTE(int64_t val) {
    string digits = to_string(val);

    int64_t n = digits.size();
    vector<vector<vector<vector<int64_t>>>> dp(
        10, vector<vector<vector<int64_t>>>(
                n, vector<vector<int64_t>>(2, vector<int64_t>(2, -1))));

    return count_lte(dp, digits, /*prev_digit=*/0, /*idx=*/0,
                     /*is_started=*/false,
                     /*is_tight=*/true);
}

void solve() {
    int64_t a, b;
    cin >> a >> b;

    int64_t res = CountLTE(b) - CountLTE(a - 1);
    cout << res << "\n";
}

int main() {
    solve();
}
