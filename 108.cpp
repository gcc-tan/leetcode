//Convert Sorted Array to Binary Search Tree

/*
Given an array where elements are sorted in ascending order, convert it to a height balanced BST
*/


/*
根据一个升序数组，构造一个高度平衡的二叉搜索树(高度平衡的应该是左右子树的高度差不超过1)
-------------------------------------------------------------------------------------------------
每次均分节点，构造左右子树就能构造一个平衡的二叉树
*/



/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution 
{
private:
	TreeNode *recursive(int *a, int n)
	{
		TreeNode *root;
		int pos;
		if(n <= 0) return 0;
		pos = n / 2;

		root = new TreeNode(a[pos]);
		root->left = recursive(a, pos);
		root->right = recursive(a + pos + 1, n - pos - 1);
		return root;
	}
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) 
	{
		if(nums.size() == 0) return 0;
		return recursive(&nums[0], nums.size());
    }
};



/*
discuss里面的java代码，瞬间感觉清楚明了了不少(使用start和end)
*/
public TreeNode sortedArrayToBST(int[] num) {
    if (num.length == 0) {
        return null;
    }
    TreeNode head = helper(num, 0, num.length - 1);
    return head;
}

public TreeNode helper(int[] num, int low, int high) {
    if (low > high) { // Done
        return null;
    }
    int mid = (low + high) / 2;
    TreeNode node = new TreeNode(num[mid]);
    node.left = helper(num, low, mid - 1);
    node.right = helper(num, mid + 1, high);
    return node;
}
