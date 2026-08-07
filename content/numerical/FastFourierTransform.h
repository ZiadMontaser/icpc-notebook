/**
 * Author: Ludo Pulles, chilli, Simon Lindholm
 * Date: 2019-01-09
 * License: CC0
 * Source: http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf (do read, it's excellent)
   Accuracy bound from http://www.daemonology.net/papers/fft.pdf
 * Description: fft(a) computes $\hat f(k) = \sum_x a[x] \exp(2\pi i \cdot k x / N)$ for all $k$. N must be a power of 2.
 *   Modified to multiply two integer polynomials modulo a global \texttt{mod}.
 *   \texttt{multiply(a, b)} computes $c[x] = \sum a[i]b[x-i] \pmod{mod}$.
 *   \texttt{poly\_pow(poly, p)} computes the polynomial to the power of $p$ modulo \texttt{mod}.
 *   Rounding is safe if $(\sum A_i B_i) \log_2 N < 9 \cdot 10^{14}$
 *   (in practice $10^{16}$; higher for random inputs).
 *   Otherwise, use NTT/FFTMod.
 * Time: O(N \log N) with $N = |A|+|B|$ ($\tilde 1s$ for $N=2^{22}$)
 * Status: somewhat tested
 * Details: An in-depth examination of precision for both FFT and FFTMod can be found
 * here (https://github.com/simonlindholm/fft-precision/blob/master/fft-precision.md)
 */
#pragma once

const long double PI = acos(-1);
typedef complex<double> C;
#define rep(i,a,b)  for(int i = a; i < b; i++)
void fft(vector<C>& a) {
    int n = a.size(), L = 31 - __builtin_clz(n);
    static vector<complex<long double>> R(2, 1);
    static vector<C> rt(2, 1);  // (^ 10% faster if double)
    for (static int k = 2; k < n; k *= 2) {
        R.resize(n); rt.resize(n);
        auto x = polar(1.0L, acos(-1.0L) / k);
        rep(i,k,2*k) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
    }
    vector<ll> rev(n);
    rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
                // C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
                auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
                C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
}
vector<ll> multiply(const vector<ll> & a, const vector<ll> & b) {
    if (a.empty() || b.empty()) return {};
    vector<ll> res(a.size() + b.size() - 1);
    int L = 32 - __builtin_clz(res.size()), n = 1 << L;
    vector<C> in(n), out(n);
    copy(a.begin(),a.end(), begin(in));
    rep(i,0,b.size()) in[i].imag(b[i]);
    fft(in);
    for (C& x : in) x *= x;
    rep(i,0,n) out[i] = in[-i & (n - 1)] - conj(in[i]);
    fft(out);
    rep(i,0,res.size()) res[i] = (mod+(ll)round(imag(out[i]) / (4 * n))) % mod;
    return res;
}

vector<ll> poly_pow(vector<ll> poly, int p) {
    vector<ll> ans{1};
    while (p) {
        if(p&1) ans = multiply(ans, poly);
        poly = multiply(poly, poly);
        p >>= 1;
    }
    return ans;
}

