class Solution {
  public:
	int visiblePoints(vector<vector<int>> &points, int angle, vector<int> &location) {
		int extra = 0;
		vector<double> angles;
		for (const vector<int> &p : points) {
			// Ignore points identical to location
			if (p == location) {
				extra++;
				continue;
			}
			// Take the arctg in radians
			angles.push_back(atan2(p[1] - location[1], p[0] - location[0]));
		}

		// Sort agngles
		sort(angles.begin(), angles.end());
		// Duplicate the array and add 2*PI to the angles
		for (int i = 0; i < (int)points.size(); i++) {
			angles.push_back(angles[i] + 2 * M_PI);
		}

		int ans = 0;
		double angle_radians = M_PI * angle / 180;
		// Sliding window
		for (int r = 0, l = 0; r < (int)angles.size(); r++) {
			// Pop all the points out of the field of view
			while (angles[r] - angles[l] > angle_radians) { l++; }
			ans = max(ans, r - l + 1);
		}

		return ans + extra;
	}
};