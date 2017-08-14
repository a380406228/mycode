// demo1.cpp : �������̨Ӧ�ó������ڵ㡣
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

// ������
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

//������� �ǵݹ鷽ʽ
//˼·�����ҽڵ�ѹջ����������ڵ��ʼ�ҽڵ��ջ��
// ��ʱ����Ϊ�����ĸ��ڵ㣬�߳�ջ��ѹջ�ø��ڵ�����ӽڵ㣬Ȼ���ٴα�����������ڵ㣬ͬʱ�����
// ���ڳ�ջ�Ĺ����ְ�ǰ��ѹջ�Ĺ���ִ����һ��
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

// ��2�ļ򻯺͸Ľ�
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

// ǰ���������һ�ֽⷨ
// ѹ��˳��������->������->���ڵ� 
// ʹ�÷��ʵ�ʱ���˳���Ϊ����->������->������
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

//�������
void InTravel(BiNode* root) {
	if (NULL == root) return;
	InTravel(root->left);
	cout << root->val << " ";
	InTravel(root->right);
}


// ������� �ǵݹ�
// ˼·������߽ڵ�ݹ�ѹջ��Ȼ�����γ�ջ��
// ��ջ�������ж��ҽڵ��Ƿ�Ϊ�գ��������ҽڵ�ѹջ(if 1��)��
// Ȼ���жϸ��ҽڵ����ڵ��Ƿ�Ϊ�գ���Ϊ����ѹջ(while ����ѹջ)
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

// ��������ķǵݹ� ��һ�ַ�ʽ
// ѹ��˳��������->��->������ 
// ֻ�е��������Ѿ�������󣬲��ܷ��ʸ��ڵ�
// ������һ���P��
// 1)�������Ӳ�Ϊ�գ���P��ջ����P��������Ϊ��ǰ��P��Ȼ��Ե�ǰ���P�ٽ�����ͬ�Ĵ���
// 2)��������Ϊ�գ���ȡջ��Ԫ�ز����г�ջ���������ʸ�ջ����㣬Ȼ�󽫵�ǰ��P��Ϊջ�������Һ��ӣ�
// 3)ֱ��PΪNULL����ջΪ�����������
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

//�������
void PostTravel(BiNode* root) {
	if (NULL == root) return;
	PostTravel(root->left);
	PostTravel(root->right);
	cout << root->val << " ";
}



// ��������ķǵݹ鷽ʽ
// �ο���http://blog.csdn.net/quzhongxin/article/details/46315251
// ������һ���P��������ջ��Ȼ������������һֱ����������ֱ��������û�����ӵĽ�㣬
// ��ʱ�ý�������ջ�������Ǵ�ʱ���ܽ����ջ�����ʣ�������Һ��ӻ�Ϊ�����ʡ�
// ���Խ�����������ͬ�Ĺ������������������ͬ�Ĵ��������������Һ���ʱ���ý���ֳ�����ջ����
// ��ʱ���Խ����ջ�����ʡ������ͱ�֤����ȷ�ķ���˳��
// ���Կ���������������У�ÿ����㶼���γ�����ջ����ֻ���ڵڶ��γ�����ջ��ʱ�����ܷ�������
void PostTravel2(BiNode* root) {
	if (NULL == root) return;
	stack<BiNode*> s;
	BiNode* t = root; //��¼��ǰ���ڷ��ʵĽڵ�
	BiNode* lastvisited; //��¼�ոշ��ʹ��Ľڵ�
	do {
		while (t != NULL) {
			s.push(t);
			t = t->left;
		}
		lastvisited = NULL;
		while (!s.empty()) {
			t = s.top();
			s.pop();
			if (t->right == lastvisited) { //������������ʹ��ˣ��Ϳ����������ֵ
				cout << t->val << " ";
				lastvisited = t; //��¼�ղŷ��ʹ��Ľڵ�
			}
			else { //��һ�η��ʸýڵ㣬��Ҫ����������ջ
				s.push(t);
				t = t->right;
				break;
			}
		}
	} while (!s.empty());
}

// �ݹ��ӡ��i�㣬i��0��ʼ
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


// �������
void levelTravel(BiNode* root) {
	for (int i = 0;; i++) {
		if (!pt_level(root, i))
			break;
	}
	cout << endl;
}

// �������
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

