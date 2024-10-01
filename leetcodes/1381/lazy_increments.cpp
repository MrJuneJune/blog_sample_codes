#include <vector>

using namespace std;

class CustomStack {
  vector<int> nums;
  vector<int> offset;
  int maxSize;
  int count = 0;
  int diff = 0;

 public:
  CustomStack(int maxSize) : maxSize(maxSize) {
    nums.resize(maxSize);
    offset.resize(maxSize);
  }

  void push(int x) {
    if (count == maxSize)
      return;

    if (count >= 1)
      offset[count - 1] += diff;
    diff = 0;

    nums[count] = x;
    offset[count] = 0;
    count++;
  }

  int pop() {
    if (count == 0)
      return -1;

    diff += offset[count - 1];
    int ret = nums[count - 1] + diff;
    count--;
    return ret;
  }

  void increment(int k, int val) {
    if (count == 0)
      return;

    offset[min(k - 1, count - 1)] += val;
  }
};

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */
