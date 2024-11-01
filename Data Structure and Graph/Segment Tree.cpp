//Iterative Segment Tree
ll tree[1 << 19];
void update(int idx, int val) {
  tree[idx += n] += val;
  for (idx /= 2; idx; idx /= 2)
    tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
}
ll query(int lo, int hi) {
  ll ra = 0, rb = 0;
  for (lo += n, hi += n + 1; lo < hi; lo /= 2, hi /= 2) {
    if (lo & 1) ra = ra + tree[lo++];
    if (hi & 1) rb = rb + tree[--hi];
  } return ra + rb;
}
//Persistent Segment Tree
#define LOG 17
struct info { int L, R, val; };
info tree[LOG * MAX];
int root[MAX], arr[MAX], N, NEXT_FREE_INDEX = 1, v_id = 1;
int merge(int x, int y) { return x + y; }
void build(int node, int l, int r) {
  if (l == r) { tree[node].val = arr[l]; return; }
  int mid = (l + r) / 2;
  int x = NEXT_FREE_INDEX++; int y = NEXT_FREE_INDEX++;
  tree[node].L = x; tree[node].R = y;
  build(tree[node].L, l, mid);
  build(tree[node].R, mid + 1, r);
  tree[node].val = merge(tree[x].val, tree[y].val);
}
int update(int node, int l, int r, int pos, int val) {
  if (pos < l || r < pos) return node;
  if (l == r) {
    int x = NEXT_FREE_INDEX++;
    tree[x].val = tree[node].val + val; return x;
  }
  int mid = (l + r) / 2; int z = NEXT_FREE_INDEX++;
  int x = update(tree[node].L, l, mid, pos, val);
  int y = update(tree[node].R, mid + 1, r, pos, val);
  tree[z].val = merge(tree[x].val, tree[y].val);
  tree[z].L = x; tree[z].R = y;  return z;
}
int query(int node, int l, int r, int i, int j) {
  if (j < l || r < i) return 0;
  if (l >= i && r <= j) return tree[node].val;
  int mid = (l + r) / 2; int x = query(tree[node].L, l, mid, i, j);
  int y = query(tree[node].R, mid + 1, r, i, j);
  return merge(x, y);
}
int k_th(int cur, int pre, int l, int r, int k) {
  if (l == r) return l; int mid = (l + r) / 2;
  int l_val = tree[tree[cur].L].val - tree[tree[pre].L].val;
  if (k <= l_val)
    return k_th(tree[cur].L, tree[pre].L, l, mid, k);
  else return k_th(tree[cur].R, tree[pre].R, mid + 1, r, k - l_val);
}
void build(int n) {
  N = n; NEXT_FREE_INDEX = 1; v_id = 1;
  root[0] = NEXT_FREE_INDEX++; build(root[0], 0, N - 1);
}
void update(int version, int pos, int x) {
  root[v_id++] = update(root[version], 0, N - 1, pos, x);
}
int query(int version, int i, int j) {
  return query(root[version], 0, N - 1, i, j);
}
//2D Segment Tree
struct info {
  int sum, mn, mx;
  info() { mn = INT_MAX / 100; mx = INT_MIN / 100; sum = 0; }
  info(int x, int y, int z) { mn = x; mx = y; sum = z; }
  info(int x) { mn = mx = sum = x; }
} tree[3 * MAXN][3 * MAXM];
info leaf(int i, int j) { return info(arr[i][j]); }
info Set(ll x) { return info(x); }
info outOfRange() { return info(); }
info merge(info x, info y) {
  info ans; ans.mn = min(x.mn, y.mn);
  ans.mx = max(x.mx, y.mx); ans.sum = x.sum + y.sum;
  return ans;
}
void build_y(int vx, int lx, int rx, int vy, int ly, int ry) {
  if (ly == ry) {
    if (lx == rx) tree[vx][vy] = leaf(lx, ly);
    else tree[vx][vy] = merge(tree[vx * 2][vy], tree[vx * 2 + 1][vy]);
  } else {
    int my = (ly + ry) / 2;
    build_y(vx, lx, rx, vy * 2, ly, my);
    build_y(vx, lx, rx, vy * 2 + 1, my + 1, ry);
    tree[vx][vy] = merge(tree[vx][vy * 2], tree[vx][vy * 2 + 1]);
  }
}
void build_x(int vx, int lx, int rx) {
  if (lx != rx) {
    int mx = (lx + rx) / 2;
    build_x(vx * 2, lx, mx); build_x(vx * 2 + 1, mx + 1, rx);
  }
  build_y(vx, lx, rx, 1, 0, M - 1);
}
info query_y(int vx, int vy, int tly, int try_, int ly, int ry) {
  if (ly > ry)  return outOfRange();
  if (ly == tly && try_ == ry) return tree[vx][vy];
  int tmy = (tly + try_) / 2;
  auto x = query_y(vx, vy * 2, tly, tmy, ly, min(ry, tmy));
  auto y = query_y(vx, vy * 2 + 1, tmy + 1, try_, max(ly, tmy + 1), ry);
  return merge(x, y);
}
info query_x(int vx, int tlx, int trx, int lx, int rx, int ly, int ry) {
  if (lx > rx) return outOfRange();
  if (lx == tlx && trx == rx)
    return query_y(vx, 1, 0, M - 1, ly, ry);
  int tmx = (tlx + trx) / 2;
  auto x = query_x(vx * 2, tlx, tmx, lx, min(rx, tmx), ly, ry);
  auto y = query_x(vx * 2 + 1, tmx + 1, trx, max(lx, tmx + 1), rx, ly, ry);
  return merge(x, y);
}
void update_y(int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, int val) {
  if (ly == ry) {
    if (lx == rx) tree[vx][vy] = val;
    else tree[vx][vy] = merge(tree[vx * 2][vy], tree[vx * 2 + 1][vy]);
  } else {
    int my = (ly + ry) / 2;
    if (y <= my) update_y(vx, lx, rx, vy * 2, ly, my, x, y, val);
    else update_y(vx, lx, rx, vy * 2 + 1, my + 1, ry, x, y, val);
    tree[vx][vy] = merge(tree[vx][vy * 2], tree[vx][vy * 2 + 1]);
  }
}
void update_x(int vx, int lx, int rx, int x, int y, int val) {
  if (lx != rx) {
    int mx = (lx + rx) / 2;
    if (x <= mx) update_x(vx * 2, lx, mx, x, y, val);
    else update_x(vx * 2 + 1, mx + 1, rx, x, y, val);
  }
  update_y(vx, lx, rx, 1, 0, M - 1, x, y, val);
}
void build(int n, int m) { N = n; M = m; build_x(1, 0, N - 1);}
void update(int i, int j, int val) { //arr[i][j]=val
  update_x(1, 0, N - 1, i, j, val);
}
info query(int x1, int y1, int x2, int y2) {
  return query_x(1, 0, N - 1, x1, x2, y1, y2);
}
