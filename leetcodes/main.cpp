#include <iostream>
#include <string>
#include <vector>
#include "2707/solution.h"

int main() {
  Solution solution;
  std::string s1 = "leetscode";
  std::vector<std::string> dictionary1 = {"leet", "code", "leetcode"};
  std::cout << solution.minExtraChar(s1, dictionary1) << "\n";  // Output: 1
}
