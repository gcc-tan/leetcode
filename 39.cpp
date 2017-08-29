//Combination Sum


/*
Given a set of candidate numbers (C) (without duplicates) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

The same repeated number may be chosen from C unlimited number of times.

Note:
All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
For example, given candidate set [2, 3, 6, 7] and target 7, 
A solution set is: 
[
  [7],
  [2, 2, 3]
]
*/




/*
给定一个数集C和一个目标数字t，在C中找出所有的组合使得这些数字的和是目标数字t. 这些数字都可以重复使用
--------------------------------------------------------------------------------------------------------------------------------------
搞错了，之前我以为是背包问题，但是不是背包问题和背包问题不太一样，背包问题是有容量和价值的，如果是背包问题可以看背包9讲。

递归的方法，具体看代码
*/







class Solution 
{
public:
    vector<vector<int>> combinationSum(vector<int>& ca, int target) 
	{
		vector<vector<int> > v;
		vector<int> combination;
		recursive(ca, target, v, combination, 0);
		return v;
    }
	void recursive(vector<int> &candidates, int target, vector<vector<int> > &v, vector<int> &combination, int begin)
	{
		int i;
		if(!target)
		{
			v.push_back(combination);
			return;
		}
		for(i = begin; i < candidates.size(); ++i)
		{
			if(candidates[i] > target) continue;
			combination.push_back(candidates[i]);
			recursive(candidates, target - candidates[i], v, combination, i);
			combination.pop_back();
		}
	}
};
