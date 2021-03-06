// BST.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

/*

建树操作 CreatRoot() Put() GetNum()
搜索 Get()返回节点
插入 Put()
删除 DeleteMin() Min() Delete() GetNum()
遍历 ...

*/
struct Node
{
	//左右子节点
	Node *left, *right;
	//值
	int val;
	//节点数量
	int num;
};

//创建根节点
Node* CreatRoot()
{
	Node* node = new Node;
	int n;
	scanf_s("%d", &n);
	node->val = n;
	node->left = NULL;
	node->right = NULL;
	return node;
}

/*
//以root为根节点创建树
void CreatNode(Node* root,int n)
{
	//当前树
	Node* node = new Node;
	//设置根节点
	node->root = root;
	//设置值
	int t;
	node->val = n;
	//小于0为null
	if (n < 0)
		return;
	//接入root
	if (n < root->val && root->left == NULL)
		root->left = node;
	else if (n > root->val && root->right == NULL)
		root->right = node;
	else
		return;
}
*/

//设置节点数
int GetNum(Node* node)
{
	//如果空节点，返回0
	if (node == NULL)
		return 0;
	//如果是末节点，节点数为1
	if (node->left == NULL && node->right == NULL)
		node->num = 1;
	//否则递归
	else
		node->num = GetNum(node->left) + GetNum(node->right) + 1;
	return node->num;
}

//插入操作 在node位置插入新节点，如果node位置存在节点，则比较后向下put
Node* Put(Node* node, int n)
{
	//创建节点，结束put
	if (node == NULL)
	{
		Node* node2 = new Node;
		node2->val = n;
		node2->left = NULL;
		node2->right = NULL;
		node2->num = GetNum(node2);
		return node2;
	}
	//寻找节点
	if (n < node->val)
		node->left = Put(node->left, n);
	else if (n > node->val)
		node->right = Put(node->right, n);
	//最后设置num
	node->num = GetNum(node);
	//如果值相等，或者上述put完成，结束put
	return node;						
}

//简单查找
Node* Get(Node *node, int n)
{
	if (node == NULL)
		return NULL;
	if (n == node->val)
		return node;
	else if (n < node->val)
		return Get(node->left, n);
	else
		return Get(node->right, n);
}

//先序遍历*沙雕式
void Traversal(Node *node)
{
	if (node == NULL)
	{
		printf_s("空");
		return;
	}
	if (node != NULL)
		printf_s("%d", node->val);
	printf_s("左");
	Traversal(node->left);
	printf_s("右");
	Traversal(node->right);
	printf_s("沙雕");
}

//删除最小 删除时返回新节点，搜索时返回当前节点
Node* DeleteMin(Node *node)
{
	if (node->left == NULL)
	{
		Node* node2 = node->right;
		delete(node);
		//刷新num
		node2->num = GetNum(node2);
		return node2;
	}
	//如果不满足条件，继续往下搜索，并返回自身(不改变链接
	//递归同时链接，最终将新节点和末尾链接上
	node->left = DeleteMin(node->left);
	//刷新num
	node->num = GetNum(node);

	return node;
}

//查找最小
Node *Min(Node *node)
{
	if (node->left == NULL)
		return node;
	else
		return Min(node->left);
}

//查找并删除
Node *Delete(Node *node,int n)
{
	if (node == NULL)
		return NULL;
	//匹配，删除操作
	if (node->val == n)
	{
		//单子节点情况
		if (node->left == NULL)
		{
			return node->right;
		}
		if (node->right == NULL)
		{
			return node->left;
		}
		//新节点取右子树的最小节点
		Node *node2 = Min(node->right);
		node2->left = node->left;
		//删除原新节点并链接上右节点
		node2->right = DeleteMin(node->right);
		//删除原节点
		delete(node);
		//刷新num
		node2->num = GetNum(node2);
		return node2;
	}
	//不匹配时返回当前节点，不改动链接
	if (n < node->val)
	{
		node->left = Delete(node->left, n);
		//刷新num
		node->num = GetNum(node);
		return node;
	}
	else if (n > node->val)
	{
		node->right = Delete(node->right, n);
		//刷新num
		node->num = GetNum(node);
		return node;
	}
	
}



int main()
{
	//用插入建树
	int n;
	printf_s("输入根节点数据:");
	Node* j = CreatRoot();
	j->num = 0;
	while (true)
	{
		printf_s("输入子节点数据(负数终止):");
		scanf_s("%d", &n);
		if (n < 0)				//结束建树
			break;
		Put(j, n);
	}
	/*
	//遍历
	Traversal(j);

	//查找

	printf_s("输入需查找数:");
	scanf_s("%d ", &n);
	printf_s("%d ", Get(j, n)->val);
	
	//删除
	printf_s("输入被删除数:");
	scanf_s("%d", &n);
	Delete(j, n);
	*/
	//断点查看树（原始方法
    return 0;
}



