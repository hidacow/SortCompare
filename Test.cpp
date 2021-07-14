#include <algorithm>
#include <ctime>
#include <iostream>
#include  "MyRand.h"
#include  "Test.h"
using namespace std;


double timer(bool isRestart=false)					// 参数带默认值，非零表示重新计时
{											// 否则累计计时
	const double c = 1.0/CLOCKS_PER_SEC;
	static clock_t t = clock();				// 静态局部变量。第一次调用时，确定计时起点
	if(isRestart) t = clock();				// 根据实参决定是否重新确定计时起点
	return c*(clock()-t);					// 从上一计时点到现在所经历的时间
}


double DataCreator::Random(size_t index, size_t total)	//完全随机
{
	return rand() * (10000.0 / RAND_MAX);
}

double DataCreator::Gauss(size_t index, size_t total)	//正态分布
{
	return GaussRand(1000,4096);
}

double DataCreator::MostlyDescending(size_t index, size_t total)	//大体递减
{
	return total - index + rand() * 1.0 / RAND_MAX * 5 - 2.5;
}

double DataCreator::MostlyAscending(size_t index, size_t total)		//大体递增
{
	return index + rand() * 1.0 / RAND_MAX * 5 - 2.5;
}

double DataCreator::Ascending(size_t index, size_t total)	//顺序
{
	return index;
}

double DataCreator::Descending(size_t index, size_t total)	//逆序
{
	return total - index;
}

double DataCreator::Equal(size_t index, size_t total)	//完全相等
{
	return 1000;
}

double DataCreator::Jittered(size_t index, size_t total)	//小范围抖动，例1,2,3,4,5,6,7,6,5,7,8,9,...
{
	return (rand() * 1.0 / RAND_MAX <= 0.9) ? index : (index - 2);
}

double DataCreator::MostlyEqual(size_t index, size_t total)	//大多数相等
{
	return 1000 + (int)(rand() * 1.0 / RAND_MAX * 4);
}

double DataCreator::Append(size_t index, size_t total)	//在一堆有序数据最后有一些随机数据(占20%)
{
	if (index > total - total / 5) return rand() * 1.0 / RAND_MAX * total;
	return index;
}
