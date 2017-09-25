//Reorder List

/*
Given a singly linked list L: L0->L1->…->Ln-1->Ln,
reorder it to: L0->Ln->L1->Ln-1->L2->Ln-2->…

You must do this in-place without altering the nodes' values.

For example,
Given {1,2,3,4}, reorder it to {1,4,2,3}.
*/


/*
重构链表结构，按照第一个最后一个，第二个倒数第二个的顺序连在一起
---------------------------------------------------------------------------------------------------------------------
一个很直接的想法是首先找到中间节点，然后将后半部分反转，然后两部分链表都从头开始遍历，将后面的每个节点挂在前面每个节点的后面
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
    void reorderList(ListNode* head) 
	{
		ListNode *mid, *iter, dummy(0), *pre, *next, *tail, *cur, *n1, *n2;
		if(!head || !head->next) return;
		//找到中间的节点
		for(mid = head, iter = head; iter;)
		{
			pre = mid;
			mid = mid->next;
			if(!iter->next) break;
			iter = iter->next->next;
		}
		pre->next = 0;//拆分成两个链表
		//节点数是偶数mid指向的是中间节点，是偶数mid指向的是后半部分的第一个节点
		dummy.next = mid, pre = &dummy, tail = pre->next, next = tail->next;//tail表示被反转链表最后一个节点，next表示当前被反转的节点，tail的值在迭代过程中不会改变
		//反转链表
		while(next)
		{
			tail->next = next->next;
			next->next = pre->next;
			pre->next = next;
			next = tail->next;
		}
		//按照前后一个的要求重构链表(其实就是合并两个链表)
		iter = head, cur = dummy.next;
		while(iter->next)
		{
			n1 = iter->next;
			n2 = cur->next;
			iter->next = cur;
			cur->next = n1;
			iter = n1, cur = n2;
		}
		iter->next = cur;
    }
};



