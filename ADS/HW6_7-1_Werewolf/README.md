# 7-1 Werewolf (15 分)

Werewolf（狼人杀） is a game in which the players are partitioned into two parties: the werewolves and the human beings. Suppose that in a game,

- player #1 said: "Player #2 is a werewolf.";
- player #2 said: "Player #3 is a human.";
- player #3 said: "Player #4 is a werewolf.";
- player #4 said: "Player #5 is a human."; and
- player #5 said: "Player #4 is a human.".

Given that there were 2 werewolves among them, at least one but not all the werewolves were lying, and there were exactly 2 liers. Can you point out the werewolves?

Now you are asked to solve a harder vertion of this problem: given that there were N players, with M werewolves among them, at least one but not all the werewolves were lying, and there were exactly L liers. You are supposed to point out the werewolves.

### Input Specification:

Each input file contains one test case. For each case, the first line gives three positive integer N (5 ≤ N ≤ 100), M and L (2 ≤ M，L < N). Then N lines follow and the i-th line gives the statement of the i-th player (1 ≤ i ≤ N), which is represented by the index of the player with a positive sign for a human and a negative sign for a werewolf.

### Output Specification:

If a solution exists, print in a line in descending order the indices of the M werewolves. The numbers must be separated by exactly one space with no extra spaces at the beginning or the end of the line. If there are more than one solution, you must output the largest solution sequence -- that is, for two sequences A = { a[1], ..., a[M] } and B = { b[1], ..., b[M] }, if there exists 0 ≤ k < M such that a[i] = b[i] (i ≤ k) and a[k+1]>b[k+1], then A is said to be larger than B. In case there is no solution, simply print `No Solution`.

### Sample Input 1:

```in
5 2 2
-2
+3
-4
+5
+4
```

### Sample Output 1:

```out
4 1
```

### Sample Input 2:

```in
6 2 3
-2
+3
-4
+5
+4
-3
```

### Sample Output 2:

```out
6 4
```

### Sample Input 3:

```in
6 2 5
-2
+3
-4
+5
+4
+6
```

### Sample Output 3:

```out
No Solution
```

### 13分/15分

| 提交时间            | 状态     | 分数 | 题目   | 编译器    | 耗时 | 用户 |
| ------------------- | -------- | ---- | ------ | --------- | ---- | ---- |
| 2020/03/29 23:13:15 | 部分正确 | 13   | 编程题 | C++ (g++) | 4 ms | *    |

| 测试点 | 提示                  | 结果     | 分数 | 耗时 | 内存   |
| ------ | --------------------- | -------- | ---- | ---- | ------ |
| 0      | sample 1: unique      | 答案正确 | 4    | 4 ms | 384 KB |
| 1      | sample 2: not unique  | 答案正确 | 3    | 4 ms | 512 KB |
| 2      | no solution           | 答案正确 | 2    | 4 ms | 516 KB |
| 3      | no human lies         | 答案正确 | 2    | 4 ms | 384 KB |
| 4      | max size, random      | 运行超时 | 0    | --   | 0 KB   |
| 5      | one describes oneself | 答案正确 | 2    | 4 ms | 352 KB |

### AC.cpp

AC代码来自https://blog.csdn.net/baidu_37550206/article/details/79792287