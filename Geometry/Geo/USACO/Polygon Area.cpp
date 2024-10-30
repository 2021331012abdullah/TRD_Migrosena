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

int main() {
	int n;
	cin >> n;
	vector<Point> points(n);
	for (auto &p : points) { cin >> p; }
	points.push_back(points[0]);

	long long area = 0;
	for (int i = 0; i < points.size(); i++) {
		area +=
		    (1LL * points[i].x * points[i + 1].y - 1LL * points[i].y * points[i + 1].x);
	}
}