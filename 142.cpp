//Linked List Cycle II

/*
Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

Note: Do not modify the linked list.

Follow up:
Can you solve it without using extra space?
*/



/*
判断一个链表是否有环，没有环返回空，有环返回环的开始地址，没有环返回空
-------------------------------------------------------------------------------------------
使用两个指针，fast和slow，fast走两步，slow走一步。如果有环肯定fast会和slow相遇，并且相遇的时慢指针刚好走完或者没有走完整个链表。确定环入口点的方法将此时的fast指针指向链表头，slow在相遇的位置，
两个指针每次移动一步，再次相遇时两个指针的位置就是环入口位置

因为有环的情况fast肯定比slow先或者一起入环(整个链表就是一个大环)，fast在slow前，每次追进一步的距离，如果slow都走完环了，fast对slow追击的距离肯定有一圈(两者间距小于一圈),故slow肯定没走完，或者
刚好走完

先定义几个变量，链表head到环入口为s，环入口到相遇点的距离为m，相遇时slow走过的距离为k，环的长度为r

很容易得到下面两个等式
1) 2k - k = nr (2k是快指针走的距离，nr表示快指针多走的圈数 n = 1, 2, 3...)

2) s = k - m

s = k - m = nr - m = (n - 1)r + r - m， 即 s = (n - 1)r + r - m

解释一下上面的等式，等式的右边让slow定位在入口m的距离，剩下的距离就是再走r - m的距离就回到环的入口，接着走(n - 1)r的距离还是在入口的地方。所以等式的右边是slow走的步数，左边是fast走的步数，
两者相等相遇，所有相等，fast走过了s的距离
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
    ListNode *detectCycle(ListNode *head) 
	{
		ListNode *fast = head, *slow = head;
		if(!head) return 0;
		do
		{
			slow = slow->next;
			if(!fast || !fast->next) return 0;
			fast = fast->next->next;
		}while(fast != slow);

		fast = head;
		while(fast != slow)
		{
			slow = slow->next;
			fast = fast->next;
		}
		return fast;
    }
};
