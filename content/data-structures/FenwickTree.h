/**
 * Author: Yousef
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: Computes partial sums a[0] + a[1] + ... + a[pos - 1], and updates single elements a[i],
 * taking the difference between the old and new value, and is 1-indexed.
 * Time: Both operations are $O(\log N)$.
 * Status: Stress-tested
 */
#pragma once

// 1-indexed
struct BIT {

    int n;
    vector<long long> b;

    BIT(int _n) {
        n = _n;
        b.assign(n + 1, 0);
    }

    long long get(int idx) {
        long long res = 0;
        while (idx > 0) {
            res += b[idx];
            idx -= idx & -idx;
        }
        return res;
    }

    void add(int idx, int v) {
        while (idx <= n) {
            b[idx] += v;
            idx += idx & -idx;
        }
    }

    long long get(int l, int r) {
        return get(r) - get(l - 1);
    }

    long long get_idx(int idx) {
        return get(idx) - get(idx - 1);
    }

    void set(int idx, int v) {
        int old = get_idx(idx);
        add(idx, -old + v);
    }
};