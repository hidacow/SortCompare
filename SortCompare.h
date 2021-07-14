#pragma once


//数据设置
#define SEED 123	//随机数种子，用以产生相同数据

void TestString();			// 函数原型，用于声明
//测试项目

#define isTestSortInt			true	//测试排序算法，数据类型int
#define isTestCompAssignInt		true	//测试元素间比较、赋值次数计数(int)

#define isTestSortDouble		true	//测试排序算法，数据类型double
#define isTestCompAssignDouble	false	//测试元素间比较、赋值次数计数(double)

#define isTestScore				true	//测试排序分数(结构体)
#define isTestString			true	//思考题(SortString)

#define GenerateDataInt			false	//生成测试数据(int)
#define GenerateDataDouble		false	//生成测试数据(double)
