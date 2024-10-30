int val[MAX], cnt[MAX], sz[MAX], ans[MAX]; bool big[MAX];
void processQuery(int v) { /*ans[v] = cnt[ ?? ]; */}
void getSize(int v, int p) {
  sz[v] = 1; for (auto u : adj[v]) {
    if ( u == p ) continue; getSize(u, v); sz[v] += sz[u];
  }
}
void add(int v, int p, int x) {
  cnt[ val[v] ] += x;
  for (auto u : adj[v])if (u != p && !big[u]) add(u, v, x);
}
void dfs(int v, int p, bool keep) {
  int mx = -1, bigChild = -1; for (auto u : adj[v])
    if (u != p && sz[u] > mx) mx = sz[u], bigChild = u;
  for (auto u : adj[v])
    if (u != p && u != bigChild) dfs(u, v, 0);
  if (bigChild != -1) dfs(bigChild, v, 1), big[bigChild] = 1;
  add(v, p, 1);  processQuery(v);
  if (bigChild != -1) big[bigChild] = 0;
  if (keep == 0) { add(v, p, -1); }
}
void init(int root = 1) {getSize(root, -1); dfs(root, -1, 0);}