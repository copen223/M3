// Sort.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>



void Merge(int a[], int left, int mid, int right)
{
	//归并辅助数组
	int n = right - left + 1;
	int* b = new int[n];
	//指针
	int i, j;
	i = left;
	j = mid + 1;

	for (int k = 0; k < n; k++)
	{
		if (a[i] < a[j])
		{
			b[k] = a[i];
			i++;
		}
		else
		{
			b[k] = a[j];
			j++;
		}

		if (i > mid)
		{
			for (; j <= right;j++)
			{
				k++;
				b[k] = a[j];
			}
			break;
		}
		if (j > right)
		{
			for (; i <= mid;i++)
			{
				k++;
				b[k] = a[i];
			}
			break;
		}
	}

	for (int k = left; k <= right; k++)
	{
		a[k] = b[k-left];
	}
}

void Sort(int a[], int i, int j)
{
	if (i >= j)
		return;
	int mid = i + (j - i) / 2;
	Sort(a, i, mid);
	Sort(a, mid + 1, j);
	Merge(a, i, mid, j);

}

int FirstSort(int a[], int left, int right)
{
	//指针
	int i, j, v, t;
	i = left;
	j = right;
	v = a[left];
	while (i < j)
	{
		//左右指针移动至比v大及比v小的数位置
		//先移动右指针，因为参照数是左边第一位。
		//最终交换参照数和j位置，此时的j位置应为小于参照数的数。
		//先右移，那么是j--操作造成j=i，此时i所在位置绝对是小于参照数的（前一次循环交换了i,j数），所以满足第三条。
		//先左移，那么是i++操作造成j=i，此时i所在位置不一定小于参照数，所以j也不小于参照数,所以不满足第三条。
		while (v < a[j] && i<j)
		{
			j--;
		}
		//<=是因为参照数在左侧
		while (a[i] <= v && i<j)
		{
			i++;
		}

		t = a[i];
		a[i] = a[j];
		a[j] = t;
	}
	t = a[j];
	a[j] = a[left];
	a[left] = t;
	return j;
}

void QuickSort(int a[], int i, int j)
{
	if (i >= j)
		return;
	int mid = FirstSort(a, i, j);
	
	QuickSort(a, i, mid - 1);
	QuickSort(a, mid + 1, j);
}


void main()
{
	int n;
	scanf_s("%d", &n);
	int *a = new int[n];
	for (int i = 0; i < n; i++)
	{
		scanf_s("%d", &a[i]);
	}
	//递归排序
	//Sort(a, 0, n-1);
	//快速排序
	QuickSort(a, 0, n - 1);
	for (int i = 0; i < n; i++)
	{
		printf_s("%d ", a[i]);
	}
	system("pause");
}



