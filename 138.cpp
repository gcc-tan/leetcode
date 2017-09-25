//Copy List with Random Pointer

/*
A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

Return a deep copy of the list.
*/


/*
复制一个链表，但是链表中有随机指针指向其他其他节点。
------------------------------------------------------------------------------------------------------------
1. 最直接的想法就是给原来链表的节点和新链表的节点建立一个map，然后利用这个map更新random指针

2. discuss里面提出一种方法，使得空间复杂度降低为O(1)，核心的思想是将新建立的节点放在原来的节点之后，统一成一个链表，在建立好random指针后，拆分和还原原来链表
*/


/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
//方法1的实现
class Solution 
{
public:
    RandomListNode *copyRandomList(RandomListNode *head) 
	{
		RandomListNode *cur;
		unordered_map<RandomListNode *, RandomListNode *> mp;
		//建立map
		mp[0] = 0;
		for(cur = head; cur; cur = cur->next)
			mp[cur] = new RandomListNode(cur->label);

		//更改新链表的next指针和random指针
		for(cur = head; cur; cur = cur->next)
		{
			mp[cur]->next = mp[cur->next];
			mp[cur]->random = mp[cur->random];
		}
		return mp[head];
    }
};



//方法2实现
/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution 
{
public:
    RandomListNode *copyRandomList(RandomListNode *head) 
	{
		RandomListNode *iter, *next, dummy(0), *cp_iter;
		//复制原来节点，新节点加在原来节点后，最后形成一个新链表
		for(iter = head; iter; iter = next)
		{
			next = iter->next;
			iter->next = new RandomListNode(iter->label);
			iter->next->next = next;
		}
		//更新random指针
		for(iter = head; iter; iter =iter->next->next)
		{
			if(iter->random)
				iter->next->random = iter->random->next;
		}

		//拆分，恢复原来链表
		cp_iter = &dummy;
		for(iter = head; iter;)
		{
			next = iter->next->next;
			cp_iter->next = iter->next;
			cp_iter = iter->next;
			iter->next = next;
			iter = next;
		}
		return dummy.next;
    }
};
