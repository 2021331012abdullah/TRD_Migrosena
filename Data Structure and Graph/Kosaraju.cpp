// dfs Function to reach destination
bool dfs(int curr, int des, vector<vector<int>> &adj, vector<int> &vis) {
    if (curr == des) return true;
    vis[curr] = 1;
    for (auto x : adj[curr]) {
        if (!vis[x] && dfs(x, des, adj, vis)) return true;
        else return false;
    }
}
// To tell whether there is path from source to destination
bool isPath(int src, int des, vector<vector<int>> &adj) {
    vector<int> vis(adj.size() + 1, 0);
    return dfs(src, des, adj, vis);
}
// Function to return all the strongly connected component of a graph.
vector<vector<int>> findSCC(int n, vector<vector<int>> &a) {
    vector<vector<int>> ans;
    vector<int> is_scc(n + 1, 0);
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < a.size(); i++)
        adj[a[i][0]].push_back(a[i][1]);
    for (int i = 1; i <= n; i++)
        if (!is_scc[i])
        {   vector<int> scc; scc.push_back(i);
            for (int j = i + 1; j <= n; j++)
            {   if (!is_scc[j] && isPath(i, j, adj) && isPath(j, i, adj))
                {is_scc[j] = 1; scc.push_back(j);}
            }
            ans.push_back(scc);
        }
    return ans;
}