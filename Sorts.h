#pragma once
// Sorts.h		�����㷨���
#include <iostream>
#ifndef SORTS_H
#define SORTS_H

struct result	//����һ���ṹ���������ݡ�ͳ�ƱȽϡ���ֵ����
{
	long long comparisons=0, assignments=0;
	result& operator+=(const result &res)	//���������+=�Ա��ڵݹ��д���
	{
		assignments+=res.assignments;
		comparisons+=res.comparisons;
		return *this;
	}
};


template <typename T> void GetMemory(T*& data, T*& data0, int n)	// ������ڴ�ռ䣬ͨ������"����"�׵�ַ
{																	// ����Լ����ָ��ǿվͱ�ʾָ��"ӵ��"�ѿռ���Դ
	if (data0 != nullptr) delete[] data0;								// ���ͷ�ԭ����"ӵ��"�Ķѿռ���Դ
	if (data != nullptr) delete[] data;
	data0 = new T[n];												// ���������µģ���������Ҫ��ģ��ѿռ���Դ
	data = new T[n];
}

template <typename T> void FreeMemory(T*& data, T*& data0)			// �ͷ�ָ����"ӵ��"�Ķѿռ���Դ
{
	if (data0 != nullptr) delete[] data0;
	if (data != nullptr) delete[] data;
	data0 = data = NULL;											// ��һ����ֵ���ǳ���Ҫ������"����Լ��"
}

template <typename T> void ResetData(T* data, const T* data0, int n)	// ���ڻָ�"ԭʼ����"���Ա�֤��ͬ�������㷨������ȫ��ͬ������
{
	for (int i = 0; i < n; i++)
		data[i] = data0[i];
}

template <typename T> bool ValidateData(const T* a, int size)				// ��������Ԫ���Ƿ��Ѱ���������
{
	for (int i = 1; i < size; i++)
		if (a[i - 1] > a[i])
			return false;
	return true;
}

// ���ֻ����ģ�û���Ż��ģ������㷨

