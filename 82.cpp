//Remove Duplicates from Sorted List II

/*
Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3.
*/


/*
删除有序链表中重复的元素
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
    ListNode* deleteDuplicates(ListNode* head) 
	{
		ListNode *pre, *tail, *cur, dummy(0), *tmp;//cur表示需要判断是否重复的节点的开始
		dummy.next = head;
		pre = &dummy;
		while(pre->next)
		{
			cur = tail = pre->next;
			while(tail && tail->val == cur->val)//定位到第一个非重复的节点
				tail = tail->next;
			if(cur->next != tail)//删除重复
			{
				while(cur != tail)
				{
					tmp = cur;
					cur = cur->next;
					free(tmp);
				}
				pre->next = tail;
			}
			else
			{
				pre = cur;
			}
		}
		return dummy.next;
    }
};


/*
discuss里的java代码，还是比较简洁的
*/
public ListNode deleteDuplicates(ListNode head) {
    if(head==null) return null;
    ListNode FakeHead=new ListNode(0);
    FakeHead.next=head;
    ListNode pre=FakeHead;
    ListNode cur=head;
    while(cur!=null){
        while(cur.next!=null&&cur.val==cur.next.val){//从cur开始相同的最长位置
            cur=cur.next;
        }
        if(pre.next==cur){//判断是否需要更改链表结构进行删除
            pre=pre.next;
        }
        else{
            pre.next=cur.next;
        }
        cur=cur.next;
    }
    return FakeHead.next;
}
