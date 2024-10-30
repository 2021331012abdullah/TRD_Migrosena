const int N = 2020;
int g[N][N], w[N], to[N], selected[N];
long long Prims(int n, vector< pair<int, int> > &edges) {
  long long ans = 0;
  for (int i = 1; i <= n; i++) w[i] = 1e9, selected[i] = 0, to[i] = -1;
  w[1] = 0;
  for (int i = 1; i <= n; i++) {
    int u = -1;
    for (int j = 1; j <= n; j++) if (!selected[j] && (u == -1 || w[j] < w[u])) u = j;
    if (w[u] == 1e9) return - 1; //NO MST
    selected[u] = 1;
    ans += w[u];
    if (to[u] != -1) edges.emplace_back(u, to[u]); //order of the edges may be changed
    for (int v = 1; v <= n; v++) if (g[u][v] < w[v]) w[v] = g[u][v], to[v] = u;
  }
  return ans;
}