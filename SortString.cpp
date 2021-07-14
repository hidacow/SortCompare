// SortString.cpp
/* ˼����
1.	����Ĳ��Ժ����У�strA��strB��strC��strD��ϵ��C-�ַ�����������ݴ洢���ڴ��ʲô����
2.	���BubbleA��BubbleB��������֮ǰ��˼��
	(1) ��αȽ������ַ��������ݣ�
	(2) �洢��ʲô������ַ����ܽ��������ݣ�
	(3) �����ܽ����ַ��������ݣ���������н���ʲô��
3.	GetStringsΪʲôҪ��Ƴɺ���ģ�壬���ε���ʱ����ڶ��������ֱ���ʵ������ʲô��
4.	GetStrings��FreeStrings�����ĵ�һ������ΪʲôҪʹ�������Ͳ������ݶ���ָ�룿������������Ͳ���������ʲô�����
*/
#include <iostream>
#include <cstring>
using namespace std;

#define NUM 20

void SwapA(char *a,char*b)
{
	char temp;
	for (int i = 0; i < NUM; i++){	//����ֱ�ӽ���ָ��
		temp=*(a+i);
		*(a+i)=*(b+i);
		*(b+i)=temp;
	}
}

void SwapB(char** a,char** b){
	char* p;
	p=*a;*a=*b;*b=p;
}

//str �൱�� char[12][20]
void BubbleA(char (*str)[NUM], int size)			// ����ָ��
{
	//cout << "����ɺ��� BubbleA �Ķ��壬ִ�����������" << endl;
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (strcmp(str[j], str[j+1]) > 0){
				SwapA(str[j],str[j+1]);
				//��ʹ�ýϸ߰汾�ı���������ֱ��ʹ��std::swap(str[j + 1], str[j]);
			}
		}
	}
}

void BubbleB(char *str[], int size)					// ָ������
{
	//cout << "����ɺ��� BubbleB �Ķ��壬ִ�����������" << endl;
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (strcmp(str[j], str[j+1]) > 0){
				SwapB(&str[j],&str[j+1]);
				//��ʹ�ýϸ߰汾�ı���������ֱ��ʹ��std::swap(str[j + 1], str[j]);
			}

		}
	}
	
}

template <typename T> void ShowStrings(const char *prompt, const T *strs, int n)
{
	if(n>0)
		cout << prompt << strs[0];
	for(int i=1; i<n; i++)
		cout << ", " << strs[i];
	cout << endl;
}

template <typename T> void GetStrings(char **&dest, const T *source, int n)
{
	dest = new char*[n];
	if(dest == NULL) return;
	int len;
	for(int i=0; i<n; i++)
	{
		len = strlen(source[i]);
		dest[i] = new char[len+1];
#ifdef _MSC_VER
		strcpy_s(dest[i],n,source[i]);	//VS
#else
		strcpy(dest[i], source[i]);	//Other Compiler
#endif
	}
}

void FreeStrings(char **&strs, int n)
{
	if(strs!=NULL)
	{
		for(int i=0; i<n; i++)
			if(strs[i]!=NULL)
				delete [] strs[i];
		delete [] strs;
		strs = NULL;
	}
}

void TestString()
{
	char strA[][NUM]={"enter", "number", "size", "begin", "of", "cat", "case", "program", "certain", "a", "cake", "side"};
	char *strB[]    ={"enter", "number", "size", "begin", "of", "cat", "case", "program", "certain", "an", "cake", "side"};
	char **strC, **strD;
	int n1 = sizeof(strA)/sizeof(*strA), n2 = sizeof(strB)/sizeof(*strB);
	GetStrings(strC, strA, n1);
	GetStrings(strD, strB, n2);

	cout << "\n\t*** ���ֲ�ͬ�洢��ʽ��C-�ַ������������ ***" << endl;
	ShowStrings("\nԭʼ����: ", strA, n1);
	BubbleA(strA, n1);
	ShowStrings("������: ",   strA, n1);
	
	ShowStrings("\nԭʼ����: ", strB, n2);
	BubbleB(strB, n2);
	ShowStrings("������: ",   strB, n2);
	
	ShowStrings("\nԭʼ����: ", strC, n1);
	BubbleB(strC, n1);						// ����һ��������ָ���������
	ShowStrings("������: ",   strC, n1);

	ShowStrings("\nԭʼ����: ", strD, n2);
	BubbleB(strD, n2);						// ����һ��������ָ���������
	ShowStrings("������: ",   strD, n2);

	FreeStrings(strC, n1);
	FreeStrings(strD, n2);
	//return 0;
}
