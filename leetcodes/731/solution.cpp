#include <algorithm>
#include <array>
#include <vector>

class MyCalendarTwo {
 public:
  MyCalendarTwo() {}

  bool book(int start, int end) {
    std::vector<std::array<int, 2>> overlaps;

    for (const auto& schedule : _schedules) {
      if (start < schedule[1] && end > schedule[0]) {
        overlaps.push_back(
            {std::max(start, schedule[0]), std::min(end, schedule[1])});
      }
    }

    for (const auto& overlap : overlaps) {
      for (const auto& schedule : _overlaps) {
        if (overlap[0] < schedule[1] && overlap[1] > schedule[0]) {
          return false;
        }
      }
    }

    _schedules.push_back({start, end});
    for (const auto& overlap : overlaps) {
      _overlaps.push_back(overlap);
    }

    return true;
  }

 private:
  std::vector<std::array<int, 2>> _schedules;
  std::vector<std::array<int, 2>> _overlaps;
};
