#include<stdio.h>
#define bool char
//Regular Expression Matching


/*

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") ? false
isMatch("aa","aa") ? true
isMatch("aaa","aa") ? false
isMatch("aa", "a*") ? true
isMatch("aa", ".*") ? true
isMatch("ab", ".*") ? true
isMatch("aab", "c*a*b") ? true

*/

/*
这是给定一个需要匹配的字符串和一个正则表达式，判断这个正则表达式能否和这个字符串匹配

-----------------------------------------------------------------------------------------------------------------------------------------------------------

ps:我发现了一个巨坑爹的地方，在terminal执行./a.out aaa a*看似正常的命令的时，argv[1] = "aaa" argv[2] = "a.out" terminal将*当成适配符，转换成可执行文件的名字了。
*/


bool empty_partern(char *p)
{
	int i;
	if(*p == 0)//空串
		return 1;
	for(i = 0; p[i]; i += 2)
	{
		if(p[i+1] != '*')
			return 0;
	}
	return 1;
}
bool isMatch(char* s, char* p) 
{
	char match = 0;
	int i;
	if(s[0] == '\0' && empty_partern(p))
		return 1;
	else if(s[0] == '\0' || p[0] == '\0')
		return 0;
	if(p[1] == '*')
	{
		if(s[0] == p[0] || p[0] == '.')
			match |= isMatch(s + 1,p);
		match |= isMatch(s,p + 2);
	}
	else
	{
		if(s[0] == p[0] || p[0] == '.')
			return isMatch(s + 1,p + 1);
		else
			return 0;
	}
	return match;
}

int main(int argc,char **argv)
{
	printf("%d\n",isMatch(argv[1],argv[2]));
	return 0;
}
