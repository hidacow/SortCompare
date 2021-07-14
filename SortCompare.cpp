#include <iostream>
#include "Test.h"
#include  "score.h"
#include "Sorts.h"
#include <map>
#include <string>
#include "SortCompare.h"
using namespace std;


template <typename T> void InitData(T* data, int n, int flag,int seed=123)
{
	DataCreator d(seed);	//����һ������
	switch (flag)	//����ͬ��Flag��������
	{
		int i;
	default:
	case 0: for (i = 0; i < n; i++) data[i] = (T)d.Descending(i, n);	break;	
	case 1: for (i = 0; i < n; i++) data[i] = (T)d.MostlyDescending(i,n);break;
	case 2:	for (i = 0; i < n; i++) data[i] = (T)d.Ascending(i,n);break;
	case 3: for (i = 0; i < n; i++) data[i] = (T)d.MostlyAscending(i,n);break;
	case 4: for (i = 0; i < n; i++) data[i] = (T)d.Equal(i,n);break;
	case 5: for (i = 0; i < n; i++) data[i] = (T)d.MostlyEqual(i,n);break;
	case 6: for (i = 0; i < n; i++) data[i] = (T)d.Random(i,n); break;	
	case 7: for (i = 0; i < n; i++) data[i] = (T)d.Gauss(i,n); break;	
	case 8: for (i = 0; i < n; i++) data[i] = (T)d.Jittered(i,n);break;
	case 9: for (i = 0; i < n; i++) data[i] = (T)d.Append(i,n);break;
	}
}

template <typename T> void TestData(const T &x)					// ��������
{
	T* data0 = nullptr, * data = nullptr;								// ����ָ���ʼ��ΪNULL�ǳ���Ҫ��
	string InitConf[] = { "��ȫ����","��������","��ȫ˳��","����˳��" ,"��ȫ���","�������",
						"���(���ȷֲ�)", "���(��̬�ֲ�)", "����","ĩβ���"};		//C++�ַ������飬���ڴ��������ص�

	cout<<endl<<"\t*** �������� ***"<<endl;
	cout<<"���ӣ�"<<x<<endl;
	cout<<endl<<string(10,'-')<<"��������"<<typeid(T).name()<<string(10,'-')<<endl;
	
	for(int j = 0; j<=9; j++)									// ���ݷֲ�����
	{
		cout << endl<< "�����ص�: " << InitConf[j]  << endl;
		//for(int n = 16; n<=128; n*=2)
		for(int n = 1024; n<=65536; n*=2)	
		{
			GetMemory(data, data0, n);						// �������ѿռ�
			InitData(data0, n, j,x);							// ����ԭʼ����
			cout << n << '\t';
			for(int i=0;i<n-1;i++)
			{
				cout<<data0[i]<<",";							//д��������
			}
			cout <<data0[n-1]<< endl;
			FreeMemory(data, data0);						// �ͷŶѿռ���Դ����ʹָ��Ϊ��
			
		}
	}
}

template <typename T> void TestSort(const T &x)					// x��Ϊ��������Ӵ���
{
	T* data0 = nullptr, * data = nullptr;								// ����ָ���ʼ��ΪNULL�ǳ���Ҫ��
	string InitConf[] = { "��ȫ����","��������","��ȫ˳��","����˳��" ,"��ȫ���","�������",
						"���(���ȷֲ�)", "���(��̬�ֲ�)", "����","ĩβ���"};		//C++�ַ������飬���ڴ��������ص�
	string algo[] ={"ð��","ð���Ż�", "ѡ��", "ѡ���Ż�", "����","�����Ż�" };
	void (*f[])(T*, int) = { Bubble, BubbleImproved, Select, SelectImproved, Qsort ,QsortImproved};	// ����ָ�����飨Ԫ��Ϊһϵ�к�������ڵ�ַ��
	int i, m = sizeof(f) / sizeof(*f);					// mΪ����ָ������f��Ԫ�ظ������˴���6������ָ�룬�ֱ�ָ��6������������ڵ�ַ��
	bool flag[20];											// ������Ϊ������20�㹻���ڱ��� m����¼��ͬ�㷨ִ�е���ȷ��
	double t[20];											// ͬ�ϡ���¼��ͬ�㷨��ִ��ʱ��
	map<string,string>identities;									// �����ֵ�
	
	cout<<endl<<string(10,'-')<<"��������"<<typeid(T).name()<<string(10,'-')<<endl;
	
	for(int j = 0; j<=9; j++)									// ���ݷֲ�����
	{
		cout << endl<< "�����ص�: " << InitConf[j]  << endl;
		
		for(i=0; i<m; i++)cout << '\t' << algo[i];
		cout << endl;
		for(int n = 1024; n<=65536; n*=2)
		{
			GetMemory(data, data0, n);						// �������ѿռ�
			InitData(data0, n, j,x);							// ����ԭʼ����
			cout << n;
			for(i=0; i<m; i++)
			{
				string identity;
				ResetData(data, data0, n);						// �ָ�ԭʼ����
				timer(true);									// ���ü�ʱ���
				f[i](data, n);								// �� i �������㷨
				t[i]=timer(false);				// ���شӼ�ʱ��㵽Ŀǰ��������ʱ�䣨�룩
				flag[i]=ValidateData(data, n);					// �����������ȷ��
				cout << '\t' << t[i];
				for(int k=0;k<=4;k++)identity+= to_string(data[k]) + ",";
				identities[identity] += to_string(i);
				
			}
			cout<<"\t";
			bool tmp=true;
			string tmp2;
			for(i=0; i<m; i++)if(!flag[i]){tmp=false;tmp2+=to_string(i);}
			if(tmp)
			{
				if(identities.size()==1)cout<<"ȫ����ȷ������Ϊ"<<identities.begin()->first<<"...";
				else{
					cout<<"�������򣬵����ݲ�һ�£������㷨"<<endl;
					for(const auto &k :identities)cout<<k.first<<"...:�㷨"<<k.second<<endl;
				}
			}else
			{
				cout<<"�������ݲ����������㷨"<<tmp2<<endl;
			}
			identities.clear();			
			cout << endl;
			FreeMemory(data, data0);						// �ͷŶѿռ���Դ����ʹָ��Ϊ��
			
		}
	}
}

