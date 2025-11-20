/**
 * Author: Mahdi Nasser
 * Description:
 * Time:
 */

struct SegTree {
    vi tree, lazy;
    int n;
    const int e = INT_MAX;

    SegTree(int _n) : n(_n) {
        while (__builtin_popcount(n) != 1) n++;
        tree.assign(2 * n, e);
        lazy.resize(2 * n);
    }

    SegTree(vi& A) {
        n = A.size();
        while (__builtin_popcount(n) != 1) n++;
        tree.assign(2 * n, e);
        lazy.resize(2 * n);
        for (int i = 0; i < A.size(); i++) tree[n + i] = A[i];
        for (int i = n - 1; i >= 1; i--) tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
    }

    int merge(int a, int b) { return min(a, b); }

    void push(int p, int l, int r) {
        if (lazy[p]) {
            tree[p] = ...;
            if (l != r) {
                lazy[p << 1] = ...;
                lazy[p << 1 | 1] = ...;
            }
            lazy[p] = 0;
        }
    }

    int query(int p, int l, int r, int i, int j) {
        push(p, l, r);
        if (i <= l && r <= j) {
            return tree[p];
        }
        if (r < i || l > j) return e;
        int m = l + r >> 1;
        return merge(query(p << 1, l, m, i, j), query(p << 1 | 1, m + 1, r, i, j));
    }

    void update(int p, int l, int r, int i, int j, int x) {
        push(p, l, r);
        if (i <= l && r <= j) {
            lazy[p] = ...;
            push(p, l, r);
            return;
        }
        if (r < i || l > j) return;
        int m = l + r >> 1;
        update(p << 1, l, m, i, j, x);
        update(p << 1 | 1, m + 1, r, i, j, x);
        tree[p] = merge(tree[p << 1], tree[p << 1 | 1]);
    }

    int query(int i, int j) { return query(1, 0, n - 1, i, j); }
    void update(int i, int j, int x) { return update(1, 0, n - 1, i, j, x); }
};