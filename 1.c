#include<stdio.h>
#include<malloc.h>
#define SIZE 16
//two sum
int *twoSum(int *nums,int numsSize,int target)
{
	int *ret = malloc(2*sizeof(int));
	int i,j;
	for(i = 0;i < numsSize;++i)
	{
		for(j = i + 1;j < numsSize;++j)
		{
			if(nums[i] + nums[j] == target)
			{
				ret[0] = i;
				ret[1] = j;
				break;
			}
		}
	}
	return ret;
}
int main()
{
	int *p;
	int i,size,target;
	int a[SIZE];
	scanf("%d %d",&size,&target);
	for(i = 0;i < size;++i)
	{
		scanf("%d",&a[i]);
	}
	p = twoSum(a,size,target);
	printf("index:%d,%d\n",p[0],p[1]);
	free(p);
	return 0;
}
