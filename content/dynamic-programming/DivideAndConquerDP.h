/**
 * Author: Mahdi Nasser
 * Description: $$ dp(i,j) = \min_{0 \le k \le j} \, dp(i-1, k-1) + C(k,j)$$
 * We need $opt(i,j) \le opt(i,j+1)$.
 * C satisfying the quadrangle inequality is sufficient:  $$C(a,c) + C(b,d) \le
 * C(a,d) + C(b,c) \quad \forall a \le b \le c \le d.$$
 * Time: O(nm logn)
 */

int m, n;
vector<long long> dp_before, dp_cur;

long long C(int i, int j);

// compute dp_cur[l], ... dp_cur[r] (inclusive)
void compute(int l, int r, int optl, int optr) {
    if (l > r) return;

    int mid = (l + r) >> 1;
    pair<long long, int> best = {LLONG_MAX, -1};

    for (int k = optl; k <= min(mid, optr); k++) {
        best = min(best, {(k ? dp_before[k - 1] : 0) + C(k, mid), k});
    }

    dp_cur[mid] = best.first;
    int opt = best.second;

    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}

long long solve() {
    dp_before.assign(n, 0);
    dp_cur.assign(n, 0);

    for (int i = 0; i < n; i++) dp_before[i] = C(0, i);

    for (int i = 1; i < m; i++) {
        compute(0, n - 1, 0, n - 1);
        dp_before = dp_cur;
    }

    return dp_before[n - 1];
}