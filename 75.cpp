//Sort Colors

/*
Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

Note:
You are not suppose to use the library's sort function for this problem.

click to show follow up.

Follow up:
A rather straight forward solution is a two-pass algorithm using counting sort.
First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's, then 1's and followed by 2's.

Could you come up with an one-pass algorithm using only constant space?
*/


/*
给定一个数组中有三种数字0,1,2，然后要你进行升序排列
-------------------------------------------------------------------------------------------------------------------------------------
这是一个典型的计数排序的例子。计数排序的思想比较有意思，它不是基于比较的一种排序方法，使用的范围适合数的范围变化不大，时间复杂度是O(n)。计数排序的主要思想就是记录每个数字的出现次数，
通过这个信息重写被排序的数组。e.g. int a[5] = {0, 0, 2, 2, 1} 先记录0,1,2的出现次数，然后通过这个信息重写a

但是这个题目的要求1遍遍历，只使用常量的空间。假如没有前面的要求，这里的计数排序是一个很好的例子

*/

//先写一个计数排序的代码，这个算法很有意思虽然不符合题目的要求
class Solution 
{
public:
    void sortColors(vector<int>& nums) 
	{
		vector<int> times(3, 0);
		int i, j, n = nums.size();
		//统计每个数字的出现次数
		for(i = 0; i < n; ++i)
			++times[nums[i]];

		//重写原来的数组进行排序
		for(i = 0, j = 0; i < 3; ++i)
		{
			for(;times[i] > 0; --times[i])
				nums[j++] = i;
		}
    }
};

/*
这个是满足条件的代码

主要的思路是抓住只有三种数字这一点，利用两个变量记录当前为0的最后一个下标和当前为1的最后一个数字下标的位置，分别是idx0,idx1

扫描数组nums，
a) 如果nums[i] == 0，那么这个0肯定要放在idx0位置，idx0位置需要向后移动，这个时候挤占了idx1的数，idx1也要向后移动一个，nums[i]位置的值肯定就是2
b) 如果nums[i] == 1，那么肯定要放在idx1位置，idx1要向后移动，同样nums[i]位置的值为2
*/
class Solution 
{
public:
    void sortColors(vector<int>& nums) 
	{
		int idx0 = 0, idx1 = 0, i, n = nums.size();
		for(i = 0; i < n; ++i)
		{
			if(nums[i] == 0)
			{
				nums[i] = 2;//三者赋值的顺序不能改变，这个地方有点难懂
				nums[idx1++] = 1;
				nums[idx0++] = 0;
			}
			else if(nums[i] == 1)
			{
				nums[i] = 2;
				nums[idx1++] = 1;
			}
		}
    }
};


/*
上面这个代码可能不太好懂，有一个比较好懂的代码，就是利用red(0)指针指向0的最后一个位置，blue(2)指针指向2的最前位置
*/

class Solution 
{
public:
    void sortColors(vector<int>& nums) 
	{
		int i, red = 0, blue = nums.size() - 1;
		for(i = 0; i < blue; ++i)
		{
			if(nums[i] == 0)
				swap(nums[i], nums[red++]);//这个不需要调整是因为扫描过的i只可能是0,1
			else if(nums[i] == 2)
				swap(nums[i--], nums[blue--]);//这个i--是因为交换过来的i位置还有肯能不是1，需要进一步调整
		}
    }
};
