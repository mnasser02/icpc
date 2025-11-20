/**
 * Author: Mahdi Nasser
 * Description:
 * Time:
 */

// id is the next unused id to assign to any new node created
// par is the standard definition of dsu parent
// adj will store the KRT
int id, par[2 * MAXN];
vector<int> adj[2 * MAXN];

int find(int u) { return par[u] == u ? u : par[u] = find(par[u]); }

void unite(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return;
    par[u] = par[v] = par[id] = id;
    adj[id] = {u, v};
    id++;
}
