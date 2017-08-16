#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <sstream>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/*
			1
		   / \
		  2   3
		 / \   \
		4   5   6
		   /
		  7
*/
TreeNode* initTreeNode(TreeNode* root)
{
	root = new TreeNode(1);
	root->left = new TreeNode(2);
	root->right = new TreeNode(3);
	root->left->left = new TreeNode(4);
	root->left->right = new TreeNode(5);
	root->right->right = new TreeNode(6);
	root->left->right->left = new TreeNode(7);
	return root;
}

// ǰ������ĵݹ���ʽ
void pre_travel(TreeNode* root)
{
	if (!root) return;
	cout << root->val << " ";
	pre_travel(root->left);
	pre_travel(root->right);
}

// ��������ķǵݹ���ʽ
void level_travel(TreeNode* root)
{
	if (!root) return;
	queue<TreeNode*> q;
	q.push(root);
	while (!q.empty()) {
		TreeNode* t = q.front();
		cout << t->val << " ";
		q.pop();
		if (t->left) q.push(t->left);
		if (t->right) q.push(t->right);
	}
}

// �����������һ�ַ�ʽ
// ���԰����ӡ
// ˼·�������������н�����а��ղ�����
vector<vector<int>> levelOrder(TreeNode* root) {
	vector<vector<int>> ret;
	if (!root) return ret;
	queue<TreeNode*> q1, q2;
	q1.push(root);
	while (!q1.empty()) {
		vector<int> v;
		while (!q1.empty()) {
			TreeNode* t = q1.front();
			v.push_back(t->val);
			q1.pop();
			if (t->left) q2.push(t->left);
			if (t->right) q2.push(t->right);
		}
		q1.swap(q2);
		ret.push_back(v);
	}
	return ret;
}

// �����������һ�ַ�ʽ
// ���԰����ӡ
// ˼·������vector������ָ�룬һ��ָ��ǰ����׽ڵ㣬һ��ָ����һ����׽ڵ�
vector<vector<int>> levelOrder02(TreeNode* root) {
	vector<vector<int>> ret;
	if (!root) return ret;
	vector<TreeNode*> vt;
	int cur = 0;
	int end = 0;
	vt.push_back(root);
	while (cur < vt.size()) {
		end = vt.size();
		vector<int> vi;
		while (cur < end) {
			vi.push_back(vt[cur]->val);
			if (vt[cur]->left) vt.push_back(vt[cur]->left);
			if (vt[cur]->right) vt.push_back(vt[cur]->right);
			cur++;
		}
		ret.push_back(vi);
	}
	return ret;
}

// bottom-up level order traversal
// �������ϵĲ������
// ˼·�Ǵ������µĻ�������ջ�ȴ棬Ȼ��ȡ��
// Ҳ����ֱ�ӵ���reverse��ת
// ���������ο���
// https://leetcode.com/problems/binary-tree-level-order-traversal-ii/discuss/
vector<vector<int>> levelOrderBottom(TreeNode* root) {
	vector<vector<int>> ret;
	if (!root) return ret;
	vector<TreeNode*> vt;
	stack<vector<int>> st;
	int cur = 0;
	int end = 0;
	vt.push_back(root);
	while (cur < vt.size()) {
		end = vt.size();
		vector<int> vi;
		while (cur < end) {
			vi.push_back(vt[cur]->val);
			if (vt[cur]->left) vt.push_back(vt[cur]->left);
			if (vt[cur]->right) vt.push_back(vt[cur]->right);
			cur++;
		}
		st.push(vi);
	} 
	while (!st.empty()) {
		ret.push_back(st.top());
		st.pop();
	}
	return ret;
}

// ��һ�ֲ�α����Ľⷨ
// �����������
void dfs(TreeNode *root, int height, vector<vector<int>> &ret){
	if (root == NULL)
		return;
	while (ret.size() <= height)
		ret.push_back(vector<int>());
	ret[height].push_back(root->val);
	dfs(root->left, height + 1, ret);
	dfs(root->right, height + 1, ret);
}

vector<vector<int>> levelOrderBottom02(TreeNode* root) {
	vector<vector<int>> ret;
	dfs(root, 0, ret);
	reverse(ret.begin(), ret.end());
	return ret;
}

// Z���α���������
// �����ⷨ�ο���
// https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/discuss/
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
	vector<vector<int>> ret;
	if (!root) return ret;
	vector<TreeNode*> vt;
	int cur = 0;
	int end = 0;
	vt.push_back(root);
	while (cur < vt.size()) {
		end = vt.size();
		vector<int> vi;
		while (cur < end) {
			vi.push_back(vt[cur]->val);
			if (vt[cur]->left) vt.push_back(vt[cur]->left);
			if (vt[cur]->right) vt.push_back(vt[cur]->right);
			cur++;
		}
		ret.push_back(vi);
	}
	for (int i = 0; i<ret.size(); i++) {
		if (i % 2 == 1) {
			reverse(ret[i].begin(), ret[i].end());
		}
	}
	return ret;
}


// ��ӡ�ķ�װ
void pt_vecvec(vector<vector<int>> vvi) {
	cout << "----------------" << endl;
	for (auto i : vvi) {
		for (auto j : i) {
			cout << j << ",";
		}
		cout << endl;
	}
	cout << "----------------" << endl;
}

