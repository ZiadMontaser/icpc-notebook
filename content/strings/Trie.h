/**
 * Author: Unknown
 * Date: Unknown
 * Source: custom
 * Description: Pointer-based Trie for 26 lowercase letters.
 *  Stores insert count (\texttt{Prefix}) and end count (\texttt{IsEnd}) per node.
 *  Classical uses (adapt child size for binary tries):
 *  - Max/Min XOR pair or query: build binary trie (32 levels), greedily pick opposite bit.
 *  - Max XOR with element $\le m$: offline sort queries and array by $m$, insert then query.
 *  - Count pairs with XOR in $[lo, hi]$: store count metadata, answer $f(hi) - f(lo-1)$.
 *  - Count subarrays with XOR $< K$: use prefix XOR and binary trie.
 *  - Dynamic insert/delete: decrement Prefix/IsEnd on deletion path.
 * Time: $O(L)$ per operation where $L$ is the string/integer length.
 * Status: untested
 */
#pragma once

struct Trie{
    struct Node{
        Node*child[26];
        int IsEnd,Prefix;
        Node(){
            memset(child,0,sizeof child);
            IsEnd=Prefix=0;
        }
    };
    Node*root=new Node();
    void insert(string &s)
    {
        Node*cur=root;
        for(auto it:s)
        {
            int idx=it-'a';
            if(cur->child[idx]==0)
            {
                cur->child[idx]=new Node();
            }
            cur=cur->child[idx];
            cur->Prefix++;
        }
        cur->IsEnd++;
    }
    bool SearchWord(string &s)
    {
        Node*cur=root;
        for(auto it:s)
        {
            int idx=it-'a';
            if(cur->child[idx]==0)return 0;
            cur=cur->child[idx];
        }
        return cur->IsEnd;
    }
    int CountWord(string &s)
    {
        Node*cur=root;
        for(auto it:s)
        {
            int idx=it-'a';
            if(cur->child[idx]==0)return 0;
            cur=cur->child[idx];
        }
        return cur->IsEnd;
    }
    int CountPrefix(string &s)
    {
        Node*cur=root;
        for(auto it:s)
        {
            int idx=it-'a';
            if(cur->child[idx]==0)return 0;
            cur=cur->child[idx];
        }
        return cur->Prefix;
    }
};