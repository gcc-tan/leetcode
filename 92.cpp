//Reverse Linked List II

/*
Reverse a linked list from position m to n. Do it in-place and in one-pass.

For example:
Given 1->2->3->4->5->NULL, m = 2 and n = 4,

return 1->4->3->2->5->NULL.

Note:
Given m, n satisfy the following condition:
1 ≤ m ≤ n ≤ length of list.
*/

/*
给出两个位置[m, n]反转m~n的链表，链表的位置是从1开始计数的，要求不使用额外的空间和一遍扫描
---------------------------------------------------------------------------------------------------------
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
    ListNode* reverseBetween(ListNode* head, int m, int n) 
	{
		int i;
		ListNode dummy(0), *pre, *cur, *next, *tail;//pre需要反转第一个节点的前一个节点，cur遍历需要反转的节点，next表示需要反转节点的下一个节点，tail
		dummy.next = head;
		for(i = 1, pre = &dummy; i < m; ++i)//定位到第一个需要反转节点的前面
			pre = pre->next;
		cur = pre->next;
		tail = cur;
		next = cur->next;
		for(; i <= n; ++i)//反转节点
		{
			cur->next = pre->next;
			pre->next = cur;
			cur = next;
			if(!cur) break;
			next = next->next;
		}
		tail->next = cur;
		return dummy.next;
    }
};






/*
反转链表的代码，真的很简洁
*/
public ListNode reverseBetween(ListNode head, int m, int n) 
{
    if(head == null) return null;
    ListNode dummy = new ListNode(0); // create a dummy node to mark the head of this list
    dummy.next = head;
    ListNode pre = dummy; // make a pointer pre as a marker for the node before reversing
    for(int i = 0; i<m-1; i++) pre = pre.next;
    
    ListNode start = pre.next; // a pointer to the beginning of a sub-list that will be reversed
    ListNode then = start.next; // a pointer to a node that will be reversed
    
    // 1 - 2 -3 - 4 - 5 ; m=2; n =4 ---> pre = 1, start = 2, then = 3
    // dummy-> 1 -> 2 -> 3 -> 4 -> 5
    
	
    for(int i=0; i<n-m; i++)
    {
		/*
		*反转链表的核心，关键是固定一个start节点，这个节点是原链表的第一个节点(被反转链表的最后一个节点)，then表示的是当前需要被反转的节点
		*比我指针的节点向前插，尾节点单独赋值的算法要简单很多
		*/
        start.next = then.next;
        then.next = pre.next;
        pre.next = then;
        then = start.next;
    }
    
    // first reversing : dummy->1 - 3 - 2 - 4 - 5; pre = 1, start = 2, then = 4
    // second reversing: dummy->1 - 4 - 3 - 2 - 5; pre = 1, start = 2, then = 5 (finish)
    
    return dummy.next;
    
}
