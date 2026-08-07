/**
 * Author: Unknown
 * Date: Unknown
 * Source: custom
 * Description: Number Theoretic Transform (NTT) for multiplying two polynomials of size $K$ in $O(K \log K)$.
 *  The modulo $P$ must be NTT-friendly. You can check this by computing \texttt{\_\_builtin\_ctzll(P - 1)}.
 *  For example, for $P = 998244353$, it prints 23, meaning it supports array sizes up to $2^{23}$.
 *  As a rule of thumb, if \texttt{\_\_builtin\_ctzll(P - 1)} $\ge 18$, it supports array sizes up to $2^{18}$,
 *  which is safe for almost all problems with $N = 10^5$.
 *  Common NTT mods and primitive roots: 998244353 (3), 1004535809 (3), 469762049 (3), 167772161 (3), 754974721 (11).
 *  The current implementation uses primitive root 3 for modulo 998244353.
 * Time: $O(K \log K)$
 * Status: untested
 */
#pragma once

void ntt(vector<ll>& a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        // 3 is the primitive root of 998244353
        ll wlen = power(3, (mod - 1) / len, mod); 
        if (invert) wlen = power(wlen, mod - 2, mod);
        for (int i = 0; i < n; i += len) {
            ll w = 1;
            for (int j = 0; j < len / 2; j++) {
                ll u = a[i + j], v = (a[i + j + len / 2] * w) % mod;
                a[i + j] = (u + v < mod ? u + v : u + v - mod);
                a[i + j + len / 2] = (u - v >= 0 ? u - v : u - v + mod);
                w = (w * wlen) % mod;
            }
        }
    }
    if (invert) {
        ll n_inv = power(n, mod - 2, mod);
        for (ll& x : a) x = (x * n_inv) % mod;
    }
}

vector<ll> multiply(vector<ll> const& a, vector<ll> const& b) {
    if (a.empty() || b.empty()) return {};
    vector<ll> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    fa.resize(n); fb.resize(n);
    
    ntt(fa, false);
    ntt(fb, false);
    for (int i = 0; i < n; i++) {
        fa[i] = (fa[i] * fb[i]) % mod;
    }
    ntt(fa, true);
    
    vector<ll> res(a.size() + b.size() - 1);
    for (int i = 0; i < res.size(); i++) res[i] = fa[i];
    return res;
}