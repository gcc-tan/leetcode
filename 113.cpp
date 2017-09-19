//Path Sum II


/*
Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.

For example:
Given the below binary tree and sum = 22,
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1
return
[
   [5,4,11,2],
   [5,8,4,5]
]
*/

/*
从根节点到叶子节点的路径，使得路径上的和为sum
-------------------------------------------------------------------------------------------------------
递归的方法很简单
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
	void recursive(vector<vector<int>> &ans, vector<int> &path, TreeNode *root, int sum)
	{
		if(!root) return;
		if(sum == root->val && !root->left && !root->right)//保证是叶子节点
		{
			ans.push_back(path);
			ans.back().push_back(root->val);//保证path的入和出是配对的，不然会对其他结果影响
			return;
		}
		path.push_back(root->val);
		recursive(ans, path, root->left, sum - root->val);
		recursive(ans, path, root->right, sum - root->val);
		path.pop_back();
	}
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) 
	{
		vector<vector<int>> ans;
		vector<int> path;
		recursive(ans, path, root, sum);
		return ans;
    }
};









/*
这是discuss中非递归的版本，仔细观察其实这个非递归的版本和后续非递归遍历很相似。因为path变量中需要记录从根节点到页节点的所有节点的信息，
所以只有当某个节点的左右子树都访问完成才能将这个节点从path中移除。因此使用一个pre变量表示之前访问的节点
*/
public class Solution {
    public List<List<Integer>> pathSum(TreeNode root, int sum) {
        List<List<Integer>> res = new ArrayList<>();
        List<Integer> path = new ArrayList<>();
        Stack<TreeNode> stack = new Stack<TreeNode>();
        int SUM = 0;
        TreeNode cur = root;
        TreeNode pre = null;
        while(cur!=null || !stack.isEmpty()){
            while(cur!=null){
                stack.push(cur);
                path.add(cur.val);
                SUM+=cur.val;
                cur=cur.left;
            }
            cur = stack.peek();
            if(cur.right!=null && cur.right!=pre){
                cur = cur.right;
                continue;
            } 
            if(cur.left==null && cur.right==null && SUM==sum) 
                res.add(new ArrayList<Integer>(path));
  
            pre = cur;
            stack.pop();
            path.remove(path.size()-1);
            SUM-=cur.val;
            cur = null;
        
        }
        return res;
    }
}
