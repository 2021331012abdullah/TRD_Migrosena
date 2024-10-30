#include <bits/stdc++.h>

using namespace std;

// BeginCodeSnip{Point Class}
struct Point {
	int x, y;
	Point(int a = 0, int b = 0) : x(a), y(b) {}

	friend istream &operator>>(istream &in, Point &p) {
		int x, y;
		in >> p.x >> p.y;
		return in;
	}
};
// EndCodeSnip

bool on_segment(const Point &p, const Point &p1, const Point &p2) {
	int a = min(p1.x, p2.x);
	int b = max(p1.x, p2.x);
	int x = min(p1.y, p2.y);
	int y = max(p1.y, p2.y);
	return 1LL * (p.y - p1.y) * (p2.x - p1.x) == 1LL * (p.x - p1.x) * (p2.y - p1.y) &&
	       a <= p.x && p.x <= b && x <= p.y && p.y <= y;
}

long long trigonometric_sense(Point p, Point p1, Point p2) {
	return 1LL * (p1.x - p.x) * (p2.y - p.y) - 1LL * (p2.x - p.x) * (p1.y - p.y);
}

int main() {
	int n, m;
	cin >> n >> m;
	vector<Point> poly(n);
	for (Point &p : poly) { cin >> p; }
	for (int j = 0; j < m; j++) {
		Point p;
		cin >> p;
		// Intersection count
		int cnt = 0;
		bool flag = false;
		for (int i = 0; i < n; i++) {
			int j = (i + 1) % n;
			if (on_segment(p, poly[i], poly[j])) {
				flag = true;
				break;
			}
			if (poly[i].y <= p.y && p.y < poly[j].y &&
			    trigonometric_sense(p, poly[i], poly[j]) > 0)
				cnt++;
			if (poly[j].y <= p.y && p.y < poly[i].y &&
			    trigonometric_sense(p, poly[j], poly[i]) > 0)
				cnt++;
		}
		if (flag) {
			cout << "BOUNDARY" << '\n';
		} else {
			cout << (cnt % 2 ? "INSIDE" : "OUTSIDE") << '\n';
		}
	}
}