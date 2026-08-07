/**
 * Author: Ziad
 * Date: 2026-08-07
 * License: CC0
 * Description: Computes the prime factorization of a 64-bit integer $n$ in terms of prime factors and their exponents without the need for a sieve.
 * Time: O(\sqrt{n})
 */
 #pragma once

 vector<pair<ll, ll>> primeFactorize(ll n) {
    vector<pair<ll, ll>> facto;

    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            ll c = 0;  
            while (n % i == 0) {
                n /= i;
                c++;
            }
            facto.push_back({ i, c });  
        }
    }

    if (n > 1) facto.push_back({ n, 1 });

    return facto;
}