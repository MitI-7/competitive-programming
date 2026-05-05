import sys
from bisect import bisect, bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import lru_cache
from itertools import combinations, count, groupby, permutations, product
from math import gcd, lcm, pi, sqrt
from string import ascii_lowercase, ascii_uppercase

sys.setrecursionlimit(500000)
INF = float("inf")
YES, Yes, yes, NO, No, no = "YES", "Yes", "yes", "NO", "No", "no"
dy4, dx4 = [0, 1, 0, -1], [1, 0, -1, 0]  # 右，上，左，下
dy8, dx8 = [0, -1, 0, 1, 1, -1, -1, 1], [1, 0, -1, 0, 1, 1, -1, -1]  # 右，下，左，上，右上，右下，左下，左上


def is_bit_on(bit, i):
    return (bit >> i) & 1


def get_bit_set(bit, i, b):
    assert (b == 0 or b == 1)
    if b == 0:
        return bit & ~(1 << i)
    else:
        return bit | (1 << i)


def inside(y, x, H, W):
    return 0 <= y < H and 0 <= x < W


def ceil(a, b):
    return (a + b - 1) // b


def solve():
    MOD = 998244353

    S = input()
    n = len(S)

    ans = 0
    num = 0
    for i in range(n):
        num += 1
        if i + 1 < n and S[i + 1] == S[i]:
            ans += num * (num + 1) // 2
            ans %= MOD
            num = 0
    ans += num * (num + 1) // 2

    print(ans % MOD)


def main():
    solve()


if __name__ == '__main__':
    main()
