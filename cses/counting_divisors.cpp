#include <bits/stdc++.h>
using namespace std;

#define dbg(x) "(" << #x << "=" << x << ")"

constexpr int MAX_X = int(1e6);

// heap zero init
array<int, MAX_X + 1> count_divisors;

void solve() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int &val : nums)
        cin >> val;

    for (int i = 1; i <= MAX_X; i++) {
        for (int j = i; j <= MAX_X; j += i) {
            count_divisors[j]++;
        }
    }

    for (int val : nums) {
        cout << count_divisors[val] << "\n";
    }
}

int main() {
    solve();
}
