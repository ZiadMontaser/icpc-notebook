/**
 * Author: Simon Lindholm
 * Date: 2016-03-22
 * License: CC0
 * Source: hacKIT, NWERC 2015
 * Description: A set with support for finding the n'th
 * element, and finding the index of an element.
 * To get a map, change \texttt{null\_type}.
 * Use \texttt{less\_equal} or \texttt{greater\_equal} to turn it into a MultiSet.
 * NOTE in case of using a multi set:
 * - erase function is corrupted and you should use the below utility
 * - lower\_bound and upper\_bound are reversed
 * Time: O(\log N)
 */
#pragma once

#include<ext/pb_ds/assoc_container.hpp> /** keep-include */
#include<ext/pb_ds/tree_policy.hpp> /** keep-include */

using namespace __gnu_pbds;

typedef tree<ll , null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> OrderedSet;
// find_by_order : element at index i
// order_of_key  : how many elements < A for less, and how many ele > A for greater

void erase(OrderedSet &t, int v){
    int rank = t.order_of_key(v);
    auto it = t.find_by_order(rank);
    t.erase(it);
}