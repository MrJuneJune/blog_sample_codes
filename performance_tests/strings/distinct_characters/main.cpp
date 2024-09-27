/**
 * distinct characters
 *
 * 1. Naive, create window and see if there are any values that are same.  O(u*u*n), O(1)
 * 2. Create an fixed array with alphabets, and do above logic. O(26*n), O(26)
 * 3. Doing the same as 3, but instead of using array. Use bits and use bit operations. O(n), O(32 bits?)
 *
 **/
#include <array>
#include <bitset>
#include <chrono>
#include <cstdint>
#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <unordered_set>

std::string generate_random_string(int length) {
  const std::string characters = "abcdefghijklmnopqrstuvwxyz";

  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<> distribution(0, characters.size() - 1);

  std::string random_string;
  random_string.reserve(length);
  for (int i = 0; i < length; ++i) {
    random_string += characters[distribution(generator)];
  }

  return random_string;
}

std::int32_t solution1(const std::string& giberish,
                       const std::int32_t& unique) {
  for (int i = 0; i < giberish.size(); i++) {  // O(n)
    std::unordered_set<char16_t> window;
    for (int j = i; j < unique + i; j++) {  // O(u)
      window.insert(giberish[j]);           // O(u)
    }

    if (window.size() == unique) {
      return i;
    }
  }
  return -1;
}

std::int32_t solution2(const std::string& giberish,
                       const std::int32_t& unique) {
  // Array to keep track of the last seen position of each character
  std::array<int32_t, 26> x = {-1, -1, -1, -1, -1, -1, -1, -1, -1,
                               -1, -1, -1, -1, -1, -1, -1, -1, -1,
                               -1, -1, -1, -1, -1, -1, -1, -1};
  std::int32_t ans = 0;
  for (std::int32_t i = 0; i < giberish.size(); i++) {
    if (ans == unique) {
      return i;
    }
    std::int32_t pos = giberish[i] - 'a';
    if (x[pos] < 0) {
      // position in array
      x[pos] = i;
      ans += 1;
    } else {
      for (std::int32_t j = 0; j < 26; j++) {
        // take out characters that is behind duplicate letter
        if (x[j] < x[pos] && x[j] != -1) {
          x[j] = -1;
          ans -= 1;
        }
      }
      x[pos] = i;
    }
    if (ans == unique) {
      return i - unique + 1;  // need to beginning of it
    }
  }
  return -1;
}

int solution3(const std::string& input, const std::int32_t& unique) {
  uint32_t filter = 0;

  for (size_t i = 0; i < input.size(); ++i) {
    filter ^= 1 << (input[i] % 32);

    if (std::bitset<32>(filter).count() == unique) {
      return i - unique + 1;
    }

    if (i >= unique - 1) {
      // remove first chracters since we will add one
      filter ^= 1 << (input[i - unique + 1] % 32);
    }
  }

  return -1;
}

using SolutionFunc = std::function<int(std::string, int)>;

void measure_solution_time(const std::string& input, int unique,
                           SolutionFunc solution,
                           const std::string& solution_name) {
  auto start = std::chrono::high_resolution_clock::now();

  int result = solution(input, unique);

  auto end = std::chrono::high_resolution_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);

  std::cout << solution_name << " Result: " << result
            << " | Time: " << duration.count() << " microseconds\n";
}

int main() {
  std::string test = generate_random_string(100000);
  constexpr int unique = 18;
  measure_solution_time(test, unique, solution1, "Using Sets");
  measure_solution_time(test, unique, solution2, "Using Array");
  measure_solution_time(test, unique, solution3, "Using Bits");
  return 0;
}
