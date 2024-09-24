# Problem

```
179. Largest Number

Given a list of non-negative integers nums, arrange them such that they form the largest number and return it.

Since the result may be very large, so you need to return a string instead of an integer.

Example 1:

Input: nums = [10,2]
Output: "210"
Example 2:

Input: nums = [3,30,34,5,9]
Output: "9534330"
```

# Solutions

We want just sort by 9 to 1 rather lexigraphically. Problem letter with different length like

3, 30, we want 3 to be bigger but it won't be.

1. we compare one by one while rotating

```
3, 30
|  |


3, 30   # so just do 0 % 1 == 1 % 1
 |  |
```

2. Add each string together in two different order and see which one is the biggest.

```
330 vs 303 celver
```
