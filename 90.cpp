//SubSets II

/*
Given a collection of integers that might contain duplicates, nums, return all possible subsets.

Note: The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,2], a solution is:

[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]
*/


/*
和之前SubSets的不同之处是这个题目要求集合中的元素会有重复的
*/


class Solution 
{
public:
    vector<vector<int>> subsetsWithDup(vector<int> &nums) 
	{
		vector<vector<int>> ans;
		vector<int> tmp;
		sort(nums.begin(), nums.end());
		bt(ans, tmp, nums, 0);
		return ans;
    }
	void bt(vector<vector<int>> &ans, vector<int> &tmp, vector<int> &nums, int start)
	{
		int i;
		ans.push_back(tmp);
		for(i = start; i < nums.size(); ++i)//从start为是开始遍历，对于每个元素nums[i]选择或者不选这个元素，然后再进行递归调用
		{
			//相同的元素跳过，防止出想重复,e.g. nums = {1, 2, 2, 2} 在 i = 1时选择这个2,然后递归调用start = 2, i = 2时不能选择2,在进行递归，会有和之前重复的结果
			if(i != start && nums[i] == nums[i-1]) continue;
			tmp.push_back(nums[i]);
			bt(ans, tmp, nums, i + 1);
			tmp.pop_back();
		}
	}
};



/*
同样还有非递归的实现，道理也是和之前的非递归实现差不多，可以将重复的元素当成一个整体。先介绍一下公式如果给定
a = (a1, a2, ...,an)每个元素出现(k1, k2, ...,kn)次，那么集合a的所有子集的个数是(k1 + 1)*(k2 + 1)...*(kn + 1)

这个公式就是首先的那个将重复元素当成一个整体的想法，假设重复元素出现次数是kn次，那么可以将这个元素不加入，加入1个，加入2个，加入kn个到之前的集合中，所以一共是kn+1种情况
*/


class Solution 
{
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) 
	{
		vector<vector<int>> ans = {{}};//vector<vector<int>> ans(0, vector<int>());
		vector<int> tmp;
		int i, j, n, k, num_size = nums.size(), cnt;
		sort(nums.begin(), nums.end());
		for(i = 0; i < num_size;)
		{
			n = ans.size();
			//相同的nums[i]的个数为cnt
			for(k = i + 1, cnt = 1; k < num_size && nums[k] == nums[k-1]; ++k, ++cnt);
			for(j = 0; j < n; ++j)
			{
				tmp = ans[j];
				for(k = 0; k < cnt; ++k)
				{
					tmp.push_back(nums[i]);
					ans.push_back(tmp);
				}
			}
			i += cnt;
		}
		return ans;
    }
};
