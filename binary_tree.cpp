// demo1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;


void t01()
{
	vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	for (auto &i : v)
	{
		if (i == 3) i = 5;
	}
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

// 二叉树
struct BiNode {
	int val;
	BiNode* left, *right;
	BiNode(int i) : val(i), left(NULL), right(NULL) {}
};



BiNode* initBiNode(BiNode* root) {
	int a;
	cin >> a;
	if (0 == a) return NULL;
	root = new BiNode(a);
	root->left = initBiNode(root->left);
	root->right = initBiNode(root->right);
	return root;
}

void PreTravel(BiNode* root) {
	if (NULL == root) return;
	cout << root->val << " ";
	PreTravel(root->left);
	PreTravel(root->right);
}

//先序遍历 非递归方式
//思路：将右节点压栈，遍历完左节点后开始右节点出栈，
// 这时候视为子树的根节点，边出栈边压栈该根节点的右子节点，然后再次遍历子树的左节点，同时输出。
// 等于出栈的过程又把前面压栈的过程执行了一遍
void PreTravel2(BiNode* root) {
	stack<BiNode*> s;
	if (root == NULL) return;
	BiNode* t = root;
	while (t != NULL) {
		cout << t->val << " ";
		if (t->right != NULL) {
			s.push(t->right);
		}
		t = t->left;
	}
	while (s.size() > 0) {
		t = s.top();
		s.pop();
		cout << t->val << " ";
		while (t != NULL) {
			if (t->right != NULL)
				s.push(t->right);
			t = t->left;
			if (t != NULL)
				cout << t->val << " ";
		}
	}
}

// 对2的简化和改进
void PreTravel3(BiNode* root) {
	stack<BiNode*> s;
	if (root == NULL) return;
	BiNode* t = root;
	while (t != NULL) {
		cout << t->val << " ";
		if (t->right != NULL) {
			s.push(t->right);
		}
		t = t->left;
	}
	while (s.size() > 0) {
		t = s.top();
		s.pop();
		while (t != NULL) {
			cout << t->val << " ";
			if (t->right != NULL) {
				s.push(t->right);
			}
			t = t->left;
		}
	}
}

// 前序遍历的另一种解法
// 压入顺序：右子树->左子树->根节点 
// 使得访问的时候的顺序成为：根->左子树->右子树
void PreTravel4(BiNode* root) {
	stack<BiNode*> s;
	if (root == NULL) return;
	s.push(root);
	while (!s.empty()) {
		BiNode* t = s.top();
		s.pop();
		cout << t->val << " ";
		if (t->right)
			s.push(t->right);
		if (t->left)
			s.push(t->left);
	}
}

//中序遍历
void InTravel(BiNode* root) {
	if (NULL == root) return;
	InTravel(root->left);
	cout << root->val << " ";
	InTravel(root->right);
}


// 中序遍历 非递归
// 思路：先左边节点递归压栈，然后依次出栈，
// 出栈过程中判断右节点是否为空，不是则将右节点压栈(if 1次)，
// 然后判断该右节点的左节点是否为空，不为空则压栈(while 依次压栈)
void InTravel2(BiNode* root) {
	stack<BiNode*> s;
	BiNode* t = root;
	while (t != NULL) {
		s.push(t);
		t = t->left;
	}
	while (s.size() > 0) {
		t = s.top();
		s.pop();
		cout << t->val << " ";
		if (t->right != NULL) {
			t = t->right;
			s.push(t);
			while (t != NULL) {
				if (t->left != NULL) {
					s.push(t->left);
				}
				t = t->left;
			}
		}
	}
}

// 中序遍历的非递归 另一种方式
// 压入顺序：右子树->根->左子树 
// 只有当左子树已经访问完后，才能访问根节点
// 对于任一结点P，
// 1)若其左孩子不为空，则将P入栈并将P的左孩子置为当前的P，然后对当前结点P再进行相同的处理；
// 2)若其左孩子为空，则取栈顶元素并进行出栈操作，访问该栈顶结点，然后将当前的P置为栈顶结点的右孩子；
// 3)直到P为NULL并且栈为空则遍历结束
void InTravel3(BiNode* root) {
	stack<BiNode*> s;
	if (root == NULL) return;
	BiNode* t = root;
	while (!s.empty() || t != NULL) {
		if (t != NULL) {
			s.push(t);
			t = t->left;
		}
		else {
			t = s.top();
			cout << t->val << " ";
			s.pop();
			t = t->right;
		}
	}
}

//后序遍历
void PostTravel(BiNode* root) {
	if (NULL == root) return;
	PostTravel(root->left);
	PostTravel(root->right);
	cout << root->val << " ";
}



// 后序遍历的非递归方式
// 参考：http://blog.csdn.net/quzhongxin/article/details/46315251
// 对于任一结点P，将其入栈，然后沿其左子树一直往下搜索，直到搜索到没有左孩子的结点，
// 此时该结点出现在栈顶，但是此时不能将其出栈并访问，因此其右孩子还为被访问。
// 所以接下来按照相同的规则对其右子树进行相同的处理，当访问完其右孩子时，该结点又出现在栈顶，
// 此时可以将其出栈并访问。这样就保证了正确的访问顺序。
// 可以看出，在这个过程中，每个结点都两次出现在栈顶，只有在第二次出现在栈顶时，才能访问它。
void PostTravel2(BiNode* root) {
	if (NULL == root) return;
	stack<BiNode*> s;
	BiNode* t = root; //记录当前正在访问的节点
	BiNode* lastvisited; //记录刚刚访问过的节点
	do {
		while (t != NULL) {
			s.push(t);
			t = t->left;
		}
		lastvisited = NULL;
		while (!s.empty()) {
			t = s.top();
			s.pop();
			if (t->right == lastvisited) { //如果右子树访问过了，就可以输出根的值
				cout << t->val << " ";
				lastvisited = t; //记录刚才访问过的节点
			}
			else { //第一次访问该节点，需要将其重新入栈
				s.push(t);
				t = t->right;
				break;
			}
		}
	} while (!s.empty());
}

// 递归打印第i层，i从0开始
int pt_level(BiNode* t, int level) {
	if (t == NULL || level < 0) {
		return 0;
	}
	if (0 == level) {
		cout << t->val << " ";
		return 1;
	}
	return pt_level(t->left, level - 1) + pt_level(t->right, level - 1);
}


// 层序遍历
void levelTravel(BiNode* root) {
	for (int i = 0;; i++) {
		if (!pt_level(root, i))
			break;
	}
	cout << endl;
}

// 层序遍历
void levelTravel2(BiNode* root) {
	if (root == NULL) return;
	queue<BiNode*> q;
	q.push(root);
	while (!q.empty()) {
		BiNode* t = q.front();
		cout << t->val << " ";
		q.pop();
		if (t->left) q.push(t->left);
		if (t->right) q.push(t->right);
	}
}


void testBiNode()
{
	// 1 2 4 8 0 0 9 0 0 5 10 0 0 0 3 6 0 0 7 0 0
	BiNode* t = NULL;
	cout << "input node val:" << endl;
	t = initBiNode(t);
	cout << "\npreorder travel:" << endl;
	PreTravel(t);
	cout << "\npreorder travel2:" << endl;
	PreTravel2(t);
	cout << "\npreorder travel3:" << endl;
	PreTravel3(t);
	cout << "\npreorder travel4:" << endl;
	PreTravel4(t);

	cout << "\ninorder travel:" << endl;
	InTravel(t);
	cout << "\ninorder travel2:" << endl;
	InTravel2(t);
	cout << "\ninorder travel3:" << endl;
	InTravel3(t);

	cout << "\npostorder travel:" << endl;
	PostTravel(t);
	cout << "\npostorder travel2:" << endl;
	PostTravel2(t);

	cout << "\npt_level 1:" << endl;
	pt_level(t, 0);
	cout << "\nlevelorder travel:" << endl;
	levelTravel(t);
	cout << "\nlevelorder travel2:" << endl;
	levelTravel2(t);

	cout << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//t01();
	testBiNode();
	return 0;
}

