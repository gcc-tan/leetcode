//Sort List

/*
Sort a linked list in O(nlogn) time using constant space complexity.
*/




/*
使用常量的空间，O(nlogn)的时间复杂度排序一个链表
------------------------------------------------------------------------------------------------------------------------------
使用归并排序的思想---对集合进行划分，划分成小的集合之后再进行排序，接着对这些小的集合进行合并操作
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
private:
	//合并两个有序链表
	ListNode *merge(ListNode *h1, ListNode *h2)
	{
		ListNode *iter, dummy(0), *tmp;
		iter = &dummy;
		while(h1 && h2)
		{
			if(h1->val < h2->val)
			{
				iter->next = h1;
				h1 = h1->next;
			}
			else 
			{
				iter->next = h2;
				h2 = h2->next;
			}
			iter = iter->next;
		}
		iter->next = h1 != 0 ? h1 : h2;
		return dummy.next;
	}
public:
    ListNode* sortList(ListNode* head) 
	{
		ListNode *iter = head, *mid = head, *pre, *h1, *h2;
		//找到链表的中点对输入的链表进行划分
		if(!head || !head->next) return head;
		while(iter && iter->next)
		{
			pre = mid;
			mid = mid->next;
			iter = iter->next->next;
		}
		pre->next = 0;//分成两个链表

		h1 = sortList(head);
		h2 = sortList(mid);

		return merge(h1, h2);
    }
};





