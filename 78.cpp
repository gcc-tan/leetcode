//SubSets

/*
Given a set of distinct integers, nums, return all possible subsets.

Note: The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,3], a solution is:

[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
*/

/*
给定一个集合，求出这个集合的所有子集
*/

/*
其实完全可以根据下面这个代码的思想写一个非递归的代码。先考虑一下这个集合{1, 2, 3}的子集。首先{}肯定是任何集合的子集，然后考虑1,可以将1添加到前面所有的集合中，或者是不添加得到两个集合{},{1}
处理2的方式也是类似，加上与不加得到{},{1},{2},{1,2},3的方式同理就行。代码很简单，这里就略过了
*/
class Solution 
{
public:
    vector<vector<int>> subsets(vector<int>& nums) 
	{
		vector<vector<int>> ans; 
		if(nums.size() == 0) return ans;
		int back = nums.back(), n, i;

		nums.pop_back();
		ans = subsets(nums);//不包括最后一个元素的子集
		n = ans.size();
		for(i = 0; i < n; ++i)
		{
			vector<int> tmp = ans[i];
			tmp.push_back(back);
			ans.push_back(tmp);//将包括最后一个元素的子集，加入到结果集合中
		}
		nums.push_back(back);
		return ans;
    }
};


/*
这个关于代码其实很有思想，完全就是一个数学的实现方法。是首先通过公式计算n个不重复元素的子集的个数为2^n，然后穷举[0, 2^n-1]这些数，每个数的每个比特位对应n个元素中每个元素是否出现
*/
class Solution {
public:
    vector<vector<int> > subsets(vector<int> &S) {
        sort (S.begin(), S.end());
        int elem_num = S.size();
        int subset_num = pow (2, elem_num);
        vector<vector<int> > subset_set (subset_num, vector<int>());
        for (int i = 0; i < elem_num; i++)
            for (int j = 0; j < subset_num; j++)
                if ((j >> i) & 1)
                    subset_set[j].push_back (S[i]);
        return subset_set;
    }
};


/*
下面的这个java代码其实是一个通用的结构，对应这种数组i号元素选与不选的问题，也有借鉴的地方
*/

public List<List<Integer>> subsets(int[] nums) {
    List<List<Integer>> list = new ArrayList<>();
    Arrays.sort(nums);
    backtrack(list, new ArrayList<>(), nums, 0);
    return list;
}

private void backtrack(List<List<Integer>> list , List<Integer> tempList, int [] nums, int start){//list表示结果集合，tempList表示当前可能的子集
    list.add(new ArrayList<>(tempList));
    for(int i = start; i < nums.length; i++){
        tempList.add(nums[i]);
        backtrack(list, tempList, nums, i + 1);
        tempList.remove(tempList.size() - 1);
    }
}
