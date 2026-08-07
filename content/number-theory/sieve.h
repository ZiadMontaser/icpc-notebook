/**
 * Author: Unkown
 * Date: Unkown
 * Description: Calculates prime numbers and the smallest prime factor (SPF) for all integers up to N in O(N) time and linear space.
 */
#pragma once

vector<bool> is_prime;
vector<int> primes, divisors;

void sieve(int n) {
    divisors = vector<int>(n + 1);
    is_prime = vector<bool>(n + 1, true);

    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            divisors[i] = i;
            primes.push_back(i);
        }

        for (auto p: primes) {
            if (1LL * i * p > n) {
                break;
            }

            is_prime[i * p] = false;
            divisors[i * p] = p;

            if (i % p == 0) {
                break;
            }
        }
    }
}
