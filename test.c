#include<stdio.h>
void show(char **m, int row, int col)
{
	int i, j;
	for(i = 0; i < row; ++i)
	{
		for(j = 0; j < col; ++j)
			printf("%d\n",m[i][j]);
		printf("\n");
	}
}
int main()
{
	char a[2][3] = {{'1', '2', '3'}, {'4', '5', '6'}};
	show((char **)a, 2, 3);
	return 0;
}
