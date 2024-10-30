struct RMQ {
    int t[2 * N];
    int n;
    void build(int _n) {
        n = _n;
        for (int i = 2 * n - 1; i >= n; i--)
            t[i] = psum[i - n];
        for (int i = n - 1; i > 0; --i)
            t[i] = min(t[i << 1], t[i << 1 | 1]);
    }
    int query(int l, int r) {
        r++;
        int minV = 1e18;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1)  minV = min(minV, t[l++]);
            if (r & 1)  minV = min(minV, t[--r]);
        }
        return minV;
    }
} r;