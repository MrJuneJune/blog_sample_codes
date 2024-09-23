# 386. Lexicographical Numbers
# Medium
# Topics
# Companies
# Given an integer n, return all the numbers in the range [1, n] sorted in lexicographical order.
# 
# You must write an algorithm that runs in O(n) time and uses O(1) extra space.

class Solution():
    def __init__(self):
        pass
    def solve(self, number):
        ans = []
        for i in range(1, 10):
            if i < number:
                ans.append(i)
            currI = i
            while currI < number:
                print(currI)
                currI *= 10
                for i in range(10):
                    if currI + i > number:
                        break
                    ans.append(currI + i)
        return ans

x = Solution()
print(x.solve(13))

            