template <typename T> void Bubble(T* a, int size)	// û���Ż���ð������
{
	T temp;											// ����һ���ֲ�������������������ʽ����������ͬ
	for (int i = 1; i < size; i++)							// ������ size-1 �ֱȽϺͽ���
	{
		for (int j = 0; j < size - i; j++)
		{
			if (a[j] > a[j + 1])						// ����Ԫ��֮��Ƚϣ���Ҫʱ
			{
				temp = a[j];						// ���� a[j] �� a[j+1]
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
	
}

template <typename T> void Select(T* a, int size)	// û���Ż���ѡ������
{
	T temp;
	int k = 0;
	for (int i = 1; i < size; i++)							// ѭ��size-1��
	{
		for (int j = i; j < size; j++)
			if (a[j] < a[k])
				k = j;								// �ҳ���ǰ��Χ��"��С"Ԫ�ص��±�
		if (k != i - 1)									// ��"��С"Ԫ�ز���a[i-1]���򽻻�֮
		{
			temp = a[k];
			a[k] = a[i - 1];
			a[i - 1] = temp;
		}
		k = i;
	}
}

template <typename T> void Qsort(T* a, int size)	// û���Ż��Ŀ�������
{
	T pivot, temp;
	int left = 0, right = size - 1;						// �±꣨������

	if (size <= 1) return;

	pivot = a[right];								// ѡ�����һ��ֵΪ�ֽ�ֵ
	do
	{
		while (left < right && a[left] <= pivot) left++;	// �˴� "<=" ������ֽ�ֵ��ȵ�Ԫ����ʱ����ԭ��
		while (left < right && a[right] >= pivot)right--;// �˴� ">=" ������ֽ�ֵ��ȵ�Ԫ����ʱ����ԭ��
		if (left < right)
		{
			temp = a[left]; a[left] = a[right]; a[right] = temp;
		}
	} while (left < right);
	a[size - 1] = a[left]; a[left] = pivot;			// �ҵ��ֽ�� left
	Qsort(a, left);									// �ݹ����(��ಿ��)
	Qsort(a + left + 1, size - left - 1);					// �ݹ����(�Ҳಿ��)
	
}

// �����Ż��������㷨

template <typename T> void BubbleImproved(T* a, int size)	// �Ż���ð������
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

template <typename T> void SelectImproved(T* a, int size)	// �Ż���ѡ������
{
	T temp;
	int k=0;
	int i=0,j=size-1;
	while(i<j)
	{
		int min = i, max = j;				//����min��max�ֱ�Ϊ���ֵ����Сֵ���±�
		for(k=i; k<=j; k++)				//�ҳ���ǰ��Χ��"��С"��"���"Ԫ�ص��±�
		{
			if(a[k] < a[min])
				min = k;			
			else if(a[k] > a[max])
				max = k;
		}
		if(min!=i)					// ��"��С"Ԫ�ز���a[i]���򽻻�֮
		{
			temp = a[i];
			a[i] = a[min];
			a[min] = temp;
		}
		if(max==i) max=min;	
		if(max!=j)					// ��"���"Ԫ�ز���a[j]���򽻻�֮
		{
			temp = a[j];
			a[j] = a[max];
			a[max] = temp;
		}
		++i;
		--j;
	}
}

template <typename T> void QsortImproved(T* a, int size)	// �Ż��Ŀ�������
{
	T pivot, temp;
	int left=0, right=size-1 ,mid=size/2-1;// �±꣨������
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
		while(left<right && a[left]<=pivot)left++;	// �˴� "<=" ������ֽ�ֵ��ȵ�Ԫ����ʱ����ԭ��
		while(left<right && a[right]>=pivot)right--;// �˴� ">=" ������ֽ�ֵ��ȵ�Ԫ����ʱ����ԭ��
		if(left < right)
		{
			temp=a[left]; a[left]=a[right]; a[right]=temp;
		}
	}while(left < right);
	a[size-1] = a[left]; a[left] = pivot;			// �ҵ��ֽ�� left
	QsortImproved(a, left);									// �ݹ����(��ಿ��)
	QsortImproved(a+left+1, size-left-1);					// �ݹ����(�Ҳಿ��)
}


//*********����Ϊ���Ը�ֵ���Ƚϴ���ר�ú���*********


template <typename T> result BubbleC(T* a, int size)	// û���Ż���ð������
{
	T temp;											// ����һ���ֲ�������������������ʽ����������ͬ
	result res;
	for (int i = 1; i < size; i++)							// ������ size-1 �ֱȽϺͽ���
	{
		for (int j = 0; j < size - i; j++)
		{
			res.comparisons++;
			if (a[j] > a[j + 1])						// ����Ԫ��֮��Ƚϣ���Ҫʱ
			{
				temp = a[j];						// ���� a[j] �� a[j+1]
				a[j] = a[j + 1];
				a[j + 1] = temp;
				res.assignments+=3;
			}
		}
	}
	return res;
}

template <typename T> result SelectC(T* a, int size)	// û���Ż���ѡ������
{
	T temp;
	int k = 0;
	result res;
	for (int i = 1; i < size; i++)							// ѭ��size-1��
	{
		for (int j = i; j < size; j++)
		{
			res.comparisons++;
			if (a[j] < a[k])
			{
				k = j;
			}
		}
											// �ҳ���ǰ��Χ��"��С"Ԫ�ص��±�
		if (k != i - 1)									// ��"��С"Ԫ�ز���a[i-1]���򽻻�֮
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

template <typename T> result QsortC(T* a, int size)	// û���Ż��Ŀ�������
{
	T pivot, temp;
	int left = 0, right = size - 1;						// �±꣨������
	result res;
	if (size <= 1) return res;

	pivot = a[right];								// ѡ�����һ��ֵΪ�ֽ�ֵ
	do
	{
		res.comparisons+=2;
		while (left < right && (res.comparisons++,a[left] <= pivot)) 
		{
			left++;	// �˴� "<=" ������ֽ�ֵ��ȵ�Ԫ����ʱ����ԭ��
			res.comparisons++;
			}
		while (left < right && (res.comparisons++,a[right] >= pivot))
		{
			right--;// �˴� ">=" ������ֽ�ֵ��ȵ�Ԫ����ʱ����ԭ��
			res.comparisons++;
		}
		if (left < right)
		{
			temp = a[left]; a[left] = a[right]; a[right] = temp;
			res.assignments+=3;
		}
	} while (left < right);
	a[size - 1] = a[left]; a[left] = pivot;			// �ҵ��ֽ�� left
	res.assignments+=2;
	res+=QsortC(a, left);									// �ݹ����(��ಿ��)
	res+=QsortC(a + left + 1, size - left - 1);					// �ݹ����(�Ҳಿ��)
	return res;
}

template <typename T> result BubbleImprovedC(T* a, int size)	// �Ż���ð������
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

template <typename T> result SelectImprovedC(T* a, int size)	// �Ż���ѡ������
{
	T temp;
	result res;
	int k=0;
	int i=0,j=size-1;
	while(i<j)
	{
		int min = i, max = j;				//����min��max�ֱ�Ϊ���ֵ����Сֵ���±�
		for(k=i; k<=j; k++)				//�ҳ���ǰ��Χ��"��С"��"���"Ԫ�ص��±�
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
		if(min!=i)					// ��"��С"Ԫ�ز���a[i]���򽻻�֮
		{
			temp = a[i];
			a[i] = a[min];
			a[min] = temp;
			res.assignments+=3;
		}
		if(max==i) max=min;	
		if(max!=j)					// ��"���"Ԫ�ز���a[j]���򽻻�֮
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

template <typename T> result QsortImprovedC(T* a, int size)	// �Ż��Ŀ�������
{
	result res;
	T pivot, temp;
	int left=0, right=size-1 ,mid=size/2-1;// �±꣨������
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
			left++;	// �˴� "<=" ������ֽ�ֵ��ȵ�Ԫ����ʱ����ԭ��
		}
		
		while(left<right && (res.comparisons++,a[right]>=pivot)){
			right--;// �˴� ">=" ������ֽ�ֵ��ȵ�Ԫ����ʱ����ԭ��
		}
		if(left < right)
		{
			temp=a[left]; a[left]=a[right]; a[right]=temp;
			res.assignments+=3;
		}
	}while(left < right);
	a[size-1] = a[left]; a[left] = pivot;			// �ҵ��ֽ�� left
	res.assignments+=2;
	res+=QsortImprovedC(a, left);									// �ݹ����(��ಿ��)
	res+=QsortImprovedC(a+left+1, size-left-1);					// �ݹ����(�Ҳಿ��)
	return res;
}


#endif
