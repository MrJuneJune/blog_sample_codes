// Copyright
//
#include <set>
#include <string>
#include <vector>

class Solution {
 public:
  int countConsistentStrings(std::string allowed,
                             std::vector<std::string>& words) {
    std::set<std::string> allowed = std::set(allowed.begin(), allowed.end());
  }

 private:
  std::string allowed;

  bool checkIfExits(const std::string& word) {}
};
