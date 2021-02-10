# 7-1 Self-printable B+ Tree (10 分)

In this project, you are supposed to implement a B+ tree of order 3, with the following operations: initialize, insert (with splitting) and search. The B+ tree should be able to print out itself.

### Input Specification:

Each input file contains one test case. For each case, the first line contains a positive number N (≤104), the number of integer keys to be inserted. Then a line of the N positive integer keys follows. All the numbers in a line are separated by spaces.

### Output Specification:

For each test case, insert the keys into an initially empty B+ tree of order 3 according to the given order. Print in a line `Key X is duplicated` where `X` already exists when being inserted. After all the insertions, print out the B+ tree in a top-down lever-order format as shown by the samples.

### Sample Input 1:

```in
6
7 8 9 10 7 4
```

### Sample Output 1:

```out
Key 7 is duplicated
[9]
[4,7,8][9,10]
```

### Sample Input 2:

```
10
3 1 4 5 9 2 6 8 7 0
```

### Sample Output 2:

```
[6]
[2,4][8]
[0,1][2,3][4,5][6,7][8,9]
```

### Sample Input 3:

```
3
1 2 3
```

### Sample Output 3:

```
[1,2,3]
```