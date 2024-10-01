#include <map>
#include <set>
#include <string>

class AllOne {
 public:
  AllOne() : max_int(0), min_int(0) {}

  void inc(std::string key) {
    int curr_freq;
    if (strings.find(key) != strings.end()) {
      curr_freq = strings[key];

      // remove from current position in frequency map
      frequencies[curr_freq].erase(key);
      if (frequencies[curr_freq].empty()) {
        frequencies.erase(curr_freq);
        // Update min frequency if the current frequency was min_int
        if (min_int == curr_freq) {
          min_int = (frequencies.empty()) ? 0 : frequencies.begin()->first;
        }
      }

      // Increment frequency
      curr_freq += 1;
    } else {
      curr_freq = 1;  // New key with frequency 1
      if (min_int == 0 || min_int > 1) {
        min_int = 1;
      }
    }

    frequencies[curr_freq].insert(key);
    strings[key] = curr_freq;

    // Update max frequency
    if (curr_freq > max_int) {
      max_int = curr_freq;
    }
  }

  void dec(std::string key) {
    if (strings.find(key) == strings.end()) {
      return;  // Key does not exist, nothing to do
    }

    int curr_freq = strings[key];

    // Remove from current position in frequency map
    frequencies[curr_freq].erase(key);
    if (frequencies[curr_freq].empty()) {
      frequencies.erase(curr_freq);
      // Update max frequency if the current frequency was max_int
      if (max_int == curr_freq) {
        max_int = (frequencies.empty()) ? 0 : (--frequencies.end())->first;
      }
    }

    // Decrement frequency
    curr_freq -= 1;
    if (curr_freq == 0) {
      strings.erase(key);  // Remove key completely if frequency is zero
    } else {
      frequencies[curr_freq].insert(key);
      strings[key] = curr_freq;

      // Update min frequency
      if (min_int == 0 || curr_freq < min_int) {
        min_int = curr_freq;
      }
    }
  }

  std::string getMaxKey() {
    if (max_int == 0) {
      return "";  // No keys present
    }
    return *frequencies[max_int].begin();
  }

  std::string getMinKey() {
    if (min_int == 0) {
      return "";  // No keys present
    }
    return *frequencies[min_int].begin();
  }

 private:
  int max_int;                         // Track maximum frequency of any key
  int min_int;                         // Track minimum frequency of any key
  std::map<std::string, int> strings;  // Map to track frequencies of keys
  std::map<int, std::set<std::string>>
      frequencies;  // Map frequency -> set of keys
};
