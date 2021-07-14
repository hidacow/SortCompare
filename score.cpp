// Score.cpp
#include "MyRand.h"
#include "score.h"
#include "Sorts.h"
#include "Test.h"
#include <iostream>
#include <cstdio>
#include <typeinfo>
using namespace std;

void InitScore(Score *data, int n)
{
	const double variance=6*6;
	const double mean=72;
	for(int i=0; i<n; i++)
	{
		
#ifdef _MSC_VER
		sprintf_s(data[i].Id, "%08d", i+1);	// ����ѧ sprintf ��������ע�⣺ԭʼ�����У�ѧ������ȫ˳�����еģ�
#else
		sprintf(data[i].Id, "%08d", i+1);	// ����ѧ sprintf ��������ע�⣺ԭʼ�����У�ѧ������ȫ˳�����еģ�
#endif
		
		data[i].Total  = data[i].Chinese   = int(0.5+GaussRand(mean, variance));	// ��0.5��ȡ����С������"��������"
		data[i].Total += data[i].Math      = int(0.5+GaussRand(mean, variance));
		data[i].Total += data[i].English   = int(0.5+GaussRand(mean, variance));
		data[i].Total += data[i].Physics   = int(0.5+GaussRand(mean, variance));
		data[i].Total += data[i].Chemistry = int(0.5+GaussRand(mean, variance));
	}
}

void ShowScore(const Score *data, int size, int last)
{
	int m;
	if(last<=0 || last>=size)
		m = 0;								// ��������
	else
		m = size-last;						// ���last������
	cout << "\t��������������ݣ����ܷ�ǰ�����������ݣ�" << endl;
	cout << "\t ѧ ��  �ܷ� �� �� �� �� ��" << endl;
	for(int i=size-1; i>=m; i--)
		cout << '\t' << data[i].Id << ' ' << data[i].Total << ' '
			 << data[i].Chinese << ' ' << data[i].Math << ' '
			 << data[i].English << ' ' << data[i].Physics << ' '
			 << data[i].Chemistry << endl;
}

void TestScore()
{
	Score *data0=NULL, *data=NULL;							// ����ָ���ʼ��ΪNULL�ǳ���Ҫ��
	string algo[] ={"ð��","ð��(��)", "ѡ��", "ѡ��(��)", "����","����(��)" };
	void (*f[])(Score*, int) = { Bubble, BubbleImproved, Select, SelectImproved, Qsort ,QsortImproved};	// ����ָ�����飨Ԫ��Ϊһϵ�к�������ڵ�ַ��
	
	int m = sizeof(f)/sizeof(*f);						// mΪ����ָ������f��Ԫ�ظ������˴���3������ָ�룬�ֱ�ָ��3������������ڵ�ַ��

	cout << "\nԭʼ���ݷֲ�: ��̬�ֲ�, �������� = " << typeid(Score).name() << endl;
	for(int n = 1024; n<=65536; n*=2)
	{
		GetMemory(data, data0, n);							// �������ѿռ�
		InitScore(data0, n);								// ����ԭʼ����
		for(int i=0; i<m; i++)
		{
			ResetData(data, data0, n);							// �ָ�ԭʼ����
			timer(true);										// ���ü�ʱ���
			f[i](data, n);									// �� i �������㷨
			double t = timer(false);									// ���شӼ�ʱ��㵽Ŀǰ��������ʱ�䣨�룩
			bool flag = ValidateData(data, n);							// �����������ȷ��
			cout << n << '\t' << t << '\t' << algo[i] << (flag?": ��ȷ":": ����") << endl;
			ShowScore(data, n, 10);							// ����������10����ڰ��������У���߷ֵ�һ�������
		}
		FreeMemory(data, data0);							// �ͷŶѿռ���Դ����ʹָ��Ϊ��
	}
}
