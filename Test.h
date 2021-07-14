#pragma once
#include <cmath>


double timer(bool isRestart);

class DataCreator	//数据生成器对象
{
public:

	int seed;
	DataCreator(int s=123):seed(s)	//Constructor，初始化随机数种子，以便复现数据
	{
		srand(seed);	//设置随机数种子
	}
	
	double Random(size_t index, size_t total);
	
	double Gauss(size_t index, size_t total);
	
	double MostlyDescending(size_t index, size_t total);
	
	double MostlyAscending(size_t index, size_t total);
	
	double Ascending(size_t index, size_t total);
	
	double Descending(size_t index, size_t total);
	
	double Equal(size_t index, size_t total);
	
	double Jittered(size_t index, size_t total);
	
	double MostlyEqual(size_t index, size_t total);

	double Append(size_t index, size_t total);

};
