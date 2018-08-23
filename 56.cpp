//Merge Intervals 

/*
Given a collection of intervals, merge all overlapping intervals.

For example,
Given [1,3],[2,6],[8,10],[15,18],
return [1,6],[8,10],[15,18].
*/


/*
题目的意思是给一堆区间，合并有重复的区间
-----------------------------------------------------------------------------------------------------------------------------------
这个题目好像也是在编程之美上面看过，忘了

首先先对区间按照左端点排序，然后从第i个区间开始判断，判断是否和i+1号区间重合，重合就合并这两个区间，继续判断i+2号区间。否则将这个区间加入结果集合中。重复上面过程，直到所有集合都合并完成
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
//9ms 最快的算法
class Solution 
{
public:
	bool operator()(const Interval &a, const Interval &b) const//这个是运算重载，重载的是(),函数最后的const表示这个函数不能修改类的成员函数
	{
		return a.start < b.start;
	}
    vector<Interval> merge(vector<Interval>& intervals) 
	{
		int i, n = intervals.size(), end;
		Interval cur;
		vector<Interval> ans;
		if(n <= 0) return ans;
		sort(intervals.begin(), intervals.end(), *this);

		cur = intervals[0];
		for(i = 1; i < n; ++i)
		{
			if(cur.end >= intervals[i].start)
			{
				cur.end = max(cur.end, intervals[i].end);
			}
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

//discuss中优秀的代码，写的不错
vector<Interval> merge(vector<Interval>& ins) 
{
    if (ins.empty()) return vector<Interval>{};
    vector<Interval> res;
    sort(ins.begin(), ins.end(), [](Interval a, Interval b){return a.start < b.start;});
    res.push_back(ins[0]);
    for (int i = 1; i < ins.size(); i++) 
	{
        if (res.back().end < ins[i].start) 
			res.push_back(ins[i]);
        else
            res.back().end = max(res.back().end, ins[i].end);
    }
    return res;
}

/*
这里讲讲c++的sort函数
sort函数是algorithm头文件里面的函数，这个函数有两中类型的参数
void sort( RandomIt first, RandomIt last, Compare comp);
void sort( RandomIt first, RandomIt last);
排序的范围是[first, last)的左开右闭区间

注意comp的返回值，虽然可以是int，但是其实只有两个有意义的值，true（非0）表示第一个参数比第二个参数小，要排在前面。false则是相反

前面两个参数就是迭代器的参数，后一个是比较对象，可以是一个全局的函数，也可以是一个对象，实现了操作符重载(我觉得操作符应该是括号)
e.g.
1. 全局函数，将cmp作为第三个参数传递
int cmp(const Type &a, const Type &b);
2. 通过重载需要比较对象的<操作符号，这个时候调用sort就不需要提供第三个参数
class Object
{
	int operator < (const Type &a) const
	{
	}
};
3. 函数对象，采用定义一个比较对象，将Compare对象传入第三个参数
struct Compare
{
	int operator()(const Type &a, const Type &b)
	{
	}
};
不管是对象还是函数，函数参数一般是bool cmp(const Type1 &a, const Type2 &b);
*/

