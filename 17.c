#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Letter Combinations of a Phone Number

/*
Given a digit string, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below.

Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

*/

/*
这个题目在编程之美上好像是看过的。题目的意思就是数字键盘上的数字是对应好几个字母，例如2对应"abc"，3对应"def"。现在输入一串数字，要求输出对应的字母的所有可能。

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

这个题目有很多的做法。

1. 建立一个与输入数字个数相同的数组。也就是每个数字有个对应的计数器，计数器的初始值0。遍历所有数字，每个数字上计数器所代表的字母组合就是这次循环产生的一个可能的结果。就像进位一样更新计数器的值。
最后直到计数器的最高位溢出。
举个例子，计数器的第一位是0,那么就直接+1。这个计数器的值大于等于计数器对应数字的字母的长度，那么这个计数器清零，用同样的方法更新下一个计数器。

2. 采用bfs的方案，使用一个FIFO的队列。举个例子，加入输入是"23"，那么可以得到一棵这样的树
        root
	  /    |   \
	 a     b    c
	/|\   /|\   /|\
   d e f d e f d e f

代码很简单，直接看java代码比较清楚
public List<String> letterCombinations(String digits) {
    LinkedList<String> ans = new LinkedList<String>();
    String[] mapping = new String[] {"0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    ans.add("");
    for(int i =0; i<digits.length();i++){
        int x = Character.getNumericValue(digits.charAt(i));//获取当前的数字
        while(ans.peek().length()==i){//利用长度判断上层的所有节点是否已经出队
            String t = ans.remove();
            for(char s : mapping[x].toCharArray())
                ans.add(t+s);出队节点的字符串加上层的字符构成当前层的字符串
        }
    }
    return ans;
}
*/



/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
char map[10][5] = 
{
	{""},
	{""},
	{"abc"},
	{"def"},
	{"ghi"},
	{"jkl"},
	{"mno"},
	{"pqrs"},
	{"tuv"},
	{"wxyz"},
};//定义一个数字到字母的映射
char entry_len[10] = {0, 0, 3, 3, 3, 3, 3, 4, 3, 4};//每个数字对应字母的个数
char** letterCombinations(char* digits, int* returnSize) 
{
	int i, len , pos, *p, *dig = malloc(strlen(digits) * sizeof(int));
	char **ret = 0;

	//预处理，去掉digits里面的1,并且转换成int
	for(i = 0, len = 0; digits[i]; ++i)
	{
		if(digits[i] == '1') continue;
		dig[len++] = digits[i] - '0';
	}
	if(len == 0)//leetcode非要返回一个长度为0的非空指针
	{
		*returnSize = 0;
		return malloc(sizeof(char *));
	}
	//初始化操作
	p = malloc(len * sizeof(int));
	for(i = 0, *returnSize = 1; i < len; ++i)
		*returnSize *= entry_len[dig[i]];
	ret = malloc(*returnSize * sizeof(char *));
	for(i = 0; i < len; ++i)
		p[i] = 0;

	for(pos = 0; p[0] < entry_len[dig[0]];)
	{
		ret[pos] = malloc(len * sizeof(char) + 1);
		for(i = 0; i < len; ++i)
			ret[pos][i] = map[dig[i]][p[i]];
		ret[pos++][i] = '\0';

		for(i = len - 1; i > 0; --i)
		{
			if(++p[i] < entry_len[dig[i]])
				break;
			else
				p[i] = 0;
		}
		if(i == 0) ++p[0];
	}

	free(p);

	return ret;
}


int main(int argc, char **argv)
{
	int size, i;
	char **p = letterCombinations(argv[1], &size);

	for(i = 0; i < size; ++i)
		printf("%s\n",p[i]);
	return 0;
}
















