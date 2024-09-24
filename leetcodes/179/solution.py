from collections import defaultdict


class Solution:
    def largestNumber(self, nums):
        new_nums = defaultdict(list)
        for num in nums:
            new_nums[str(num)[0]].append(num)

        for nlist in new_nums.values():
            nlist.sort(reverse=True)

        ans = ""
        for index in "987654321":
            ans += "".join([str(num) for num in new_nums[index]])

        return ans

print(Solution().largestNumber([10, 2]))