// ��ÿһ��ڵ��ƽ��ֵ
vector<double> averageOfLevels(TreeNode* root) {
	vector<double> ret;
	if (!root) return ret;
	vector<TreeNode*> vt;
	int cur = 0;
	int end = 0;
	vt.push_back(root);
	while (cur < vt.size()) {
		end = vt.size();
		long int sum = 0;
		int len = end - cur;
		while (cur < end) {
			sum += vt[cur]->val;
			if (vt[cur]->left) vt.push_back(vt[cur]->left);
			if (vt[cur]->right) vt.push_back(vt[cur]->right);
			cur++;
		}
		double average = 0.0;
		if (len)
			average = (double)sum / len;
		ret.push_back(average);
	}
	return ret;
}


// ��ת������
// �ǵݹ� ջ
TreeNode* invertTree(TreeNode* root) {
	if (!root) return NULL;
	stack<TreeNode*> s;
	s.push(root);
	while (!s.empty()) {
		TreeNode* t = s.top();
		s.pop();
		swap(t->left, t->right);
		if (t->left) s.push(t->left);
		if (t->right) s.push(t->right);
	}
	return root;
}

// ��������������
// �ݹ�
int maxDepth(TreeNode* root) {
	if (!root) return 0;
	int left = maxDepth(root->left);
	int right = maxDepth(root->right);
	return max(left, right) + 1;
}

// ��������С���
// �ݹ�
int minDepth(TreeNode* root) {
	if (!root) return 0;
	if (!root->left) return minDepth(root->right) + 1;
	if (!root->right) return minDepth(root->left) + 1;
	return min(minDepth(root->left), minDepth(root->right)) + 1;
}

// �ж�һ�����Ƿ�Ϊƽ�������
bool isBalancedInner(TreeNode* root, int &depth) {
	if (!root) {
		depth = 0;
		return true;
	}
	int left_depth = 0;
	int right_depth = 0;
	bool left = isBalancedInner(root->left, left_depth);
	bool right = isBalancedInner(root->right, right_depth);
	if (left && right) {
		int d = left_depth - right_depth;
		if (d <= 1 && d >= -1) {
			depth = max(left_depth, right_depth) + 1;
			return true;
		}
	}
	return false;
}

bool isBalanced(TreeNode* root) {
	int depth = 0;
	return isBalancedInner(root, depth);
}

// �ж��Ƿ����һ����������·����Ϊĳ��ֵ
bool findPath(TreeNode* root, int sum, int expectedSum) {
	sum += root->val;
	bool isLeaf = !root->left && !root->right;
	if (sum == expectedSum && isLeaf) return true;
	bool l = false;
	bool r = false;
	if (root->left) l = findPath(root->left, sum, expectedSum);
	if (root->right) r = findPath(root->right, sum, expectedSum);
	if (l || r) return true;
	return false;
}

bool hasPathSum(TreeNode* root, int sum) {
	if (!root) return false;
	int currsum = 0;
	return findPath(root, currsum, sum);
}

// �ж��Ƿ����һ����������·����Ϊĳ��ֵ������ӡ����·��
void findpath(TreeNode* root, vector<int> &path, vector<vector<int>> &path_all, int exceptedSum, int curSum) {
	curSum += root->val;
	path.push_back(root->val);
	bool isLeaf = !root->left && !root->right;
	if (curSum == exceptedSum && isLeaf)
		path_all.push_back(path);
	if (root->left) findpath(root->left, path, path_all, exceptedSum, curSum);
	if (root->right) findpath(root->right, path, path_all, exceptedSum, curSum);
	path.pop_back();
}

vector<vector<int>> pathSum(TreeNode* root, int sum) {
	vector<vector<int>> ret;
	if (!root) return ret;
	vector<int> path;
	int cursum = 0;
	findpath(root, path, ret, sum, cursum);
	return ret;
}

string itostr(int i) {
	stringstream ss;
	string ret;
	ss << i;
	ss >> ret;
	return ret;
}


void bitreeepath(TreeNode* root, vector<string>& vs, string s) {
	if (!root) return;
	bool isLeaf = !root->left && !root->right;
	if (isLeaf)
		vs.push_back(s);
	if (root->left)    bitreeepath(root->left, vs, s + "->" + to_string(root->left->val));
	if (root->right)    bitreeepath(root->right, vs, s + "->" + to_string(root->right->val));
}

vector<string> binaryTreePaths(TreeNode* root) {
	vector<string> ret;
	if (!root) return ret;
	bitreeepath(root, ret, to_string(root->val));
	return ret;
}


void testTreeNode()
{
	TreeNode* root = NULL;
	root = initTreeNode(root);
	cout << "\npre travel: " << endl;
	pre_travel(root);
	cout << "\nlevel travel: " << endl;
	level_travel(root);

	cout << "\ninvertTree: " << endl;
	root = invertTree(root);
	cout << "\nlevel travel: " << endl;
	level_travel(root);
	root = invertTree(root);
	cout << "\nlevel travel: " << endl;
	level_travel(root);

	cout << "\nmax depth of tree is: " << endl;
	cout << maxDepth(root) << endl;

	cout << "\nmin depth of tree is: " << endl;
	cout << minDepth(root) << endl;

	cout << "\nlevel order travel of tree is: " << endl;
	vector<vector<int>> ret = levelOrder(root);
	pt_vecvec(ret);
	cout << "\nlevel order travel of tree is: " << endl;
	vector<vector<int>> ret02 = levelOrder02(root);
	pt_vecvec(ret02);

	vector<string> sret = binaryTreePaths(root);
	for (string s : sret) {
		cout << s << endl;
	}

}

int main(void)
{
	testTreeNode();
	return 0;
}

