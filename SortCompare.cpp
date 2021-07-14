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
	DataCreator d(seed);	//创建一个对象
	switch (flag)	//按不同的Flag生成数据
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

template <typename T> void TestData(const T &x)					// 生成数据
{
	T* data0 = nullptr, * data = nullptr;								// 两个指针初始化为NULL非常重要！
	string InitConf[] = { "完全逆序","大体逆序","完全顺序","大体顺序" ,"完全相等","大体相等",
						"随机(均匀分布)", "随机(正态分布)", "抖动","末尾随机"};		//C++字符串数组，用于储存数据特点

	cout<<endl<<"\t*** 测试数据 ***"<<endl;
	cout<<"种子："<<x<<endl;
	cout<<endl<<string(10,'-')<<"变量类型"<<typeid(T).name()<<string(10,'-')<<endl;
	
	for(int j = 0; j<=9; j++)									// 数据分布类型
	{
		cout << endl<< "数据特点: " << InitConf[j]  << endl;
		//for(int n = 16; n<=128; n*=2)
		for(int n = 1024; n<=65536; n*=2)	
		{
			GetMemory(data, data0, n);						// 申请分配堆空间
			InitData(data0, n, j,x);							// 设置原始数据
			cout << n << '\t';
			for(int i=0;i<n-1;i++)
			{
				cout<<data0[i]<<",";							//写测试数据
			}
			cout <<data0[n-1]<< endl;
			FreeMemory(data, data0);						// 释放堆空间资源，并使指针为空
			
		}
	}
}

template <typename T> void TestSort(const T &x)					// x作为随机数种子传递
{
	T* data0 = nullptr, * data = nullptr;								// 两个指针初始化为NULL非常重要！
	string InitConf[] = { "完全逆序","大体逆序","完全顺序","大体顺序" ,"完全相等","大体相等",
						"随机(均匀分布)", "随机(正态分布)", "抖动","末尾随机"};		//C++字符串数组，用于储存数据特点
	string algo[] ={"冒泡","冒泡优化", "选择", "选择优化", "快速","快速优化" };
	void (*f[])(T*, int) = { Bubble, BubbleImproved, Select, SelectImproved, Qsort ,QsortImproved};	// 函数指针数组（元素为一系列函数的入口地址）
	int i, m = sizeof(f) / sizeof(*f);					// m为函数指针数组f的元素个数（此处有6个函数指针，分别指向6个排序函数的入口地址）
	bool flag[20];											// 这里认为：常量20足够大于变量 m。记录不同算法执行的正确性
	double t[20];											// 同上。记录不同算法的执行时间
	map<string,string>identities;									// 特征字典
	
	cout<<endl<<string(10,'-')<<"变量类型"<<typeid(T).name()<<string(10,'-')<<endl;
	
	for(int j = 0; j<=9; j++)									// 数据分布类型
	{
		cout << endl<< "数据特点: " << InitConf[j]  << endl;
		
		for(i=0; i<m; i++)cout << '\t' << algo[i];
		cout << endl;
		for(int n = 1024; n<=65536; n*=2)
		{
			GetMemory(data, data0, n);						// 申请分配堆空间
			InitData(data0, n, j,x);							// 设置原始数据
			cout << n;
			for(i=0; i<m; i++)
			{
				string identity;
				ResetData(data, data0, n);						// 恢复原始数据
				timer(true);									// 设置计时起点
				f[i](data, n);								// 第 i 种排序算法
				t[i]=timer(false);				// 返回从计时起点到目前所经历的时间（秒）
				flag[i]=ValidateData(data, n);					// 检验排序的正确性
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
				if(identities.size()==1)cout<<"全部正确，数据为"<<identities.begin()->first<<"...";
				else{
					cout<<"满足升序，但数据不一致，请检查算法"<<endl;
					for(const auto &k :identities)cout<<k.first<<"...:算法"<<k.second<<endl;
				}
			}else
			{
				cout<<"部分数据不满足升序：算法"<<tmp2<<endl;
			}
			identities.clear();			
			cout << endl;
			FreeMemory(data, data0);						// 释放堆空间资源，并使指针为空
			
		}
	}
}

template <typename T> void TestSortCompAssign(const T &x)					//测试赋值、比较次数专用函数
{
	T* data0 = nullptr, * data = nullptr;								// 两个指针初始化为NULL非常重要！
	string InitConf[] = { "完全逆序","大体逆序","完全顺序","大体顺序" ,"完全相等","大体相等",
						"随机(均匀分布)", "随机(正态分布)", "抖动","末尾随机"};		//C++字符串数组，用于储存数据特点
	string algo[] ={"冒泡","冒泡优化", "选择", "选择优化", "快速","快速优化" };
	result (*f[])(T*, int) = { BubbleC, BubbleImprovedC, SelectC, SelectImprovedC, QsortC ,QsortImprovedC};	// 函数指针数组（元素为一系列函数的入口地址）
	int i, m = sizeof(f) / sizeof(*f);					// m为函数指针数组f的元素个数（此处有6个函数指针，分别指向6个排序函数的入口地址）
	
	cout<<endl<<"\t*** 测试元素间比较、赋值次数 ***";
	cout<<endl<<string(10,'-')<<"变量类型"<<typeid(T).name()<<string(10,'-')<<endl;
	
	for(int j = 0; j<=9; j++)									// 数据分布类型
	{
		cout << endl<< "数据特点: " << InitConf[j]  << endl;
		
		for(i=0; i<m; i++)cout << '\t' << algo[i];
		cout << endl;
		for(int n = 1024; n<=65536; n*=2)
		{
			GetMemory(data, data0, n);						// 申请分配堆空间
			InitData(data0, n, j,x);							// 设置原始数据
			cout << n;
			for(i=0; i<m; i++)
			{
				
				ResetData(data, data0, n);						// 恢复原始数据
				
				result a=f[i](data, n);								// 第 i 种排序算法
				cout << '\t' << "比较"<<a.comparisons<<",赋值"<<a.assignments;
			}	
			cout << endl;
			FreeMemory(data, data0);						// 释放堆空间资源，并使指针为空
		}
	}
}

int main() {
	
	
	//int seed=time(NULL);		//随机产生种子

	//以下为测试函数样例，可选择执行
	
	if(isTestSortInt)			TestSort(int(SEED));	//测试排序算法，数据类型int
	if(isTestCompAssignInt)		TestSortCompAssign(int(SEED));	//元素间比较、赋值次数计数
	
	if(isTestSortDouble)		TestSort(double(SEED));	//测试排序算法，数据类型double
	if(isTestCompAssignDouble)	TestSortCompAssign(double(SEED));	//元素间比较、赋值次数计数
	
	if(isTestScore)				TestScore();	//测试结构体
	if(isTestString)			TestString();	//思考题
	
	if(GenerateDataInt)			TestData(int(SEED));		//生成数据类型为int的原始数据
	if(GenerateDataDouble)		TestData(double(SEED));		//生成数据类型为int的原始数据

	

    return 0;
}