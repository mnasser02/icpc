/**
 * Author: Mahdi Nasser
 * Description:
 * Time:
 */

struct LCA {
    vector<vi>&AL, up, dp;
    vi d;
    int n, log;

    LCA(vector<vi>& AL_) : AL(AL_) {
        n = AL.size();
        d.resize(n);
        log = log2(n) + 2;
        up.assign(n, vi(log));
        dp.assign(n, vi(log));
        for (int u = 0; u < n; u++)
            // init dp[u][0]
            ;
        dfs(0, -1);
    }

    int merge(int a, int b) { return max(a, b); }

    void dfs(int u, int p) {
        for (int v : AL[u]) {
            if (v == p) continue;
            d[v] = d[u] + 1;
            up[v][0] = u;
            for (int j = 1; j < log; j++) {
                dp[v][j] = merge(dp[v][j - 1], dp[up[v][j - 1]][j - 1]);
                up[v][j] = up[up[v][j - 1]][j - 1];
            }
            dfs(v, u);
        }
    }

    int get(int u, int v) {
        if (d[u] < d[v]) swap(u, v);
        int k = d[u] - d[v];
        int res = 0;
        for (int j = 0; j < log; j++) {
            if (k & (1 << j)) {
                res = merge(res, dp[u][j]);
                u = up[u][j];
            }
        }
        if (u == v) {
            res = merge(res, dp[u][0]);
            return res;
        }
        for (int j = log - 1; j >= 0; j--) {
            if (up[u][j] != up[v][j]) {
                res = merge(res, dp[u][j]);
                res = merge(res, dp[v][j]);
                u = up[u][j];
                v = up[v][j];
            }
        }
        res = merge(res, dp[u][1]);
        res = merge(res, dp[v][0]);
        return res;
    }
};