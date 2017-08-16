//Search in Rotated Sorted Array



/*

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.

*/


/*
给定一个数组a，这个数组本来是升序排列的，然后从某个位置开始，可能交换了一部分，数组的某些部分是有序的。要查找一个给定元素在数组中的位置，可以假设这个不重复，且在数组中出现

----------------------------------------------------------------------------------------------------------
leetcode的假设都是放屁，明明说好不可能的测试用例就出现了

这种题肯定就是二分查找的变种，正确的做法应该是先找到最小的元素的位置，也就是轴的位置，然后再根据要查找的数的大小，确定这个数究竟是在哪个部分

之前还做在有序数组中查找刚好大于或者小于给定数的例子，也是二分查找的应用
*/

int search(int* nums, int n, int target) 
{
	int i, j, mid, pos = -1;
	/*
	*二分的方法找最小的，根据中间的数进行判断时要与右边界进行比较，比右边界大，这个数肯定在中间数的右侧，比边界小，肯定是在左侧，但是这个左侧必须要包括中间的数
	*/
	for(i = 0, j = n - 1; i < j;)
	{
		mid = (i + j) / 2;
		if(nums[mid] > nums[j]) i = mid + 1;
		else if(nums[mid] < nums[j]) j = mid;
	}
	pos = i;

	if(pos == 0)//没有旋转
	{
		i = 0, j = n - 1;
	}
	else
	{
		if(target > nums[n-1])
			i = 0, j = pos - 1;
		else
			i = pos, j = n - 1;
	}
	//正常的二分查找
	while(i <= j)
	{
		mid = (i + j) / 2;
		if(nums[mid] < target) i = mid + 1;
		else if(nums[mid] > target) j = mid - 1;
		else return mid;
	}
	return -1;
}


/*
看了解答之后才知道这题有这么多的解答，不过说实话，这些解答都不是很好理解

1. 第一个方案是和上面的方法一样求出最小值的位置，在进行lo，hi的边界判断时做了化简，利用一个把mid当成偏移量


2.这个思想是每次取其中的一半，总有一半是肯定排好序的，剩下的可能是包含旋转的部分。根据查找的目标在排序好的部分还是在旋转部分进行否决
*/

//1的实现代码
class Solution {
public:
    int search(int A[], int n, int target) {
        int lo=0,hi=n-1;
        // find the index of the smallest value using binary search.
        // Loop will terminate since mid < hi, and lo or hi will shrink by at least 1.
        // Proof by contradiction that mid < hi: if mid==hi, then lo==hi and loop would have been terminated.
        while(lo<hi){
            int mid=(lo+hi)/2;
            if(A[mid]>A[hi]) lo=mid+1;
            else hi=mid;
        }
        // lo==hi is the index of the smallest value and also the number of places rotated.
        int rot=lo;
        lo=0;hi=n-1;
        // The usual binary search and accounting for rotation.
        while(lo<=hi){
            int mid=(lo+hi)/2;
			/*
			* 0,1,...rot-1, rot,...,n-1
			*                0      rot-1
			*/
            int realmid=(mid+rot)%n;
            if(A[realmid]==target)return realmid;
            if(A[realmid]<target)lo=mid+1;
            else hi=mid-1;
        }
        return -1;
    }
};









//2的实现代码
public class Solution {
public int search(int[] A, int target) {
    int lo = 0;
    int hi = A.length - 1;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (A[mid] == target) return mid;
        
        if (A[lo] <= A[mid]) {
            if (target >= A[lo] && target < A[mid]) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        } else {
            if (target > A[mid] && target <= A[hi]) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
    }
    return A[lo] == target ? lo : -1;
}


