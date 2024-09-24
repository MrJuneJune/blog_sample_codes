#include <algorithm>
#include <string>
#include <vector>

class Solution {
 public:
  std::string largestNumber(std::vector<int>& nums) {
    std::sort(nums.begin(), nums.end(), compare);

    // If values is 00000 then we just want 0.
    if (nums[0] == 0) {
      return "0";
    }

    std::string result;
    for (const auto& num : nums) {
      result += std::to_string(num);
    }

    return result;
  }

 private:
  static bool compare(int& i, int& j) {
    // 3, 30 comparison if you do it just 1 by 1, 3 will always be smaller. We can compare each char by char with rotating values.
    // But this way is much cleaner.
    std::string s1 = std::to_string(i) + std::to_string(j);
    std::string s2 = std::to_string(j) + std::to_string(i);

    return s1 > s2;
  }
};
