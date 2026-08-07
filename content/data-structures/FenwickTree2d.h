/**
 * Author: Simon Lindholm
 * Date: 2017-05-11
 * License: CC0
 * Source: folklore
 * Description: Computes sums a[i,j] for all i<I, j<J, and increases single elements a[i,j].
 *  Requires that the elements to be updated are known in advance (call fakeUpdate() before init()).
 * Time: $O(\log^2 N)$. (Use persistent segment trees for $O(\log N)$.)
 * Status: stress-tested
 */
#pragma once

#include "FenwickTree.h"

struct FT2 {
	vector<vi> ys; vector<FT> ft;
	FT2(int limx) : ys(limx) {}
	void fakeUpdate(int x, int y) {
		for (; x < sz(ys); x |= x + 1) ys[x].push_back(y);
	}
	void init() {
		for (vi& v : ys) sort(all(v)), ft.emplace_back(sz(v));
	}
	int ind(int x, int y) {
		return (int)(lower_bound(all(ys[x]), y) - ys[x].begin()); }
	void update(int x, int y, ll dif) {
		for (; x < sz(ys); x |= x + 1)
			ft[x].update(ind(x, y), dif);
	}
	ll query(int x, int y) {
		ll sum = 0;
		for (; x; x &= x - 1)
			sum += ft[x-1].query(ind(x-1, y));
		return sum;
	}
};

template <typename T> class OfflineBIT2D {
private:
	/**
	* Description: Offline 2D Fenwick Tree. Computes rectangle sums and updates single elements.
	*  Requires all point coordinates to be updated/queried to be known in advance and passed to the constructor.
	*  Automatically deduplicates coordinates to save memory. 0-indexed API.
	* Time: $O(\log^2 N)$ per query/update, $O(M \log M + M \log^2 N)$ initialization where $M$ is the number of points.
	* Memory: $O(M \log N)$
	*/
    const int n;
    vector<vector<int>> vals;
    vector<vector<T>> bit;

    /** @return the first index i such that v[i] <= x */
    int ind(const vector<int> &v, int x) {
        return upper_bound(begin(v), end(v), x) - begin(v) - 1;
    }

public:
    OfflineBIT2D(int n, vector<array<int, 2>> &todo) : n(n), vals(n + 1), bit(n + 1) {
        sort(begin(todo), end(todo),
             [](const array<int, 2> &a, const array<int, 2> &b) -> bool {
                 return a[1] < b[1];
             });

        for (int i = 1; i <= n; i++) { vals[i].push_back(0); }
        for (auto [r, c] : todo) {
            r++, c++;
            for (; r <= n; r += r & -r) {
                if (vals[r].back() != c) { vals[r].push_back(c); }
            }
        }
        for (int i = 1; i <= n; i++) { bit[i].resize(vals[i].size()); }
    }

    /** adds val to the point (r, c) */
    void add(int r, int c, T val) {
        r++, c++;
        for (; r <= n; r += r & -r) {
            int i = ind(vals[r], c);
            for (; i < bit[r].size(); i += i & -i) { bit[r][i] += val; }
        }
    }

    /** @returns sum of points with row in [0, r] and column in [0, c] */
    T rect_sum(int r, int c) {
        r++, c++;
        T sum = 0;
        for (; r > 0; r -= r & -r) {
            int i = ind(vals[r], c);
            for (; i > 0; i -= i & -i) { sum += bit[r][i]; }
        }
        return sum;
    }

    /** @returns sum of points with row in [r1, r2] and column in [c1, c2] */
    T rect_sum(int r1, int c1, int r2, int c2) {
        return rect_sum(r2, c2) - rect_sum(r2, c1 - 1) - rect_sum(r1 - 1, c2) +
               rect_sum(r1 - 1, c1 - 1);
    }
};

