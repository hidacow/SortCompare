#pragma once
// Sorts.h		排序算法相关
#include <iostream>
#ifndef SORTS_H
#define SORTS_H

struct result	//定义一个结构体用来传递、统计比较、赋值次数
{
	long long comparisons=0, assignments=0;
	result& operator+=(const result &res)	//重载运算符+=以便在递归中传递
	{
		assignments+=res.assignments;
		comparisons+=res.comparisons;
		return *this;
	}
};


template <typename T> void GetMemory(T*& data, T*& data0, int n)	// 分配堆内存空间，通过参数"返回"首地址
{																	// 隐含约定：指针非空就表示指针"拥有"堆空间资源
	if (data0 != nullptr) delete[] data0;								// 先释放原先所"拥有"的堆空间资源
	if (data != nullptr) delete[] data;
	data0 = new T[n];												// 重新申请新的（容量符合要求的）堆空间资源
	data = new T[n];
}

template <typename T> void FreeMemory(T*& data, T*& data0)			// 释放指针所"拥有"的堆空间资源
{
	if (data0 != nullptr) delete[] data0;
	if (data != nullptr) delete[] data;
	data0 = data = NULL;											// 这一条赋值语句非常重要！保持"隐含约定"
}

template <typename T> void ResetData(T* data, const T* data0, int n)	// 用于恢复"原始数据"，以保证不同的排序算法处理完全相同的数据
{
	for (int i = 0; i < n; i++)
		data[i] = data0[i];
}

template <typename T> bool ValidateData(const T* a, int size)				// 检验数组元素是否已按升序排列
{
	for (int i = 1; i < size; i++)
		if (a[i - 1] > a[i])
			return false;
	return true;
}

// 三种基本的（没有优化的）排序算法

