//Multiply Strings


/*
Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2.

Note:

The length of both num1 and num2 is < 110.
Both num1 and num2 contains only digits 0-9.
Both num1 and num2 does not contain any leading zero.
You must not use any built-in BigInteger library or convert the inputs to integer directly.
*/




/*
一个简单的大数乘法
------------------------------------------------------------------------------------
感觉写了不下一万次，但是动起手来还是不怎么会写
*/




class Solution
{
public:
    string multiply(string num1, string num2)
	{
		int i, j, len1 = num1.size(), len2 = num2.size(), carry, tmp;
		string sum(len1 + len2, '0');

		for(i = len1 - 1; i >= 0; --i)
		{
			carry = 0;
			for(j = len2 - 1; j >= 0; --j)
			{
				tmp = (num1[i] - '0') * (num2[j] - '0') + (sum[i+j+1] - '0') + carry;//将上位的进位，这次乘法的数，以及当前的和都加起来
				carry = tmp / 10;
				sum[i+j+1] = tmp % 10 + '0';
			}
			if(carry)
				sum[i+j+1] = carry + '0';
		}

		for(i = 0; i < len1 + len2 - 1 && sum[i] == '0'; ++i); //去掉前导0，这里i不取等号为了防止结果是0,把所有的0都去掉了

		string ans(len1 + len2  - i, '0');
		for(j = 0; j < ans.size(); ++j, ++i)
            ans[j] = sum[i];
		return ans;
    }
};




//在看看别人写的c++代码，很简介明了


string multiply(string num1, string num2) {
    string sum(num1.size() + num2.size(), '0');//预先分配可能的空间
    
    for (int i = num1.size() - 1; 0 <= i; --i) {
        int carry = 0;
        for (int j = num2.size() - 1; 0 <= j; --j) {
            int tmp = (sum[i + j + 1] - '0') + (num1[i] - '0') * (num2[j] - '0') + carry;
            sum[i + j + 1] = tmp % 10 + '0';
            carry = tmp / 10;
        }
        sum[i] += carry;//这个进位处理很厉害，不需要判断0就相当于没加，而且不需要i+j+1，j+1肯定是0
    }
    
    size_t startpos = sum.find_first_not_of("0");//npos表示容器中不存在的位置，这里直接使用substr，没有像我一样又重复造车轮子
    if (string::npos != startpos) {
        return sum.substr(startpos);
    }
    return "0";
}
