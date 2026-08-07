/**
 * Author: Unknown
 * Date: Unknown
 * Description: Provides prime factorization for any integer $x \le N$. Need Sieve to N.
 * Usage:
 *  sieve(N);
 *  auto res = prime_factorization(number);
 * Time: $O(\log x)$
 */
#pragma once

vector<pair<int, int>> prime_factorization(int x) {
    vector<pair<int, int>> P;
    while (x > 1) {
        int p = divisors[x], cnt = 0;
        while (x % p == 0) {
            x /= p;
            cnt++;
        }
        P.emplace_back(p, cnt);
    }
    return P;
}