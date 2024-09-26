import random

x = [random.randint(0, 1000) for _ in range(100)]
x.sort()

def binary_search(target):
    l = 0
    r = len(x)

    while (l < r):
        mid = (l + r)// 2
        
        if x[mid] < target:
            l = mid + 1
        else:
            r = mid
    return l

print(x)
import pdb; pdb.set_trace()

