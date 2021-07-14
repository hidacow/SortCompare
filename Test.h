#pragma once
#include <cmath>


double timer(bool isRestart);

class DataCreator	//��������������
{
public:

	int seed;
	DataCreator(int s=123):seed(s)	//Constructor����ʼ����������ӣ��Ա㸴������
	{
		srand(seed);	//�������������
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
