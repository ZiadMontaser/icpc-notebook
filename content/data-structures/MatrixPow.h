/**
 * Author: Unknown
 * Date: Unknown
 * Source: custom
 * Description: Basic matrix struct for fast exponentiation.
 *  Can be used to solve linear recurrences in $O(N^3 \log K)$ time.
 *  - When a recurrence depends on $i^2$, construct it as a complete square: $(i+1)^2 = i^2 + 2i + 1$.
 *  - Fermat's Little Theorem (FLT): $a^{p-1} \equiv 1 \pmod p$.
 *    When working with powers, take exponents modulo $(p-1)$.
 *  - For multiplication recurrences, you can take the $\ln$ of both sides to linearize it!
 * Time: $O(N^3 \log K)$
 * Status: untested
 */
#pragma once

struct Matrix {
    vector<vector<ll>>m;
    int _n;
    Matrix(int n, int v = 0) : _n(n) {
        m.assign(_n,vector<ll>(_n,v));
    }
    Matrix operator*(Matrix&other)const{
        Matrix ans(_n);
        for (ll i = 0; i < _n; i++)
            for (ll j = 0; j < _n; j++)
                for (ll k = 0; k < _n; k++)
                    ans.m[i][j]+=m[i][k]*other.m[k][j],
                        ans.m[i][j]%=MOD;
        return ans;
    }

    Matrix operator^(ll pw)const{
        Matrix result(_n);
        for(int i = 0; i < _n; i++) result.m[i][i]=1;
        Matrix trans = *this;
        while(pw){
            if(pw&1)result=result*trans;
            trans=trans*trans;
            pw/=2;
        }
        return result;
    }
};