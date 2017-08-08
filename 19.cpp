//Remove Nth Node From End of List

/*
Given a linked list, remove the nth node from the end of list and return its head.

For example,

   Given linked list: 1->2->3->4->5, and n = 2.

   After removing the second node from the end, the linked list becomes 1->2->3->5.
Note:
Given n will always be valid.
Try to do this in one pass.
*/

/*
题目很清楚，就是给出一个单链表，给出数字n，移除倒数第n个节点，题目有个小要求，要求一遍扫描
------------------------------------------------------------------------------------------------------------------------------------------

首先没有看见一遍扫描这个要求，直接就强上了。写完发现要一遍扫描，脑子也没有多想。弄了个vector存起来....真是愚蠢

正确的做法应该是快慢指针，先让快指针先走n，然后快慢指针一起移动，最后快指针到头了，慢指针就到达指定地点了。
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
	
	//可以从头遍历单链表，将每个节点的指针都存起来，然后知道节点个数之后计算其前驱节点位置，然后删除 不过这个做法是真的有点蠢
    ListNode* removeNthFromEnd(ListNode* head, int n) 
	{
		vector<ListNode *> v;
		struct ListNode *p = head;
		int pos;

		while(p)
		{
			v.push_back(p);
			p = p->next;
		}

		if(n == v.size()) //要删除的是头节点
		{
			p = head->next;
			free(head);
			return p;
		}

		pos = v.size() - n;
		v[pos-1]->next = v[pos]->next;
		free(v[pos]);
		return head;
    }
};



/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
//free肯定是个耗时的调用，速度快的代码明显是刷赖吗，注释了两个free之后再提交由首先的6%提高到了%58
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) 
{
	struct ListNode *fast = head, *low = head;
	int i;
	for(i = 0; i < n; ++i)//相差n个节点
		fast = fast->next;

	if(!fast) 
	{
		free(head);
		return low->next;
	}
	while(fast->next)//将fast定位到最后一个节点
	{
		fast = fast->next;
		low = low->next;
	}

	fast = low->next;
	low->next = fast->next;
	free(fast);

	return head;
}


//最后贴上两个很风骚的代码，一个是java写的，一个是c++写的。两个都很有意思，java代码同过添加虚拟节点使得处理统一化，c++比较有意思，很巧妙地用了二级指针达到了同样的效果。




public ListNode removeNthFromEnd(ListNode head, int n) {
    
    ListNode start = new ListNode(0);
    ListNode slow = start, fast = start;
    slow.next = head;
    
    //Move fast in front so that the gap between slow and fast becomes n
    for(int i=1; i<=n+1; i++)   {
        fast = fast.next;
    }
    //Move fast to the end, maintaining the gap
    while(fast != null) {
        slow = slow.next;
        fast = fast.next;
    }
    //Skip the desired node
    slow.next = slow.next.next;
    return start.next;
}




class Solution
{
public:
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        ListNode** t1 = &head, *t2 = head;
        for(int i = 1; i < n; ++i)
        {
            t2 = t2->next;
        }
        while(t2->next != NULL)
        {
            t1 = &((*t1)->next);
            t2 = t2->next;
        }
        *t1 = (*t1)->next;
        return head;
    }
};
