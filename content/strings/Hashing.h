/**
 * Author: Simon Lindholm
 * Date: 2015-03-15
 * License: CC0
 * Source: own work
 * Description: Self-explanatory methods for string hashing.
 * Status: stress-tested
 */
#pragma once
const int N = 4e5 + 7;
const int MOD = 1e9+7;
const int PRIME = 331;

ll prime[N];
ll hashes[N];
void init(string s){
    prime[0] = 1;
    for (size_t i = 1; i < N; i++)
    {
        prime[i] = (prime[i-1] * PRIME) % MOD;
    }


    for (size_t i = 0; i < s.size(); i++)
    {
        hashes[i+1] = (hashes[i] * PRIME + s[i] ) % MOD;
    }
}

ll getHash(int l, int r){
    return (hashes[r + 1] - ((hashes[l] * prime[r - l + 1]) % MOD) + MOD) % MOD;
}

int compute_hash(string const& s) {
    const int p1 = 31;
    const int m = 1e9 + 9;
    long long hash_value1 = 0;
    long long p_pow1 = 1;
    for (char c : s) {
        hash_value1 = (hash_value1 + (c - 'A' + 1) * p_pow1) % m;
        p_pow1 = (p_pow1 * p1) % m;
    }
    return hash_value1;
}

int combine_hashed_strings(string const& prevStr, int prevHash,int newHash){
    return add(prevHash,  mul(newHash,  power(31, prevStr.size())));
}

for (char c : s) {
	h1 = (h1 * p1 + (c - 'a' + 1)) % m1;
	h2 = (h2 * p2 + (c - 'a' + 1)) % m2;

	ll ch = (ll(h1) << 32) | h2;

	m[ch]++;
}

struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};

gp_hash_table<int, int, custom_hash> mp;
