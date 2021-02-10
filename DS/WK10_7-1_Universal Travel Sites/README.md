# 7-1 Universal Travel Sites (15 分)

After finishing her tour around the Earth, CYLL is now planning a universal travel sites development project. After a careful investigation, she has a list of capacities of all the satellite transportation stations in hand. To estimate a budget, she must know the minimum capacity that a planet station must have to guarantee that every space vessel can dock and download its passengers on arrival.

### Input Specification:

Each input file contains one test case. For each case, the first line contains the names of the source and the destination planets, and a positive integer `N` (≤500). Then `N` lines follow, each in the format: `source[i] destination[i] capacity[i]` where `source[i]` and `destination[i]` are the names of the satellites and the two involved planets, and `capacity[i]` > 0 is the maximum number of passengers that can be transported at one pass from `source[i]` to `destination[i]`. Each name is a string of 3 uppercase characters chosen from {A-Z}, e.g., ZJU.

Note that the satellite transportation stations have no accommodation facilities for the passengers. Therefore none of the passengers can stay. Such a station will not allow arrivals of space vessels that contain more than its own capacity. It is guaranteed that the list contains neither the routes to the source planet nor that from the destination planet.

### Output Specification:

For each test case, just print in one line the minimum capacity that a planet station must have to guarantee that every space vessel can dock and download its passengers on arrival.

### Sample Input:

```in
EAR MAR 11
EAR AAA 300
EAR BBB 400
AAA BBB 100
AAA CCC 400
AAA MAR 300
BBB DDD 400
AAA DDD 400
DDD AAA 100
CCC MAR 400
DDD CCC 200
DDD MAR 300
```

### Sample Output:

```out
700
```