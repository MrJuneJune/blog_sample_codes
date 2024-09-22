// abcbdefg
//    |
#include <array>
#include <cstdint>
#include <iostream>
#include <string>

std::int32_t solution(std::string giberish, std::int32_t unique) {
  std::array<int32_t, 26> x = {-1, -1, -1, -1, -1, -1, -1, -1, -1,
                               -1, -1, -1, -1, -1, -1, -1, -1, -1,
                               -1, -1, -1, -1, -1, -1, -1, -1};
  std::int32_t ans = 1;
  for (std::int32_t i; i < giberish.size(); i++) {
    if (ans == unique) {
      return i;
    }
    std::int32_t pos = giberish[i] - 97;
    if (x[pos] < 0) {
      x[pos] = i;
      ans += 1;
    } else {
      for (int32_t j = 0; j < 26; j++) {
        if (x[j] < x[pos]) {
          x[j] = -1;
          ans -= 1;
        }
      }
    }
  }
  return -1;  // does not exists
}

int main() {
  std::cout << solution("jmaskjsdkjqmqwefrtygfjgih", 8) << "\n";
  return 0;
}
