#include <iostream>
#include <type_traits>

/* ���� 5 ����ģ������� */

int max(const int& a, const int& b)
{
	std::cout << "no template " << std::endl;
	return a < b ? b : a;
}

// ����һ��һ����ģ�庯�����Ժ�һ������ͬ���ĺ���ģ�干�棬�������ͬ���ĺ���ģ����Ա�ʵ����Ϊ���ģ�庯��������ͬ���͵ĵ��ò�����
// ע�⣺�������������ض���ͬ������£�ģ��������̽�����ѡ���ģ�庯���������Ǵ�ģ��ʵ���������ĺ�����
template<typename T>
T max(const T& a, const T& b) 
{
	std::cout << "template " << std::endl;
	return a < b ? b : a;
}

int main()
{
	// ������õ��Ƿ�ģ�庯��
	std::cout << "max(5, 100) = " << ::max(5, 100) << std::endl << std::endl; 

	// ��ģ������ƶ�ʱ�������Զ�����ת��(����ʽת��)�������溯��������ģ�����������õ�Ҳ�Ƿ�ģ�庯��
	std::cout << "max('a', 100) = " << ::max('a', 100) << std::endl;

	return 0;
}