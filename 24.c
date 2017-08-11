//Swap Node in Pairs

/*
Given a linked list, swap every two adjacent nodes and return its head.

For example,
Given 1->2->3->4, you should return the list as 2->1->4->3.

Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed.
*/

/*
就是反转链表的相邻两个节点，这个要求还有点意思，只能使用常量的空间，不能够直接改变链表的值(想法很好)
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

//纪念一下，不知所言。这个代码提交打败了93.99%的c语言用户，0ms
struct ListNode* swapPairs(struct ListNode* head) 
{
	struct ListNode node, *pre, *first, *last;
	if(!head) return 0;
	node.next = head, pre = &node, first = head, last = head->next;
	while(last)
	{
		//拼接
		pre->next = last;
		first->next = last->next;
		last->next = first;

		//移动指针
		pre = first;
		first = first->next;
		if(first)
			last = first->next;
		else break;
	}

	return node.next;
}
