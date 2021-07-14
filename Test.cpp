#include <algorithm>
#include <ctime>
#include <iostream>
#include  "MyRand.h"
#include  "Test.h"
using namespace std;


double timer(bool isRestart=false)					// ������Ĭ��ֵ�������ʾ���¼�ʱ
{											// �����ۼƼ�ʱ
	const double c = 1.0/CLOCKS_PER_SEC;
	static clock_t t = clock();				// ��̬�ֲ���������һ�ε���ʱ��ȷ����ʱ���
	if(isRestart) t = clock();				// ����ʵ�ξ����Ƿ�����ȷ����ʱ���
	return c*(clock()-t);					// ����һ��ʱ�㵽������������ʱ��
}


double DataCreator::Random(size_t index, size_t total)	//��ȫ���
{
	return rand() * (10000.0 / RAND_MAX);
}

double DataCreator::Gauss(size_t index, size_t total)	//��̬�ֲ�
{
	return GaussRand(1000,4096);
}

double DataCreator::MostlyDescending(size_t index, size_t total)	//����ݼ�
{
	return total - index + rand() * 1.0 / RAND_MAX * 5 - 2.5;
}

double DataCreator::MostlyAscending(size_t index, size_t total)		//�������
{
	return index + rand() * 1.0 / RAND_MAX * 5 - 2.5;
}

double DataCreator::Ascending(size_t index, size_t total)	//˳��
{
	return index;
}

double DataCreator::Descending(size_t index, size_t total)	//����
{
	return total - index;
}

double DataCreator::Equal(size_t index, size_t total)	//��ȫ���
{
	return 1000;
}

double DataCreator::Jittered(size_t index, size_t total)	//С��Χ��������1,2,3,4,5,6,7,6,5,7,8,9,...
{
	return (rand() * 1.0 / RAND_MAX <= 0.9) ? index : (index - 2);
}

double DataCreator::MostlyEqual(size_t index, size_t total)	//��������
{
	return 1000 + (int)(rand() * 1.0 / RAND_MAX * 4);
}

double DataCreator::Append(size_t index, size_t total)	//��һ���������������һЩ�������(ռ20%)
{
	if (index > total - total / 5) return rand() * 1.0 / RAND_MAX * total;
	return index;
}
