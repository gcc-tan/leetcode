//Median of Two Sorted Arrays

/*
There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

Example 1:
nums1 = [1, 3]
nums2 = [2]

The median is 2.0
Example 2:
nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5
*/


/*
   
题目的大概意思就是给出两个有序数组长度为m，n，然后在O(log (m +n))的时间复杂度下找出两个数组的中位数



----------------------------------------------------------------------------------------------------------------------------------------------------------

这里给出两个有序数组(数组是递增的)，A的长度是m，B数组的长度是n
 left_part               |        right_part
A[0], A[1], ..., A[i-1]  |  A[i], A[i+1], ..., A[m-1]
B[0], B[1], ..., B[j-1]  |  B[j], B[j+1], ..., B[n-1]

根据中位数的概念，中位数能够使得集合中比中位数大的数和比中位数小的数的个数相同。在上面的两个数组中A被i，B被j分成了左右两个部分。i的取值范围是[0,m]，
i=0时表示left_part为空,i=m表示右半部分为空。j表示的方法同理

如果我们可以保证
1) len(left_part) == len(right_part) 这里其实不是要求完全相等，因如果m+n是奇数的情况，左右两部分的个数肯定会相差1,这里的做法是奇数的情况就让len(left_part) = len(right_part) + 1,当然也可以反过来
2) max(left_part) <= min(right_part)

这样两个数组就被分成了两个相等的部分，并且一个部分的所有数要比另外一个部分的所有数要大。并且这两个部分的中位数就是median = (max(left_part) + min(right_part))/2。前面两个条件用数学表达式表示就是
1) i + j == m - i + n - j (or m - i + n - j + 1)
2) A[i-1] <= B[j]  and B[j-1] <= A[i]

所以我们的任务就化成了
Searching i in [0, m], to find an object `i` that:
    B[j-1] <= A[i] and A[i-1] <= B[j], ( where j = (m + n + 1)/2 - i 这里的+1设计的很巧妙，如果m+n是偶数，+1对j的为是是没有影响的，如果m+n是奇数，+1会让j向有移动一个，也就是我上面提到的left_part+1) 

上面的转换需要两个条件第一个A[i-1]和B[i-1]不存在的边界条件没有考虑，第二个m <= n，这个是为了 j = (m + n +1) / 2的j是一个非负值

为了加快查找i的速度，肯定使用二分查找的方式

<1> 设置 imin = 0,imax = m，然后在[imin,imax]的区间开始搜索
<2> 设置 i = (imin + imax) / 2，j = (m + n + 1)/2 - i
<3> 由于j的等式保证了len(left_part) = len(right_part)，所以只有下面的三种情况
    <a> B[j-1] <= A[i] and A[i-1] <= B[j] 这意味着找到了这样的i，停止搜索
	<b> B[j-1] > A[i] 这个时候应该增加i，因为增加i，j就减小，导致A[i] 增大，B[j-1]减小，更有可能满足<a>中的条件。因此 imin = i + 1，搜索的范围变为[i+1,imax]，再执行<2>
	<c> A[i-1] > B[j] 这个时候应该减小i，理由同上。因此 imax = i - 1，搜索范围变为[imin,i-1]，在执行<2>

最后当i找到的时候，中位数变为
max(A[i-1], B[j-1]) (when m + n 是奇数)
or (max(A[i-1], B[j-1]) + min(A[i], B[j]))/2 (when m + n 是偶数)


*/
