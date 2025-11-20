/**
 * Author: Mahdi Nasser
 * Description:
 * Time:
 */

template <int M>
struct mint {
    int v;

    explicit operator int() const { return v; }

    mint() : v(0) {}

    mint(ll _v) : v(int(_v % M)) { v += (v < 0) * M; }

    mint& operator+=(mint o) {
        if ((v += o.v) >= M) v -= M;
        return *this;
    }

    mint& operator-=(mint o) {
        if ((v -= o.v) < 0) v += M;
        return *this;
    }

    mint& operator*=(mint o) {
        v = int((ll)v * o.v % M);
        return *this;
    }

    mint& operator/=(const mint& o) { return (*this) *= inv(o); }

    friend mint mpow(mint a, ll p) {
        assert(p >= 0);
        return p == 0 ? 1 : mpow(a * a, p / 2) * (p & 1 ? a : 1);
    }

    friend mint inv(mint a) {
        assert(a.v != 0);
        return mpow(a, M - 2);
    }

    friend mint operator+(mint a, mint b) { return a += b; }
    friend mint operator-(mint a, mint b) { return a -= b; }
    friend mint operator*(mint a, mint b) { return a *= b; }
    friend mint operator/(mint a, mint b) { return a /= b; }
};