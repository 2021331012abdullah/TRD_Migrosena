#include <bits/stdc++.h>

using namespace std;

// BeginCodeSnip{Point Class}
struct Point {
	int x, y;
	Point(int a = 0, int b = 0) : x(a), y(b) {}
	Point operator-(const Point &other) { return {x - other.x, y - other.y}; }
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
	for (Point &point : points) { cin >> point; }
	points.push_back(points[0]);
	long long area = 0;
	for (int i = 0; i < n; i++) {
		area +=
		    (1LL * points[i].x * points[i + 1].y - 1LL * points[i].y * points[i + 1].x);
	}
	area = abs(area);
	long long boundary_points = 0;
	for (int i = 0; i < n; i++) {
		Point diff = points[i + 1] - points[i];
		int g = gcd(abs(diff.x), abs(diff.y));
		boundary_points += g;
	}
	long long interior_points = (area - boundary_points) / 2 + 1;
	cout << interior_points << ' ' << boundary_points;
}