//Reverse Nodes in k-Group

/*
Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

You may not alter the values in the nodes, only nodes itself may be changed.

Only constant memory is allowed.

For example,
Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5
*/

/*
和之前的24题有点类似，但是这个节点是k个为一组对链表进行反转，要求和之前的一样。如果剩下的节点小于k，那么就不做改变
-------------------------------------------------------------------------------------------------------------------------------
思路还是很明确的，就是根据k值分段去反转链表。

这个leetcode的测试用例是真的很有意思，题目里面明明说了k是小于链表的长度，测试用例里面居然出现了大于链表长度的例子。[1,2] k = 3

首先没有加上一个虚拟节点，没有计算节点的个数，结果边界条件是真的很恶心
*/


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseKGroup(struct ListNode* head, int k) 
{
	struct ListNode *pre, *cur, *cur_next, node;//单链表中的很多操作通过添加一个虚拟节点都能简化
	int num, i;
	if(!head || k <= 1) return head;
	node.next = head, pre = &node, cur_next;

	for(cur = head, num = 0; cur; ++num)//计算节点的个数
		cur = cur->next;

	while((num -= k) >= 0)
	{
		cur = pre->next;
		cur_next = cur->next;
		for(i = 1; i < k; ++i)//每次将cur_next节点放在pre节点后
		{
			cur->next = cur_next->next;
			cur_next->next = pre->next;
			pre->next = cur_next;

			cur_next = cur->next;
		}
		pre = cur;
	}

	return node.next;
}


//上面的代码是非递归的版本，这里还有一个更好理解的递归的版本。道理都差不多，先找到k+1的节点，然后作为头节点递归调用，而前面的节点进行一次单链表反转就行。

public ListNode reverseKGroup(ListNode head, int k) {
    ListNode curr = head;
    int count = 0;
    while (curr != null && count != k) { // find the k+1 node
        curr = curr.next;
        count++;
    }
    if (count == k) { // if k+1 node is found
        curr = reverseKGroup(curr, k); // reverse list with k+1 node as head
        // head - head-pointer to direct part, 
        // curr - head-pointer to reversed part;
        while (count-- > 0) { // reverse current k-group: 
            ListNode tmp = head.next; // tmp - next head in direct part
            head.next = curr; // preappending "direct" head to the reversed list 
            curr = head; // move head of reversed part to a new node
            head = tmp; // move "direct" head to the next node in direct part
        }
        head = curr;
    }
    return head;
}
