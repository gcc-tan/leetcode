#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define bool char
bool isMatch(char *s, char *p)
{
	int m = strlen(s) + 1, n = strlen(p) + 1, i, j;
	char **dp = malloc(m * sizeof(char *)),is_match;
	dp[0] = malloc(m * n *sizeof(char));
	for(i = 1; i < m; ++i)
		dp[i] = dp[0] + i * n;

	//边界条件
	dp[0][0] = 1;
	for(i = 1; i < m; ++i)
		dp[i][0] = 0;
	for(j = 1; j < n; ++j)
		dp[0][j] = p[j-1] == '*' ? dp[0][j-2] : 0;

	for(i = 1; i < m; ++i)
	{
		for(j = 1; j < n; ++j)
		{
			if(p[j-1] != '*')
				dp[i][j] = dp[i-1][j-1] && (s[i-1] == p[j-1] || p[j-1] == '.');
			else
				dp[i][j] = dp[i][j-2] || (dp[i-1][j] && (s[i-1] == p[j-2] || p[j-2] == '.'));
		}
	}

	is_match = dp[m-1][n-1];
	free(dp[0]);
	free(dp);

	return is_match;
}
int main(int argc,char **argv)
{
	if(isMatch(argv[1],argv[2]))
		printf("1\n");
	else
		printf("0\n");

	return 0;
}
