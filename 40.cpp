//Combination Sum II

/*
Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

Each number in C may only be used once in the combination.

Note:
All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
For example, given candidate set [10, 1, 2, 7, 6, 1, 5] and target 8, 
A solution set is: 
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]
*/


/*
和之前的Combination Sum一样，只是这里的每个数字只能用一次
------------------------------------------------------------------------------------------------------------------------
但是仔细一想还是有不一样的地方，就是之前的数字可以重复使用没有次数的限制，也就是说集合里面的数字有没有重复的都无所谓，但是这个地方不一样，每个数字只能使用一次，所以集合中数字会有重复的情况，
用之前的方法计算就会产生重复的结果

举个了例子
[10,1,2,7,6,1,5]
8
下面这个是答案
[[1,1,6],[1,2,5],[1,7],[2,6]]

若用之前的方法算出来的是
[[1,2,5],[1,7],[1,6,1],[2,6],[2,1,5],[7,1]]

做法基本也是一样的，只要先对候选的集合进行排序，然后如果发现相同的数跳过就行
*/




//我这个代码就是很直接，直接找相同的数的最远位置在哪，然后每次从相同的数中选一个，两个，...然后跳过这些相同的数进行递归
class Solution
{
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
	{
		vector<vector<int> > ans;
		vector<int> combination;

		sort(candidates.begin(), candidates.end());
		bt(ans, candidates, target, combination, 0);
		return ans;
    }
	void bt(vector<vector<int> > & ans, vector<int> &candidates, int target, vector<int> &combination, int begin)
	{
		int i, j, k, l, len;
		if(!target)
		{
			ans.push_back(combination);
			return;
		}
		len = candidates.size();
		for(i = begin; i < len && candidates[i] <= target; ++i)
		{
			for(j = i; j + 1 < len && candidates[j+1] == candidates[j]; ++j);
			for(k = 1; k <= j - i + 1; ++k)
			{
				l = k;
				while(l-- > 0)
					combination.push_back(candidates[i]);
				bt(ans, candidates, target - candidates[i] * k, combination, j + 1);

				l = k;
				while(l-- > 0)
					combination.pop_back();
			}

			i = j;
		}
	}
};









//这是leetcode上很简洁的c++代码，方法很上面的一样，但是真的很简洁很厉害
class Solution {
public:
    std::vector<std::vector<int> > combinationSum2(std::vector<int> &candidates, int target) {
        std::sort(candidates.begin(), candidates.end());
        std::vector<std::vector<int> > res;
        std::vector<int> combination;
        combinationSum2(candidates, target, res, combination, 0);
        return res;
    }
private:
    void combinationSum2(std::vector<int> &candidates, int target, std::vector<std::vector<int> > &res, std::vector<int> &combination, int begin) {
        if (!target) {
            res.push_back(combination);
            return;
        }
        for (int i = begin; i != candidates.size() && target >= candidates[i]; ++i)
            if (i == begin || candidates[i] != candidates[i - 1]) {
                combination.push_back(candidates[i]);
                combinationSum2(candidates, target - candidates[i], res, combination, i + 1);
                combination.pop_back();
            }
    }
};
