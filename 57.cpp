//Insert Interval

/*
Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times.

Example 1:
Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].

Example 2:
Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].

This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
*/


/*
给定一个按照区间的左端点排序的有序的区间集合，这些区间是不重复的，然后需要插入一个区间，然后继续保持之前的性质。
----------------------------------------------------------------------------------------------------------------------
*/



/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution 
{
public:
	//先通过二分查找找出需要插入区间位置，这个位置之前的区间直接放到结果集合里，剩下的与插入区间合并之后放入结果集合中
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) 
	{
		int i, j, mid, n = intervals.size();
		Interval cur;
		vector<Interval> ans;
		if(n == 0) 
		{
			ans.push_back(newInterval);
			return ans;
		}
		//二分查找刚好小于需要插入区间的位置
		for(i = 0, j = n - 1; i < j;)
		{
			mid = (i + j + 1) / 2;
			if(newInterval.start < intervals[mid].start) j = mid - 1;
			else i = mid;
		}
		
		for(i = 0; i < j; ++i)
			ans.push_back(intervals[i]);
		
		cur = newInterval;
		//主要是防止找不到刚好小于需要插入区间的位置
		if(cur.start > intervals[j].start)//这个地方为了代码简单，修改了传入参数的值
			swap(cur, intervals[j]);
		for(i = j; i < n; ++i)
		{
			if(cur.end >= intervals[i].start)
				cur.end = max(cur.end, intervals[i].end);
			else
			{
				ans.push_back(cur);
				cur = intervals[i];
			}
		}
		ans.push_back(cur);
		return ans;
    }
};




/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
/*
很简单直接的办法，代码写出来也很简单，将区间集合分三个部分
1.将新插入区间的左边所有区间直接加入到结果中，
2.将重合部分加入到结果中
3.将插入区间右边的部分加入到结果中
*/
class Solution {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) 
	{
		int i, n = intervals.size();
		vector<Interval> ans;
		if(n == 0)
		{
			ans.push_back(newInterval);
			return ans;
		}

		for(i = 0; i < n && intervals[i].end < newInterval.start; ++i)
			ans.push_back(intervals[i]);

		for(;i < n && newInterval.end >= intervals[i].start; ++i)
		{
			newInterval.start = min(newInterval.start, intervals[i].start);
			newInterval.end = max(newInterval.end, intervals[i].end);
		}
		ans.push_back(newInterval);

		for(; i < n; ++i)
			ans.push_back(intervals[i]);

		return ans;
    }
};
