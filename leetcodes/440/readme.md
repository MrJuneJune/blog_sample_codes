# Question

```
Given two integers n and k, return the kth lexicographically smallest integer in the range [1, n].

Example 1:

Input: n = 13, k = 2
Output: 10
Explanation: The lexicographical order is [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9], so the second smallest number is 10.
Example 2:

Input: n = 1, k = 1
Output: 1
```

# Ideas

1. Just find all lexicographical and then stop at the kTh?

- I guess slow and no reason. Can figure out the range between where it is interesintg.
  - if n == 200, 1 will take up 101, prefix so no need to calcualte if k > 101
  - for same reason, if k == 111, we know it has to between, 2..20 etcs
