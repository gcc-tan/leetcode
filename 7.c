#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//string to integer(atoi)

/*
   Implement atoi to convert a string to an integer.
*/

/*
这个题目没什么好讲的，我首先的代码还会定位到最后一个数字位，然后倒着求和，结果发现没有这个必要。代码就瞬间简单了不少

真坑啊，题目里面什么都没说，也没有说数据发生溢出了会怎么样，居然要返回最大的int，和最小的int。。。我上哪知道去啊？
*/

#define INT_MAX 2147483647
#define INT_MIN -2147483648
int myAtoi(char* str) 
{
	int positive = 1,i,base = 0;
	long long ret = 0;
	for(i = 0; str[i] && str[i] == ' '; ++i)//去掉前导空格
		;
	if(str[i] == '-') //判断跳过符号位
	{
		positive = 0;
		++i;
	}
	else if(str[i] == '+')
		++i;


	while(str[i] >= '0' && str[i] <= '9')
	{
		ret = ret * 10 + (str[i++] - '0');//这是修改之后代码更简洁
		if(positive && ret >= INT_MAX) return INT_MAX;
		if(!positive && -ret <= INT_MIN) return INT_MIN;
	}

	return positive ? ret : -ret;
}

int main(int argc,char **argv)
{
	printf("%d\n",myAtoi(argv[1]));
	return 0;
}
