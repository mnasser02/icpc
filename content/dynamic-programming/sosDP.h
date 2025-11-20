/**
 * Author: Mahdi Nasser
 * Description:
 * $S(x, i)$ contains all subset masks of $x$ whose bits to the left of the $i$-th bit match those of $x$.
    $$S(x,i) =
    \begin{cases}
    S(x,i-1) & \text{if the $i$-th bit is 0}, \\[6pt]
    S(x,i-1) \,\cup\, S(x \oplus 2^i,\, i-1) & \text{if the $i$-th bit is 1}.
    \end{cases}
    $$
 * Time:
 */

sos = a;
for (int i = 0; i < n; i++) {
    for (int x = 0; x < (1 << n); x++) {
        if (x & (1 << i)) {
            sos[x] += sos[x ^ (1 << i)];
        }
    }
}