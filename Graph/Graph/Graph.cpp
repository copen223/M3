// Graph.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>


//链接表
struct List
{
	int num;
	List *next;
};

//顶点
struct Vetex
{
	//数值
	int val;
	//编号
	int num;
	List *adj;
	Vetex *next;
};

//图
struct Gragh
{	
	int vNum, eNum;
	Vetex *v;
	int* edgeTo;
};

//添加顶点
void AddVetex(Gragh *g,int val)
{
	Vetex *v = new Vetex;
	Vetex *p = g->v;
	v->val = val;
	v->next = NULL;
	v->adj = NULL;
	v->num = g->vNum;
	for (int i = 0; i < g->vNum - 1; i++)
	{
		if (p->val == val)
		{
			printf_s("该点已存在\n");
			delete(v);
			return;
		}
		p = p->next;
	}
	p->next = v;
	g->vNum += 1;
}


Vetex* GetVertex(Gragh *g, int num)
{
	Vetex *p = g->v;
	while (p!=NULL&&p->num!=num)
	{
		p = p->next;
	}
	return p;
}


Vetex* GetVertexByVal(Gragh *g, int val)
{
	Vetex *p = g->v;
	while (p != NULL && p->val != val)
	{
		p = p->next;
	}
	return p;
}

//添加链接表数据
void Addadj(Vetex *v, int num)
{
	List *l = new List;
	List *p = v->adj;
	l->num = num;
	l->next = NULL;
	if (p == NULL)
	{
		v->adj = l;
		return;
	}
	if (p->num == num)
	{
		printf_s("该边已存在\n");
		return;
	}
	while (p->next!=NULL)
	{
		if (p->num == num)
		{
			printf_s("该边已存在\n");
			return;
		}
		p = p->next;
	}
	p->next = l;
}

//检测链接表数据
bool Checkadj(Vetex *v, int num)
{
	List *p = v->adj;
	if (p == NULL)
		return false;
	if (p->num == num)
		return true;
	while (p->next != NULL)
	{
		p = p->next;
		if (p->num == num)
			return true;
	}
	return false;
}

//添加边
void AddEdge(Gragh *g, int num1, int num2)
{
	Vetex* v1 = GetVertex(g, num1);
	Vetex* v2 = GetVertex(g, num2);
	if (v1 == NULL || v2 == NULL)
		return;
	Addadj(v1, num2);
	Addadj(v2, num1);
	g->eNum++;
}

//检测边
bool CheckEdge(Gragh *g, int num1, int num2)
{
	Vetex* v1 = GetVertex(g, num1);
	Vetex* v2 = GetVertex(g, num2);
	if (v1 == NULL || v2 == NULL)
		return false;
	if (Checkadj(v1, num2) && Checkadj(v2, num1))
		return true;
	return false;
}

//初始化图 以val作为第一个顶点值
Gragh *CreatGragh(int val)
{
	Gragh *g = new Gragh;
	g->eNum = 0;
	g->vNum = 1;
	g->v = new Vetex;
	g->v->val = val;
	g->v->num = 0;
	g->v->next = NULL;
	g->v->adj = NULL;
	return g;
}

//用于Search函数。v为所在点，hasgone储存路径信息，更新edgeTo数组
void DFS(Gragh *g,Vetex *v,bool hasgone[])
{
	//更新hasgone
	hasgone[v->num] = true;
	//检测相邻点
	List *p = v->adj;
	while (p!=NULL)
	{
		//若相邻点没去过，便前往相邻点，否则结束
		if (!hasgone[p->num])
		{
			g->edgeTo[p->num] = v->num;
			DFS(g, GetVertex(g, p->num), hasgone);
		}
		p = p->next;
	}
}

//深度优先搜索，从编号num开始，路径储存于edgeTo数组
void Search(Gragh *g, int num)
{
	g->edgeTo = new int[g->vNum];			//edgeTo数组表示按照深度优先搜索路径当前顶点的上一个顶点num值
	bool* hasgone = new bool[g->vNum];
	for (int i = 0; i < g->vNum; i++)
	{
		hasgone[i] = false;
	}
	DFS(g, GetVertex(g, num), hasgone);
}

//从编号num1到num2的路径
void Path(Gragh *g,int num1, int num2)
{
	//获取DFP路径数组edgeTo
	Search(g, num1);
	//倒序输出(栈:???
	for (int i = num2;; i = g->edgeTo[i])
	{
		//以数值方式输出
		printf_s("%d\n", GetVertex(g, i)->val);
		if (i == num1)
			break;
	}
}


int main()
{
	/*
	Gragh *g=CreatGragh(1);
	AddVetex(g, 2);
	AddVetex(g, 3);
	AddEdge(g, 0, 1);
	AddEdge(g, 0, 2);
	if (CheckEdge(g, 0, 2))
		printf_s("存在该边");
	else
		printf_s("不存在该边");
	*/
	int n;

	printf_s("第一个顶点数值:");
	scanf_s("%d", &n);
	Gragh *g = CreatGragh(n);
	n = 0;
	while (true)
	{
		printf_s("新顶点数值:(负数终止)");
		scanf_s("%d", &n);
		if (n < 0)
			break;
		AddVetex(g, n);
	}
	int i = 0, j = 0;
	while (true)
	{
		printf_s("创造边:(输入数值,负数终止,例:3 4)");
		scanf_s("%d %d", &i, &j);
		if (i < 0 || j < 0)
			break;
		AddEdge(g, GetVertexByVal(g, i)->num, GetVertexByVal(g, j)->num);
	}
	printf_s("路径:(输入数值,例:1 2)");
	scanf_s("%d %d", &i, &j);
	Path(g, GetVertexByVal(g, i)->num, GetVertexByVal(g, j)->num);
	system("pause");
    return 0;
}

 