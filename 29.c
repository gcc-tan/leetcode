#include<stdio.h>
#include<string.h>
//Divide Two Integers

/*
Divide two integers without using multiplication, division and mod operator.

If it is overflow, return MAX_INT.
*/


/*
题目很简单，就是不准用乘法，除法，取余而实现除法运算

--------------------------------------------------------------------------------------------------------------------------------

其实这个题目是有来源，学过计算机组成原理的同学都知道，cpu的核心就是各种门电路(应该是与非门)，所以计算机内部肯定是不认识加减乘除四种运算的，这几种基本的运算都是通过逻辑的位运算和移位实现的
那在这里就实现加减乘除四中运算

下面这些算法都是网上一篇博客里面看到的，如果有时间看机组，可以再来优化优化

*/

#define IS_POS(a) (((a) & 0xffffffff) && !((a) & 0x80000000)) //是否是正数
#define NEG_COMPLEMENT(a) (~(a) + 1) //负数的补码
#define IS_NEG(a) ((a) & 0x80000000) //是否是负数
#define IS_ZERO(a) (!((a) & 0xffffffff)) //是否是0

/*
加法，加法算法的过程是a+b
1. a+b 将每个数位加在一起不产生进位 ----异或
2. a+b 算出只产生进位的结果 ---- 在二进制中只有1+1才会产生进位，所以通过与操作，然后向左移位
3. 将1,2中的结果加在一起(这是递归调用,只有没有进位时候才会结束这个递归的过程)
举个例子5 + 17 = 101 + 10001
1. 10100
2. 10
3 10110
*/

int add(int a, int b)
{
	int ans;
	while(b)
	{
		ans = a ^ b;
		b = (a & b) << 1;
		a = ans;
	}
	return a;
}
/*
减法，将减数取补码，然后再加上被减数
*/
int sub(int a, int b)
{
	return add(a, NEG_COMPLEMENT(b));
}
/*
乘法，这个思想其实很直接，就是模拟正常的手算的过程来做的，机组上好像有算法，忘了。

例如101 * 11 用低位的1乘得101,用高位的1乘也得101,但是要错位那就是1010。两者相加就得最后的结果
*/

//正数的乘法
int pos_mul(int a, int b)
{
	int ans = 0;
	while(b)
	{
		if(b & 1)
			ans = add(ans, a);
		a <<= 1;
		b >>= 1;
	}
	return ans;
}
int mul(int a, int b)
{
	if(IS_ZERO(a) || IS_ZERO(b))
		return 0;

	if(IS_POS(a) && IS_POS(b))
		return pos_mul(a, b);
	if(a < 0)
	{
		if(b < 0)
		{
			return pos_mul(NEG_COMPLEMENT(a), NEG_COMPLEMENT(b));
		}
		return NEG_COMPLEMENT(pos_mul(NEG_COMPLEMENT(a), b));
	}

	return NEG_COMPLEMENT(pos_mul(a, NEG_COMPLEMENT(b)));
}

/*
除法
1. 实现的第一种方法是用被除数减去除数，一直到所得的余数小于除数或者等于0为止。每次减的过程商都加1,最后就可以得出商来了。
2. 上面的办法很蠢，就是被除数很大，除数很小时效率很低。所以可以用指数快速逼近。在二进制中，肯定是任何数都能写成二进制的和，所以被除数a与除数b之间肯定有这样的关系a = (2^31 + 2^30 ...+2^0)*b + c
c是余数，括号里面的2^31那项可能存在也可能不存在。首先从2^31倍开始减，如果能减去那么商就加上2^31。后面的项同理

有组测试用例很关键
-2147483648
-1

-2147483648
1
这组测试产生的结果能让int溢出
*/
//为了方便，直接用加减号，也可以使用上面的函数代替
#define INT_MAX (~(1 << 31))
#define INT_MIN (1 << 31)
#define ABS(a) ((a) > 0 ? (a) : -(a))
int divide(int a,int b)
{
	long long i, ans = 0, dividend, divisor;//ans商
	dividend = a, divisor = b;
	dividend = ABS(dividend);
	divisor = ABS(divisor);
	if(b == 0 || (a == INT_MIN && b == -1)) 
		return INT_MAX;
	for(i = 31; i >= 0; --i)
	{
		//这里选择被除数向右移位比较，也可以除数向左移位，但是这样有数据溢出的可能，b为负数从而满足条件
		if((dividend >> i) >= divisor)
		{
			ans += 1L << i;
			dividend -= divisor << i;
		}
	}
	if((a ^ b) < 0)
		return -ans;
	return ans;
}



int main(int argc, char **argv)
{
	printf("%d\n", divide(atoi(argv[1]), atoi(argv[2])));
	return 0;
}

