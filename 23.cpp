//Merge k Sorted Lists

/*
Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
*/


/*
这个题目我也是醉了，合并k个有序的链表。又没有说明白链表是升序还是降序。就当升序好了

反正思路肯定是用堆，加入k个链表的头节点。每次从堆中取出最小的元素作为头节点，然后加入这个链表的下一个节点到堆中。重复上面过程，直到所有元素都取完
*/



#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 typedef struct ListNode
 {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
 }ListNode;

class Solution
{
public:
	bool operator()(ListNode *a,ListNode *b)
	{
		return a->val > b->val;
	}
    ListNode* mergeKLists(vector<ListNode*>& lists)
	{
		int i;
		ListNode n(0), *head = &n, *p = head;
		priority_queue<ListNode *,vector<ListNode *>,Solution> q;
		for(i = 0; i < lists.size(); ++i)
			if(lists[i]) q.push(lists[i]);//leetcode的测试用例醉了，给出的头节点还有为空的，有这个必要吗

		while(!q.empty())
		{
			p->next = q.top();
			q.pop();
			p = p->next;
			if(p->next)
				q.push(p->next);
		}
		return head->next;
    }
};

int main()
{
    Solution s;
    vector<ListNode *> v(3,(ListNode *)0);
    ListNode *h1 = new ListNode(2), *h2 = new ListNode(6), *h3 = new ListNode(3), *h4;
    h1->next = new ListNode(4), h2->next = new ListNode(7);
    v[0] = h1, v[1] = h2, v[2] = h3;
    h4 = s.mergeKLists(v);
    while(h4)
    {
        cout<<h4->val<<" ";
        h4 = h4->next;
    }
    return 0;
}

