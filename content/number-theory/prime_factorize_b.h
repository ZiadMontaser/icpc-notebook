/**
 * Author: Unknown
 * Date: Unknown
 * Description: Provides prime factorization for any integer $x \le N$. Need Sieve to root N.
 * Usage:
 *  sieve(N);
 *  auto res = factorize(number);
 * Time: $O(\sqrt{x})$
 */
#pragma once

vector<pair<ll,ll>> factorize(ll k) {
    vector<pair<ll,ll>> out;
    for (int p : sv.primes) {
        if ((ll)p * p > k) break;
        if (k % p == 0) {
            ll cnt = 0;
            while (k % p == 0) {
                k /= p;
                cnt++;
            }
            out.push_back({p, cnt});
        }
    }
    if (k > 1) out.push_back({k, 1});
    return out;
}