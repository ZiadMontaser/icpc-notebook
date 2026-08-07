/**
 * Author: Unknown
 * Date: Unknown
 * Description: Checks whether a 64-bit integer $x$ is a perfect square safely handling floating-point precision errors.
 * Time: O(1)
 */
#pragma once

bool is_perfect_square(ll x)
{
    ll y = (ll)sqrtl(x);
    while(y * y < x) y++;
    while(y * y > x) y--;
    return x == y * y;
}