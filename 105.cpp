//Construct Bianry Tree from Preorder and Inorder Traversal

/*
Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.
*/


/*
根据前序和中序序列构造二叉树。
----------------------------------------------------------------------------------------------------------------------------
题目很经典，根据前序的第一元素知道当前的根，然后在中序中找到根节点，然后获取左右子树的中序序列，进行递归构造
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
	TreeNode *build_recursive(int *preorder, int n1, int *inorder, int n2)
	{
		int i, j;
		TreeNode *root;
		if(n1 <= 0 || n2 <= 0) return 0;
		root = new TreeNode(preorder[0]);
		for(j = 0; j < n2; ++j)//在中序序列中找到当前的根节点，然后在中序中找到的位置，得到左子树的前序和中序，右子树的前序和中序，进行递归构造
			if(inorder[j] == preorder[0]) break;

		root->left = build_recursive(preorder + 1, j, inorder, j);
		root->right = build_recursive(preorder + j + 1, n1 - j - 1, inorder + j + 1, n2 - j - 1);
		return root;
	}
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) 
	{
		if(preorder.size() == 0 || inorder.size() == 0) return 0;
		return build_recursive(&preorder[0], preorder.size(), &inorder[0], inorder.size());
    }
};




/*
非递归的解决方案，确实不太好懂，没有递归直观
-----------------------------------------------------------------------------------------------------------------------
算法的大概流程

     A
	/ \
   B   C
  / \
  D E
上面一棵二叉树，这个算法的流程是使用一个栈(st)，栈维护的是右子树没有被处理的节点。为了简化代码，st开始推入一个dummy节点。然后新建一个A节点，st.top()->left = A, st.push(A) ,新建一个结点B...
重复上面过程直到节点D为栈顶，然后弹栈(弹栈同时记录栈顶pp)，栈顶为B，再弹栈，栈顶为A, pp 为B。B为父节点游子节点为E，E入栈。....
*/

class Solution {
public:
    TreeNode *buildTree(vector<int> &pre, vector<int> &in) {
        int i=0,j=0;
        TreeNode *root=new TreeNode(0x80000000);
        TreeNode *pp=NULL,*ptr=root;
        stack<TreeNode*> sn;sn.push(root);
        while (j<in.size()) {
            if (sn.top()->val==in[j]) {//栈顶和中序结果相等，pp赋值为栈顶，弹栈
                pp=sn.top();
                sn.pop();
                j++;
            } else if (pp) {//将pp作为父节点，前序的当前节点作为右子树
                ptr=new TreeNode(pre[i]);
                pp->right=ptr;pp=NULL;
                sn.push(ptr);
                i++;
            } else {//将前序的当前节点作为栈顶节点的左子树
                ptr=new TreeNode(pre[i]);
                sn.top()->left=ptr;
                sn.push(ptr);
                i++;
            }
        }
        ptr=root->left;delete root;
        return ptr;
    }
}; 
