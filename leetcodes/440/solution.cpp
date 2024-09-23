
#include "./solution.h"
#include <algorithm>

int Solution::findKthNumber(int n, int k) {
  int current = 1;
  k--;

  while (k > 0) {
    int count = countPrefix(current, n);
    if (count <= k) {
      // remove all possible values I got
      k -= count;
      current++;  // next number
    } else {
      // case where, it is in between the gap number i.e) n=210, k=150 since it would try to count more (100) instead of 10.
      // 101, 101, = -48, so it finds 20's first
      current *= 10;
      k--;
    }
  }
  return current;
}

int Solution::countPrefix(int prefix, int n) {
  int64_t current = prefix;   // 1, 10, 20
  int64_t next = prefix + 1;  // 2, 20, 21
  int64_t count = 0;          // it would be, 10, 100 and so on...

  while (current <= n) {
    count += std::min(static_cast<int64_t>(n + 1), next) - current;
    current *= 10;
    next *= 10;
  }
  return count;
}