template <typename T> void Bubble(T* a, int size)	// 没有优化的冒泡排序
{
	T temp;											// 定义一个局部变量，数据类型与形式数据类型相同
	for (int i = 1; i < size; i++)							// 共进行 size-1 轮比较和交换
	{
		for (int j = 0; j < size - i; j++)
		{
			if (a[j] > a[j + 1])						// 相邻元素之间比较，必要时
			{
				temp = a[j];						// 交换 a[j] 与 a[j+1]
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
	
}

template <typename T> void Select(T* a, int size)	// 没有优化的选择排序
{
	T temp;
	int k = 0;
	for (int i = 1; i < size; i++)							// 循环size-1次
	{
		for (int j = i; j < size; j++)
			if (a[j] < a[k])
				k = j;								// 找出当前范围内"最小"元素的下标
		if (k != i - 1)									// 若"最小"元素不是a[i-1]，则交换之
		{
			temp = a[k];
			a[k] = a[i - 1];
			a[i - 1] = temp;
		}
		k = i;
	}
}

template <typename T> void Qsort(T* a, int size)	// 没有优化的快速排序
{
	T pivot, temp;
	int left = 0, right = size - 1;						// 下标（整数）

	if (size <= 1) return;

	pivot = a[right];								// 选择最后一个值为分界值
	do
	{
		while (left < right && a[left] <= pivot) left++;	// 此处 "<=" 是让与分界值相等的元素暂时留在原地
		while (left < right && a[right] >= pivot)right--;// 此处 ">=" 是让与分界值相等的元素暂时留在原地
		if (left < right)
		{
			temp = a[left]; a[left] = a[right]; a[right] = temp;
		}
	} while (left < right);
	a[size - 1] = a[left]; a[left] = pivot;			// 找到分界点 left
	Qsort(a, left);									// 递归调用(左侧部分)
	Qsort(a + left + 1, size - left - 1);					// 递归调用(右侧部分)
	
}

// 三种优化的排序算法

template <typename T> void BubbleImproved(T* a, int size)	// 优化的冒泡排序
{
	T temp;			
	int j,m=0, e=0,n=size-1;
	for(int i = 1; i<size; i++)							
	{
		int k = 0;
		for(j=e; j<n; j++)
		{
			if(a[j] > a[j+1])						
			{
				temp = a[j];	
				a[j] = a[j+1];
				a[j+1] = temp;
				k=1;
				m=j;
			}
		}
		n=m;
		if(k==0)
			return;
		for(j=n; j>e; j--)
		{
			if(a[j] < a[j-1])		
			{
				temp = a[j];		
				a[j] = a[j-1];
				a[j-1] = temp;
				k=1;
				m=j;
			}
		}
		e=m;
		if(k==0)
			return;
	}
}

template <typename T> void SelectImproved(T* a, int size)	// 优化的选择排序
{
	T temp;
	int k=0;
	int i=0,j=size-1;
	while(i<j)
	{
		int min = i, max = j;				//定义min，max分别为最大值和最小值的下标
		for(k=i; k<=j; k++)				//找出当前范围内"最小"和"最大"元素的下标
		{
			if(a[k] < a[min])
				min = k;			
			else if(a[k] > a[max])
				max = k;
		}
		if(min!=i)					// 若"最小"元素不是a[i]，则交换之
		{
			temp = a[i];
			a[i] = a[min];
			a[min] = temp;
		}
		if(max==i) max=min;	
		if(max!=j)					// 若"最大"元素不是a[j]，则交换之
		{
			temp = a[j];
			a[j] = a[max];
			a[max] = temp;
		}
		++i;
		--j;
	}
}

template <typename T> void QsortImproved(T* a, int size)	// 优化的快速排序
{
	T pivot, temp;
	int left=0, right=size-1 ,mid=size/2-1;// 下标（整数）
	if(size<=1) return;

	if (a[mid] > a[left])
	{
		std::swap(a[mid],a[left]);
	}

	if (a[right] > a[left])
	{
		std::swap(a[right],a[left]);
	}

	if (a[mid] > a[right])
	{
		std::swap(a[mid],a[right]);
	}

	pivot = a[right];
	do
	{
		while(left<right && a[left]<=pivot)left++;	// 此处 "<=" 是让与分界值相等的元素暂时留在原地
		while(left<right && a[right]>=pivot)right--;// 此处 ">=" 是让与分界值相等的元素暂时留在原地
		if(left < right)
		{
			temp=a[left]; a[left]=a[right]; a[right]=temp;
		}
	}while(left < right);
	a[size-1] = a[left]; a[left] = pivot;			// 找到分界点 left
	QsortImproved(a, left);									// 递归调用(左侧部分)
	QsortImproved(a+left+1, size-left-1);					// 递归调用(右侧部分)
}


//*********以下为测试赋值、比较次数专用函数*********


template <typename T> result BubbleC(T* a, int size)	// 没有优化的冒泡排序
{
	T temp;											// 定义一个局部变量，数据类型与形式数据类型相同
	result res;
	for (int i = 1; i < size; i++)							// 共进行 size-1 轮比较和交换
	{
		for (int j = 0; j < size - i; j++)
		{
			res.comparisons++;
			if (a[j] > a[j + 1])						// 相邻元素之间比较，必要时
			{
				temp = a[j];						// 交换 a[j] 与 a[j+1]
				a[j] = a[j + 1];
				a[j + 1] = temp;
				res.assignments+=3;
			}
		}
	}
	return res;
}

template <typename T> result SelectC(T* a, int size)	// 没有优化的选择排序
{
	T temp;
	int k = 0;
	result res;
	for (int i = 1; i < size; i++)							// 循环size-1次
	{
		for (int j = i; j < size; j++)
		{
			res.comparisons++;
			if (a[j] < a[k])
			{
				k = j;
			}
		}
											// 找出当前范围内"最小"元素的下标
		if (k != i - 1)									// 若"最小"元素不是a[i-1]，则交换之
		{
			temp = a[k];
			a[k] = a[i - 1];
			a[i - 1] = temp;
			res.assignments+=3;
		}
		k = i;
	}
	return res;
}

template <typename T> result QsortC(T* a, int size)	// 没有优化的快速排序
{
	T pivot, temp;
	int left = 0, right = size - 1;						// 下标（整数）
	result res;
	if (size <= 1) return res;

	pivot = a[right];								// 选择最后一个值为分界值
	do
	{
		res.comparisons+=2;
		while (left < right && (res.comparisons++,a[left] <= pivot)) 
		{
			left++;	// 此处 "<=" 是让与分界值相等的元素暂时留在原地
			res.comparisons++;
			}
		while (left < right && (res.comparisons++,a[right] >= pivot))
		{
			right--;// 此处 ">=" 是让与分界值相等的元素暂时留在原地
			res.comparisons++;
		}
		if (left < right)
		{
			temp = a[left]; a[left] = a[right]; a[right] = temp;
			res.assignments+=3;
		}
	} while (left < right);
	a[size - 1] = a[left]; a[left] = pivot;			// 找到分界点 left
	res.assignments+=2;
	res+=QsortC(a, left);									// 递归调用(左侧部分)
	res+=QsortC(a + left + 1, size - left - 1);					// 递归调用(右侧部分)
	return res;
}

template <typename T> result BubbleImprovedC(T* a, int size)	// 优化的冒泡排序
{
	result res;
	T temp;			
	int j,m=0, e=0,n=size-1;
	for(int i = 1; i<size; i++)							
	{
		int k = 0;
		for(j=e; j<n; j++)
		{
			res.comparisons++;
			if(a[j] > a[j+1])						
			{
				temp = a[j];	
				a[j] = a[j+1];
				a[j+1] = temp;
				res.assignments+=3;
				k=1;
				m=j;
			}
		}
		n=m;
		if(k==0)
			return res;
		for(j=n; j>e; j--)
		{
			res.comparisons++;
			if(a[j] < a[j-1])		
			{
				temp = a[j];		
				a[j] = a[j-1];
				a[j-1] = temp;
				res.assignments+=3;
				k=1;
				m=j;
			}
		}
		e=m;
		if(k==0)
			return res;
	}
	return res;
}

template <typename T> result SelectImprovedC(T* a, int size)	// 优化的选择排序
{
	T temp;
	result res;
	int k=0;
	int i=0,j=size-1;
	while(i<j)
	{
		int min = i, max = j;				//定义min，max分别为最大值和最小值的下标
		for(k=i; k<=j; k++)				//找出当前范围内"最小"和"最大"元素的下标
		{
			res.comparisons++;
			if(a[k] < a[min])
				min = k;			
			else{
				res.comparisons++;
				if(a[k] > a[max])
					max = k;
			}
		}
		if(min!=i)					// 若"最小"元素不是a[i]，则交换之
		{
			temp = a[i];
			a[i] = a[min];
			a[min] = temp;
			res.assignments+=3;
		}
		if(max==i) max=min;	
		if(max!=j)					// 若"最大"元素不是a[j]，则交换之
		{
			temp = a[j];
			a[j] = a[max];
			a[max] = temp;
			res.assignments+=3;
		}
		++i;
		--j;
	}
	return res;
}

template <typename T> result QsortImprovedC(T* a, int size)	// 优化的快速排序
{
	result res;
	T pivot, temp;
	int left=0, right=size-1 ,mid=size/2-1;// 下标（整数）
	if(size<=1) return res;
	res.comparisons+=3;
	if (a[mid] > a[left])
	{
		std::swap(a[mid],a[left]);
		res.assignments+=3;
	}

	if (a[right] > a[left])
	{
		std::swap(a[right],a[left]);
		res.assignments+=3;
	}

	if (a[mid] > a[right])
	{
		std::swap(a[mid],a[right]);
		res.assignments+=3;
	}

	pivot = a[right];
	do
	{
		while(left<right && (res.comparisons++,a[left]<=pivot)){
			left++;	// 此处 "<=" 是让与分界值相等的元素暂时留在原地
		}
		
		while(left<right && (res.comparisons++,a[right]>=pivot)){
			right--;// 此处 ">=" 是让与分界值相等的元素暂时留在原地
		}
		if(left < right)
		{
			temp=a[left]; a[left]=a[right]; a[right]=temp;
			res.assignments+=3;
		}
	}while(left < right);
	a[size-1] = a[left]; a[left] = pivot;			// 找到分界点 left
	res.assignments+=2;
	res+=QsortImprovedC(a, left);									// 递归调用(左侧部分)
	res+=QsortImprovedC(a+left+1, size-left-1);					// 递归调用(右侧部分)
	return res;
}


#endif
