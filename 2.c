//Add Two Numbers
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

/*

You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8

可能是英文不好，看了半天才懂，就是两个非负整数，每个数位用链表倒着存起来了，需要将两个数加起来，最后也用链表表示。eg:342 + 456 = 807

*/
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) 
{
	int carry = 0,tmp;
	struct ListNode *p1 = l1,*p2 = l2,*pre = 0,*cur,*head = 0;
	while(p1 || p2)//直接两个链表都为空才退出循环，首先写的是只要有一个为空，这样后面还要判断哪个为空，再进行同样的操作
	{
		tmp = carry;
		if(p1)
			tmp += p1->val;
		if(p2)
			tmp += p2->val;
		carry = tmp / 10;
		tmp = tmp % 10;

		cur = (struct ListNode *)malloc(sizeof(struct ListNode));
		cur->val = tmp;cur->next = 0;
		if(pre)
			pre->next = cur;
		else
			head = cur;
		pre = cur;

		if(p1)
			p1 = p1->next;
		if(p2)
			p2 = p2->next;
	}
	if(carry)//最高位的进位
	{
		cur = (struct ListNode*)malloc(sizeof(struct ListNode));
		cur->val = carry;cur->next = 0;
		pre->next = cur;
	}
	return head;
}


//最后附上人家的代码，虽然是同样的意思，别人的代码很简洁
public class Solution {
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        ListNode c1 = l1;
        ListNode c2 = l2;
        ListNode sentinel = new ListNode(0);
        ListNode d = sentinel;
        int sum = 0;
        while (c1 != null || c2 != null) {
            sum /= 10;
            if (c1 != null) {
                sum += c1.val;
                c1 = c1.next;
            }
            if (c2 != null) {
                sum += c2.val;
                c2 = c2.next;
            }
            d.next = new ListNode(sum % 10);
            d = d.next;
        }
        if (sum / 10 == 1)
            d.next = new ListNode(1);
        return sentinel.next;
    }
}
