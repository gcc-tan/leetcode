//4Sum

/*
Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note: The solution set must not contain duplicate quadruplets.

For example, given array S = [1, 0, -1, 0, -2, 2], and target = 0.

A solution set is:
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]
*/


/*
和之前的15题类似。可以看15的题解
*/


class Solution 
{
public:
    vector<vector<int> > fourSum(vector<int>& nums, int target) 
	{
		int i, j, l, r, sum;
		vector<vector<int> > result;
		vector<int> tmp(4,0);
		sort(nums.begin(),nums.end());
		for(i = 0; i + 3 < nums.size(); ++i)
		{
			for(j = i + 1; j + 2< nums.size(); ++j)
			{
				l = j + 1,r = nums.size() - 1;
				while(l < r)
				{
					sum = nums[i] + nums[j] + nums[l] + nums[r];
					if(sum < target) ++l;
					else if(sum > target) --r;
					else
					{
						tmp[0] = nums[i], tmp[1] = nums[j], tmp[2] = nums[l], tmp[3] = nums[r];
						result.push_back(tmp);

						while(l < r && nums[l] == tmp[2]) ++l;
						while(l < r && nums[r] == tmp[3]) --r;
					}
				}
				while(j + 1 < nums.size() && nums[j] == nums[j+1] ) ++j;
			}
			while(i + 1 < nums.size() && nums[i] == nums[i+1]) ++i;
		}
		return result;
    }
};






//上面的我的代码是38ms AC，下面这个c++代码是16ms。可以看看快在哪里
/*
总结一下就是两点一个是估计是nums.size() 这个函数调用。还有一个是外层对可能情况的判断否定掉一部分内层的循环
*/
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> total;
        int n = nums.size();
        if(n<4)  return total;
        sort(nums.begin(),nums.end());
        for(int i=0;i<n-3;i++)
        {
            if(i>0&&nums[i]==nums[i-1]) continue;
            if(nums[i]+nums[i+1]+nums[i+2]+nums[i+3]>target) break;
            if(nums[i]+nums[n-3]+nums[n-2]+nums[n-1]<target) continue;
            for(int j=i+1;j<n-2;j++)
            {
                if(j>i+1&&nums[j]==nums[j-1]) continue;
                if(nums[i]+nums[j]+nums[j+1]+nums[j+2]>target) break;
                if(nums[i]+nums[j]+nums[n-2]+nums[n-1]<target) continue;
                int left=j+1,right=n-1;
                while(left<right){
                    int sum=nums[left]+nums[right]+nums[i]+nums[j];
                    if(sum<target) left++;
                    else if(sum>target) right--;
                    else{
                        total.push_back(vector<int>{nums[i],nums[j],nums[left],nums[right]});
                        do{left++;}while(nums[left]==nums[left-1]&&left<right);
                        do{right--;}while(nums[right]==nums[right+1]&&left<right);
                    }
                }
            }
        }
        return total;
    }
};
