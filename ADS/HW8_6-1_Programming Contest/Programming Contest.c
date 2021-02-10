#include <stdio.h>

#define MAXN 10
#define MAXS 1000

int need_time(const int time[], const int score[], int happy_score, int n);

int main() {
  int n, i, happy_score;
  int time[MAXN], score[MAXN];
  scanf("%d %d", &n, &happy_score);
  for (i = 0; i < n; ++i)
      scanf("%d", &time[i]);
  for (i = 0; i < n; ++i)
      scanf("%d", &score[i]);
  printf("%d\n", need_time(time, score, happy_score, n));
  return 0;
}

/* Your function will be put here */

//n(1¡Ün¡ÜMAXN):the number of problems
//happy_score(1¡Ühappy_score¡ÜMAXS):the minimum score to be happy
//time[](1¡Ütime[i]¡Ü100):the time to solve problem i
//score[](1¡Üscore[i]¡Ü100):the score for solving problem i
int need_time(const int time[], const int score[], int happy_score, int n)
{
	int i, j;
	int sum = 0, sum_time = 0;
	
	for (i = 0; i < n; i++) {
		sum += score[i];
		sum_time += time[i];
	}
	if (sum < happy_score)
	   return -1;//solve all the problems but cannot reach happy_score
    
	//check the contrary
	//don't do those score<=happy_score, take most time 
    int v = sum - happy_score;
    int dp[v+1][n+1];//0,1 packsack 
	for (i = 0; i <= v; i++) { 
	    for(j = 0; j <= n; j++) 
		    dp[i][j] = 0;//initial
	} 
	
	for (i = 0; i <= v; i++) {
		for (j = 1; j <= n; j++) {
			if (score[j-1] <= i) {//enough space
			    int temp = time[j-1] + dp[i-score[j-1]][j-1];
			    if (dp[i][j-1] > temp)
			        dp[i][j] = dp[i][j-1];
			    else dp[i][j] = temp;//choose the max
			} else {//not enough
				dp[i][j] = dp[i][j-1];
			}
		}
	}
	if(sum_time == dp[v][n])
        return -1;
    else
        return sum_time - dp[v][n];
}
