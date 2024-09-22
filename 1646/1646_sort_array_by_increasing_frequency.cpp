#include <array>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
    vector<int> frequencySort(vector<int>& nums) {
        const int N = nums.size();
        unordered_map<int, int> frequencyMap;

        for (int n : nums)
            frequencyMap[n]++;
        vector<int> ans(nums.begin(), nums.end());

        sort(ans.begin(), ans.end(), [&](int a, int b) {
            if (frequencyMap[a] != frequencyMap[b])
                return frequencyMap[a] < frequencyMap[b];
            return a > b;
        });

        return ans;
    }
};

int main() {
    Solution solution;
    vector<int> nums = { 1, 1, 1, 2, 3, 3, 4 };
    vector<int> ans  = solution.frequencySort(nums);

    for (int num : ans) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}
