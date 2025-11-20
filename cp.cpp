#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> AL;
int n, m;
vector<bool> art;
vector<int> low, num;
int timer;
void dfs(int u, int p) {
    low[u] = num[u] = timer++;
    int children = 0;
    for (int v : AL[u]) {
        if (num[v] == -1) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            children++;
            if (low[v] >= num[u] && p != -1) {
                art[u] = 1;
            }
        } else if (p != v) {
            low[u] = min(low[u], num[v]);
        }
    }
    if (p == -1 && children > 1) {
        art[u] = 1;
    }
}

void art_points() {
    low.assign(n, -1);
    num.assign(n, -1);
    art.assign(n, 0);
    timer = 0;
    for (int u = 0; u < n; u++) {
        if (num[u] == -1) {
            dfs(u, -1);
        }
    }
}

int main() {
    while (cin >> n >> m && (n || m)) {
        AL.resize(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            AL[u].push_back(v);
            AL[v].push_back(u);
        }

        art_points();
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (art[i]) {
                cnt++;
            }
        }
        cout << cnt << "\n";
        AL.clear();
    }
    return 0;
}