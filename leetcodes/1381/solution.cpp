#include <algorithm>
#include <cstdint>
#include <vector>

class CustomStack {
 public:
  CustomStack(int maxSize)
      : max_size(maxSize), stack(std::vector(max_size, -1)), current_size(-1) {}

  void push(int x) {
    if (stack[max_size - 1] != -1) {
      return;
    }
    current_size += 1;
    stack[current_size] = x;
  }

  int pop() {
    if (current_size == -1) {
      return -1;
    }
    int ans = stack[current_size];
    stack[current_size] = -1;
    current_size -= 1;
    return ans;
  }

  void increment(int k, int val) {
    for (int i = 0; i < std::min(max_size, k); i++) {
      if (stack[i] != -1)
        stack[i] += val;
    }
  }

 private:
  std::int32_t max_size;
  std::vector<int32_t> stack;
  std::int32_t current_size;
};
