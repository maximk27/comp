#include <bits/stdc++.h>
#include <sstream>
using namespace std;

#define dbg(x) "(" << #x << "=" << x << ")"

struct Point {
    int64_t x, y;

    Point operator-(Point b) {
        return Point{x - b.x, y - b.y};
    }

    int64_t Cross(Point b) {
        return x * b.y - y * b.x;
    }
};

void solve() {
    array<Point, 3> p;
    for (int i = 0; i < 3; i++) {
        cin >> p[i].x >> p[i].y;
    }
    Point v1 = p[1] - p[0];
    Point v2 = p[2] - p[0];
    int64_t res = v1.Cross(v2);
    if (res < 0) {
        // curled down
        cout << "RIGHT\n";
    } else if (res > 0) {
        // curled up
        cout << "LEFT\n";
    } else {
        // = 0
        cout << "TOUCH\n";
    }
}

int main() {
    int t;
    cin >> t;
    while (t--)
        solve();
}
