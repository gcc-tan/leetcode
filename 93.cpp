//Restore IP Addresses

/*
Given a string containing only digits, restore it by returning all possible valid IP address combinations.

For example:
Given "25525511135",

return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)
*/


/*
给出一个字符串，全是数字，返回所有可能的IP地址。ip地址中有前导0不算是合法
-----------------------------------------------------------------------------------------------------------------
思路应该差不多，三层循环，穷举前三个点分十进制的长度
*/



class Solution 
{
private:
	bool legal(string &s)
	{
		if(s[0] == '0' && s.length() > 1) return false;//前导0
		if(stoi(s) > 255) return false;
		return true;
	}
public:
    vector<string> restoreIpAddresses(string s) 
	{
		int l1, l2, l3, l4, l = s.length();
		string s1, s2, s3, s4;
		vector<string> ans;
		for(l1 = 1; l1 < 4; ++l1)
		{
			for(l2 = 1; l2 < 4; ++l2)
			{
				for(l3 = 1; l3 < 4; ++l3)
				{
					l4 = l - (l1 + l2 + l3);
					if(l4 <= 0 || l4 > 3) continue;
					s1 = s.substr(0, l1);
					s2 = s.substr(l1, l2);
					s3 = s.substr(l1 + l2, l3);
					s4 = s.substr(l1 + l2 + l3, l4);
					if(legal(s1) && legal(s2) && legal(s3) && legal(s4))
						ans.push_back(s1 + "." + s2 + "." + s3 + "." + s4);
				}
			}
		}
		return ans;
    }
};
