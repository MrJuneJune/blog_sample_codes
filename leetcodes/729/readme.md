# Question

729. My Calendar I

You are implementing a program to use as your calendar. We can add a new event if adding the event will not cause a double booking.

A double booking happens when two events have some non-empty intersection (i.e., some moment is common to both events.).

The event can be represented as a pair of integers start and end that represents a booking on the half-open interval [start, end), the range of real numbers x such that start <= x < end.

Implement the MyCalendar class:

MyCalendar() Initializes the calendar object.
boolean book(int start, int end) Returns true if the event can be added to the calendar successfully without causing a double booking. Otherwise, return false and do not add the event to the calendar.

```
Example 1:

Input
["MyCalendar", "book", "book", "book"]
[[], [10, 20], [15, 25], [20, 30]]
Output
[null, true, false, true]

Explanation
MyCalendar myCalendar = new MyCalendar();
myCalendar.book(10, 20); // return True
myCalendar.book(15, 25); // return False, It can not be booked because time 15 is already booked by another event.
myCalendar.book(20, 30); // return True, The event can be booked, as the first event takes every time less than 20, but not including 20.
```

## Thinking about it

- Search one by one O(N)

- Can just do binary search and look at interested positions

## Notes

```
(x3,  y3)        (x3,  y3)
         [(x, y), (x2, y2)]

x3

for check for all:
  if (x <= (x3, y3) < y or x3 < x or y3 > y)  {
    return false;
  }

return True

But that is O(N) I think we can binary search a number of ranges that we are interested in...

        (9, 10)

(0, 5), 0, 3
       |

(0, 5) (5, 7) (8, 10)
                 ||

          2, 3
(-inf, inf)[5, 8]


,[15,25],

         [0, 5]
 (-inf, -inf)[[10,20]](+inf, inf), l = 0, r = 0

 [1,2,3,]
                        |
```
