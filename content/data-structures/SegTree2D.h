/**
 * Author: Mahdi Nasser
 * Description:
 * Time:
 */

template <class T>
struct SegTree2D {
    vector<vector<T>> tree;
    vector<vi>& A;
    int n, m, ni, mi;

    const T e = 0;
    T merge(T a, T b) { return a + b; }

    SegTree2D(vector<vi>& A_) : A(A_) {
        n = A.size(), m = A[0].size();
        ni = n, mi = m;
        while (__builtin_popcount(n) != 1) n++;
        while (__builtin_popcount(m) != 1) m++;

        tree.assign(2 * n, vector<T>(2 * m, e));

        build_x(1, 0, n - 1);
    }
    void build_y(int px, int lx, int rx, int py, int ly, int ry) {
        if (ly == ry) {
            if (lx == rx) {
                if (lx >= ni || ly >= mi)
                    tree[px][py] = e;
                else
                    tree[px][py] = A[lx][ly];
            } else {
                tree[px][py] = merge(tree[px << 1][py], tree[px << 1 | 1][py]);
            }
        } else {
            int my = ly + ry >> 1;
            build_y(px, lx, rx, py << 1, ly, my);
            build_y(px, lx, rx, py << 1 | 1, my + 1, ry);
            tree[px][py] = merge(tree[px][py << 1], tree[px][py << 1 | 1]);
        }
    }
    void build_x(int px, int lx, int rx) {
        if (lx != rx) {
            int mx = lx + rx >> 1;
            build_x(px << 1, lx, mx);
            build_x(px << 1 | 1, mx + 1, rx);
        }
        build_y(px, lx, rx, 1, 0, m - 1);
    }

    T query_y(int px, int ly, int ry) {
        T ra = e, rb = e;
        for (ly += m, ry += m + 1; ly < ry; ly >>= 1, ry >>= 1) {
            if (ly & 1) ra = merge(ra, tree[px][ly++]);
            if (ry & 1) rb = merge(rb, tree[px][--ry]);
        }
        return merge(ra, rb);
    }
    T query(int lx, int rx, int ly, int ry) {
        T ra = e, rb = e;
        for (lx += n, rx += n + 1; lx < rx; lx >>= 1, rx >>= 1) {
            if (lx & 1) ra = merge(ra, query_y(lx++, ly, ry));
            if (rx & 1) rb = merge(rb, query_y(--rx, ly, ry));
        }
        return merge(ra, rb);
    }

    void update_y(int px, int lx, int rx, int py, int ly, int ry, int x, int y, int v) {
        if (ly == ry) {
            if (lx == rx) {
                tree[px][py] = v;
            } else {
                tree[px][py] = tree[px << 1][py] + tree[px << 1 | 1][py];
            }
        } else {
            int my = ly + ry >> 1;
            if (y <= my)
                update_y(px, lx, rx, py << 1, ly, my, x, y, v);
            else
                update_y(px, lx, rx, py << 1 | 1, my + 1, ry, x, y, v);
            tree[px][py] = merge(tree[px][py << 1], tree[px][py << 1 | 1]);
        }
    }
    void update_x(int px, int lx, int rx, int x, int y, T v) {
        if (lx != rx) {
            int mx = lx + rx >> 1;
            if (x <= mx)
                update_x(px << 1, lx, mx, x, y, v);
            else
                update_x(px << 1 | 1, mx + 1, rx, x, y, v);
        }
        update_y(px, lx, rx, 1, 0, n - 1, x, y, v);
    }

    void update(int x, int y, T v) { update_x(1, 0, n - 1, x, y, v); }
};
