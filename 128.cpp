//Longest Consecutive Sequence

/*
Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity.
*/


/*
一个无序数组中找到最长的连续的数字长度，时间复杂度是O(n)
-----------------------------------------------------------------------------
1. 关键的思想里将连续的数字进行分组，求出每组的长度就行。但是关键是怎样保证不会重复遍历一组中同一个元素呢(这样才能保证O(n)的时间复杂度)?这个判断很巧妙，既然是连续的数字，
只需要判断当前这个数字减1是否在数组中,这样就能找到分组的第一个元素x，依次检查x+1,x+2...是在数组中。利用一个hashmap，将数组添加到hashmap中，时间复杂度是O(n)，这样就能O(1)的时间复杂度进行查找了。
*/


//方法1
class Solution 
{
public:
    int longestConsecutive(vector<int>& nums) 
	{
		unordered_map<int,bool> map;
		int i, x, n = nums.size(), max_len = 0;
		for(i = 0; i < n; ++i)
			map[nums[i]] = true;

		for(i = 0; i < n; ++i)
		{
			if(map.count(nums[i] - 1)) continue;
			for(x = nums[i] + 1; map.count(x); ++x);
			max_len = max(max_len, x - nums[i]);
		}
		return max_len;
    }
};


/*
这是discuss里面另一种思路的实现，我感觉没有上面一个方法直观
We will use HashMap. The key thing is to keep track of the sequence length and store that in the boundary points of the sequence. For example, as a result, for sequence {1, 2, 3, 4, 5}, map.get(1) and map.get(5) should both return 5.(hashmap存的是该点作为连续序列边界点的整个序列的长度,例如据的例子1, 5都是1,2,3,4,5的边界，序列长度为5，2应该是2)

Whenever a new element n is inserted into the map, do two things:

1. See if n - 1 and n + 1 exist in the map, and if so, it means there is an existing sequence next to n. Variables left and right will be the length of those two sequences, while 0 means there is no sequence and n will be the boundary point later. Store (left + right + 1) as the associated value to key n into the map.
2. Use left and right to locate the other end of the sequences to the left and right of n respectively, and replace the value with the new length.
Everything inside the for loop is O(1) so the total time is O(n). Please comment if you see something wrong. Thanks.
*/




//java代码
public int longestConsecutive(int[] num) {
    int res = 0;
    HashMap<Integer, Integer> map = new HashMap<Integer, Integer>();
    for (int n : num) {
        if (!map.containsKey(n)) {
            int left = (map.containsKey(n - 1)) ? map.get(n - 1) : 0;
            int right = (map.containsKey(n + 1)) ? map.get(n + 1) : 0;
            // sum: length of the sequence n is in
            int sum = left + right + 1;
            map.put(n, sum);
            
            // keep track of the max length 
            res = Math.max(res, sum);
            
            // extend the length to the boundary(s)
            // of the sequence
            // will do nothing if n has no neighbors
            map.put(n - left, sum);
            map.put(n + right, sum);
        }
        else {
            // duplicates
            continue;
        }
    }
    return res;
}