template <typename T> void TestSortCompAssign(const T &x)					//���Ը�ֵ���Ƚϴ���ר�ú���
{
	T* data0 = nullptr, * data = nullptr;								// ����ָ���ʼ��ΪNULL�ǳ���Ҫ��
	string InitConf[] = { "��ȫ����","��������","��ȫ˳��","����˳��" ,"��ȫ���","�������",
						"���(���ȷֲ�)", "���(��̬�ֲ�)", "����","ĩβ���"};		//C++�ַ������飬���ڴ��������ص�
	string algo[] ={"ð��","ð���Ż�", "ѡ��", "ѡ���Ż�", "����","�����Ż�" };
	result (*f[])(T*, int) = { BubbleC, BubbleImprovedC, SelectC, SelectImprovedC, QsortC ,QsortImprovedC};	// ����ָ�����飨Ԫ��Ϊһϵ�к�������ڵ�ַ��
	int i, m = sizeof(f) / sizeof(*f);					// mΪ����ָ������f��Ԫ�ظ������˴���6������ָ�룬�ֱ�ָ��6������������ڵ�ַ��
	
	cout<<endl<<"\t*** ����Ԫ�ؼ�Ƚϡ���ֵ���� ***";
	cout<<endl<<string(10,'-')<<"��������"<<typeid(T).name()<<string(10,'-')<<endl;
	
	for(int j = 0; j<=9; j++)									// ���ݷֲ�����
	{
		cout << endl<< "�����ص�: " << InitConf[j]  << endl;
		
		for(i=0; i<m; i++)cout << '\t' << algo[i];
		cout << endl;
		for(int n = 1024; n<=65536; n*=2)
		{
			GetMemory(data, data0, n);						// �������ѿռ�
			InitData(data0, n, j,x);							// ����ԭʼ����
			cout << n;
			for(i=0; i<m; i++)
			{
				
				ResetData(data, data0, n);						// �ָ�ԭʼ����
				
				result a=f[i](data, n);								// �� i �������㷨
				cout << '\t' << "�Ƚ�"<<a.comparisons<<",��ֵ"<<a.assignments;
			}	
			cout << endl;
			FreeMemory(data, data0);						// �ͷŶѿռ���Դ����ʹָ��Ϊ��
		}
	}
}

int main() {
	
	
	//int seed=time(NULL);		//�����������

	//����Ϊ���Ժ�����������ѡ��ִ��
	
	if(isTestSortInt)			TestSort(int(SEED));	//���������㷨����������int
	if(isTestCompAssignInt)		TestSortCompAssign(int(SEED));	//Ԫ�ؼ�Ƚϡ���ֵ��������
	
	if(isTestSortDouble)		TestSort(double(SEED));	//���������㷨����������double
	if(isTestCompAssignDouble)	TestSortCompAssign(double(SEED));	//Ԫ�ؼ�Ƚϡ���ֵ��������
	
	if(isTestScore)				TestScore();	//���Խṹ��
	if(isTestString)			TestString();	//˼����
	
	if(GenerateDataInt)			TestData(int(SEED));		//������������Ϊint��ԭʼ����
	if(GenerateDataDouble)		TestData(double(SEED));		//������������Ϊint��ԭʼ����

	

    return 0;
}