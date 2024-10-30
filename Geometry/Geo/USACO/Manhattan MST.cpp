#include <bits/stdc++.h>
using namespace std;

const int GRID_SZ = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

int main() {
	int n;
	cin >> n;

	// The distance from the starting point
	vector<vector<int>> d(GRID_SZ, vector<int>(GRID_SZ, -1));
	// mat[x][y] = if (x, y) point is in the input;
	vector<vector<bool>> mat(GRID_SZ, vector<bool>(GRID_SZ));

	priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>,
	               greater<pair<int, pair<int, int>>>>
	    pq;
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		mat[x][y] = 1;
		if (i == 0) {
			d[x][y] = 0;
			pq.push({0, {x, y}});
		}
	}

	auto inside = [&](int x, int y) {
		return 0 <= x && 0 <= y && x < GRID_SZ && y < GRID_SZ;
	};

	// Dijkstra's algorithm
	int ans = 0;
	while (!pq.empty()) {
		int x = pq.top().second.first;
		int y = pq.top().second.second;
		int dist = pq.top().first;
		pq.pop();

		if (dist != d[x][y]) { continue; }
		if (mat[x][y]) {
			mat[x][y] = 0;
			ans += dist;
			d[x][y] = 0;
			pq.push({0, {x, y}});
			if (dist) { continue; }
		}

		for (int dir = 0; dir < 4; dir++) {
			int newx = x + dx[dir];
			int newy = y + dy[dir];
			// Check if it's a new point or if the distance has improved
			if (inside(newx, newy) &&
			    (d[newx][newy] == -1 || dist + 1 < d[newx][newy])) {
				d[newx][newy] = dist + 1;
				pq.push({d[newx][newy], {newx, newy}});
			}
		}
	}

	cout << ans << endl;
}