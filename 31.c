//Next Permutation(排列)


/*
Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place, do not allocate extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1
*/



/*
题目的意思很明确就是生成一下个在词法顺序上比给定字符串要大的序列，其实这个就是非递归实现全排列的核心。有了这个函数，只要对给定字符串进行排序，然后比较每次生成的字符串是否和初始的一样，一样就是结束
循环，不同就输出字符串，通过这种方式就能输出所有的全排列

--------------------------------------------------------------------------------------------------------------------------------
思想很简单假设字符串(整数数组)s的索引是0~n-1,这个时候i = n - 1的初始值，向前找到最小的i使得s[i-1] > s[i],这样保证了i~n-1位置的数字是个反序，不能够通过调整i~n-1位置顺序来增大整个字符串了，但是为了
达到本次产生的是刚好大于当前的字符串，要求从i~n-1里面挑一个最小的j，并且能够满足s[j] > s[i-1]，这时候交换s[i-1]，s[j]，然后对i~n-1重新排序就行
*/



int cmp_asc(const void *a, const void *b)
{
	return *((int *)a) - *((int *)b);
}
//其实代码里面两个地方利用到了qsort都是可以优化的，并不是真正意义的排序，因为这个时候数组是反向有序的，可以写一个反转数组的代码进行优化，为了简单就直接用了排序函数
void nextPermutation(int* nums, int n) 
{
	int i, j;
	for(i = n - 1; i > 0; --i)
	{
		if(nums[i - 1] < nums[i]) 
			break;
	}

	if(i == 0)
	{
		qsort(nums, n, sizeof(int), cmp_asc);
		return;
	}

	for(j = n - 1; j >= i; --j)
	{
		if(nums[j] > nums[i-1])
		{
			//交换nums[j] nums[i-1]换个写法而已，比较无聊
			nums[j] += nums[i-1];
			nums[i-1] = nums[j] - nums[i-1];
			nums[j] -= nums[i-1];
			qsort(nums + i, n - i, sizeof(int), cmp_asc);
			break;
		}
	}
}

