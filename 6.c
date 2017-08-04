#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//ZigZag Conversation

/*

The string "PAYPALISHIRING" is written in a zigzag(蜿蜒的) pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"
Write the code that will take a string and make this conversion given a number of rows:

string convert(string text, int nRows);
convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".


*/




/*
感觉就是题目意思难以理解。题目是说给出一个之字形状的字符串，然后给定它的行数n(对之字来说每一笔就只有n个字符),然后让你按照行读出这个字符串

----------------------------------------------------------------------------------------------------------------------------------------------------------

这个只要找规律就行。字符串的规律可能不太明显，换成数字就明白了。(这个例子中输入就是"0123..18" n=4,输出是"0 6 12 18 1 5 7 11 13 17..."为了好看我加了空格)

0    6     12    18
1  5 7  11 13  17
2 4  8 10  14 16
3    9     15
*/



char* convert(char* s, int numRows) 
{
	int len = strlen(s),i,j,period = 2 * numRows - 2,pos = 0;//period周期
	char *ret = (char *)malloc(len + 1);
	if(period <= 0)
	{
		strcpy(ret,s);
		return ret;
	}
	for(i = 0; i < numRows; ++i)
	{
		if(i != 0 && i != numRows - 1)
		{
			for(j = i; j < len; j += period)
			{
				ret[pos++] = s[j];
				if(j + period - 2 * i < len)
					ret[pos++] = s[j+period-2*i];
			}
		}
		else
		{
			for(j = i; j < len; j += period)
				ret[pos++] = s[j];
		}
	}
	ret[pos] = '\0';
	return ret;
}

int main(int argc,char **argv)
{
	printf("%s\n",convert(argv[1],atoi(argv[2])));
	return 0;
}
