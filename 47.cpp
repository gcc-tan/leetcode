//Permutations II

/*
Given a collection of numbers that might contain duplicates, return all possible unique permutations.

For example,
[1,1,2] have the following unique permutations:
[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]
*/



/*
前面一题是Permutations和这一题的条件相似，不过这个题目要求给定集合中可能含有重复的元素，所以先写这个，这个写完前面一个也就完成了
-------------------------------------------------------------------------------------------------------------------------------------------------------
用的方法就是之前有一个题目叫Next Permutation，首先对要全排列的数据进行词法上的排序，然后从后向前找找到i保证i~n在词法上是倒序的，此时通过调整i~n的位置已经不能生成下一个不重复的排列了，
需要将i-1位置与i~n中刚好大于i-1位置的两个量进行交换,然后再对i~n进行逆序排列
*/




class Solution
{
public:
    vector<vector<int> > permuteUnique(vector<int>& nums)
	{
		int i, j, len = nums.size(), l, r, tmp;
		vector<vector<int> > ans;
		sort(nums.begin(), nums.end());

		ans.push_back(nums);
		while(1)
		{
			for(i = len - 1; i > 0 && nums[i-1] >= nums[i]; --i);//nums[i-1] >= nums[i]带上等号为了防止相同的数重复
			if(!i) break;
			for(j = len - 1; j >= i && nums[j] <= nums[i-1]; --j);//这里就不需要判断能否找到了，肯定能找到，因为如果其他的都不是nums[i]肯定是刚好比nums[i-1]大且不相等的

			//swap(nums[i-1], nums[j]);
			tmp = nums[i-1];
			nums[i-1] = nums[j];
			nums[j] = tmp;
			//反转i~n，为什么能直接反转因为根据nums[i-1] < nums[j] 那么nums[i-1]肯定是小于nums[j+1]并且nums[i-1]已经和j-1比较过了
			for(l = i, r = len - 1; l < r; ++l, --r)
			{
				//swap(nums[l], nums[r]);
				tmp = nums[l];
				nums[l] = nums[r];
				nums[r] = tmp;
			}
			ans.push_back(nums);
		}
		return ans;
    }
};
