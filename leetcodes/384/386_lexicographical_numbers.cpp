// 386. Lexicographical Numbers
// Medium
// Topics
// Companies
// Given an integer n, return all the numbers in the range [1, n] sorted in lexicographical order.
//
// You must write an algorithm that runs in O(n) time and uses O(1) extra space.
//
// 20
//
// 1 -> 10 -> 2 -> 20 -> 3 -> 4
// 1 -> 2
// 10 -> 11 -> ...
// 100 > 20 cancel
#include <vector>

class Solution {
 public:
  std::vector<int> lexicalOrder(int n) {
    n_ = n;
    recur(0);
    return ans_;
  }

 private:
  std::vector<int> ans_;
  int n_;

  void recur(int current_digit) {
    if (current_digit > n_) {
      return;
    }
    if (current_digit > 0) {
      ans_.push_back(current_digit);
      return;
    }
    for (int current_number = (current_digit == 0) ? 1 : 0; current_number < 10;
         current_number++) {
      recur(10 * current_digit + current_number);
    }
  }
};
