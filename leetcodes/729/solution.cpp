/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */

/** O(n) 
#include <array>
#include <vector>

class MyCalendar {
 public:
  MyCalendar() {}

  bool book(int start, int end) {
    // O(N)
    for (auto schedule : _schedules) {
      if (!isOkay(start, end, schedule)) {
        return false;
      }
    }
    std::array<int, 2> new_array = {start, end};
    _schedules.push_back(new_array);
    return true;
  }

 private:
  std::vector<std::array<int, 2>> _schedules;

  bool isOkay(const int& start, const int& end,
              const std::array<int, 2>& schedule) {
    bool cond1 = start < schedule[0] && end >= schedule[1];
    bool cond2 = start >= schedule[1];

    return cond1 || cond2;
  }
};
**/

#include <array>
#include <limits>
#include <vector>

class MyCalendar {
 public:
  MyCalendar() {
    _schedules.push_back(std::array<int, 2>(
        {std::numeric_limits<int>::min(), std::numeric_limits<int>::min()}));
    _schedules.push_back(std::array<int, 2>(
        {std::numeric_limits<int>::max(), std::numeric_limits<int>::max()}));
  }

  bool book(int start, int end) {
    std::array<int, 2> new_array = {start, end};

    if (_schedules.size() == 2) {
      _schedules.insert(_schedules.begin() + 1, new_array);
      return true;
    }

    int pos_start = binary_search(start);

    if (isOkay(start, end, pos_start)) {
      _schedules.insert(_schedules.begin() + pos_start, new_array);
      return true;
    }
    return false;
  }

 private:
  std::vector<std::array<int, 2>> _schedules;

  int binary_search(int num) {
    int l = 0;
    int r = _schedules.size();

    while (l < r) {
      int mid = (l + r) / 2;
      // left side and need equal since we want to be right of same number as end is not included
      if (_schedules[mid][1] <= num) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return l;
  }

  bool isOkay(const int& start, const int& end, const int& pos_start) {
    // start -1 will be always the smaller value so need to compare to that.
    return start >= _schedules[pos_start - 1][1] &&
           end <= _schedules[pos_start][0];
  }
};
