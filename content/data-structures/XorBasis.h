/**
 * Author: Unknown
 * Date: Unknown
 * Source: custom
 * Description: Linear basis over GF(2) (XOR basis). Set \texttt{lg} to the number of bits needed (e.g.\ 30 for $10^9$, 60 for $10^{18}$).
 *  Classical uses:
 *  - Max/Min XOR of any subset: \texttt{maximize(0)} / \texttt{minimize(0)}.
 *  - Check if $x$ is XOR-representable: \texttt{can(x)}.
 *  - Count distinct XOR values: $2^{\text{size}}$ (ignoring zero if not in span).
 *  - $k$-th smallest XOR value (1-indexed): \texttt{kth(k)}, returns $-1$ if $k > 2^{\text{size}}$.
 *  - AND/XOR the whole basis by a mask: \texttt{AND(x)} / \texttt{XOR(x)}.
 *  - NOTE: \texttt{xorSet} tracks which indices form each basis vector; commented out by default.
 * Time: $O(L)$ per insert/query where $L$ = \texttt{lg}.
 * Status: untested
 */
#pragma once

// init
const int lg = 0;

struct XorBasis {
    int size;
    set<int> build[lg];
    array<int, lg> basis;

    void init() {
        size = 0;
        for (int i = lg - 1; i >= 0; --i)
            basis[i] = 0, build[i].clear();
    }

    bool insert(int x) {
        for (int i = lg - 1; i >= 0; --i) {
            if ( ( (x >> i) & 1 ) == 0 ) continue;
            if (not basis[i]) return true;
            x = (x ^ basis[i]);
        }
        return false;
    }

    // careful gives time limit if used a lot
    void xorSet(set<int>& me, set<int>& with) {
        for (int x : with) {
            if ( me.count(x) ) me.erase(x);
            else me.insert(x);
        }
    }

    void insert(int x, int index) {
        if ( not insert(x) ) return;
//        set<int> st = { index };
        for (int i = lg - 1; i >= 0; --i) {
            if ( ( (x >> i) & 1 ) == 0 ) continue;
            if (not basis[i]) {
                basis[i] = x, ++size;
//                build[i] = st;
                return;
            }
//            if (compare[i] < myValue) {
//                swap(comare[i], myValue);
//                swap(bas[i], x);
//            }
            x = (x ^ basis[i]);
//            xorSet(st, build[i]);
        }
    }

    bool can(int x) {
        for (int i = lg - 1; i >= 0; --i)
            if ( basis[i] and ( (x >> i) & 1 ) )
                x = (x ^ basis[i]);
        return x == 0;
    }

    // kth one indexed
    // gets kth ignoring repeated ways to get the number
    // careful if the problem ask for kth considering repeating or not
    int kth(int k) {
        int x = 0;
        for (int i = lg - 1, c = size; i >= 0; --i) {
            if (not basis[i]) continue;
            --c;
            if ( ( (x >> i) & 1 ) ) {
                if ( (1LL << c) >= k ) x = (x ^ basis[i]);
                else k = k - (1LL << c);
            } else if ( k > (1LL << c) ) {
                x = (x ^ basis[i]), k = k - (1LL << c);
            }
        }
        // ignore if needed
        if (k > 1) return -1;
        return x;
    }

    int minimize(int x) {
        for (int i = lg - 1; i >= 0; --i)
            x = min( x, (x ^ basis[i]) );
        return x;
    }

    int maximized(int x) {
        for (int i = lg - 1; i >= 0; --i)
            x = max( x, (x ^ basis[i]) );
        return x;
    }

    void AND(int x) {
        size = 0;
        vector<int> update;
        for (int i = lg - 1; i >= 0; --i) {
            basis[i] = (basis[i] & x);
            if (basis[i]) update.push_back(basis[i]);
            basis[i] = 0;
        }
        for (int& value : update) insert(value);
    }

    // you should shift and make leading one and check for that one
    // when you want the actual basis remove the shift - insert again and get your actual basis
    void XOR(int x) {
        for (int i = lg - 1; i >= 0; --i)
            if (basis[i] & 1) basis[i] ^= x;
    }
};