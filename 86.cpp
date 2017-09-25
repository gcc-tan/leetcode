//Partition List


/*
Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5.
*/


/*
给出一个阈值x，链表中节点值小于x在前面，大于等于x放在链表的后面，节点之间的相对关系不能改变
-----------------------------------------------------------------------------------------------------
很自然的想法就是分两种链表进行，小于x为第一种，大于等于的为第二种，遍历链表，判断当前节点的种类，按照类别挂载到对应链表的尾部。最后连接两个链表就行
*/


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution 
{
public:
    ListNode* partition(ListNode* head, int x) 
	{
		ListNode l1(0), l2(0), *p1, *p2, *cur = head;//p1, p2分别表示小于x节点集合和大于等于x的节点集合
		p1 = &l1, p2 = &l2;
		while(cur)
		{
			if(cur->val < x)
			{
				p1->next = cur;
				p1 = cur;
			}
			else
			{
				p2->next = cur;
				p2 = cur;
			}
			cur = cur->next;
		}
		p2->next = 0;//尾指针置0
		p1->next = l2.next;
		return l1.next;
    }
};
