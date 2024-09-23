#include "./solution.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

int Solution::minExtraChar(std::string s,
                           const std::vector<std::string>& dictionary) {
  int n = s.length();

  // Convert the dictionary into a set for fast lookup
  std::unordered_set<std::string> set(dictionary.begin(), dictionary.end());

  // DP array to store the minimum number of extra characters
  std::vector<int> dp(n + 1, 0);

  // Iterate backwards from the last index to the first
  for (int i = n - 1; i >= 0; --i) {
    // Assume the current character is an extra one
    dp[i] = dp[i + 1] + 1;

    // Check all possible substrings starting at index i
    for (int j = i; j < n; ++j) {
      std::string sub = s.substr(i, j - i + 1);
      if (set.count(sub)) {
        // If the substring is in the dictionary, update dp[i]
        dp[i] = std::min(dp[i], dp[j + 1]);
      }
    }
  }

  // The answer is the minimum extra characters for the entire string s
  return dp[0];
}
