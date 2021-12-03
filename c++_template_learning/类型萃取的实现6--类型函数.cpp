#include <iostream>

// ��ͳ�������� C �� C++�ﶨ��ĺ������Ա�����ȷ�ĳ�Ϊ:
// ֵ������value functions�������ǽ���һЩֵ��Ϊ����������һ��ֵ��Ϊ����� 
// ����ģ�壬���ǻ����Զ������ͺ�����type functions�������ǽ���һЩ������Ϊ����������һ�����ͻ��߳�����Ϊ�����

// һ�������õ��������ͺ����� sizeof����������һ�������˸������ʹ�С����λ�� byte���ĳ�����
// ��ģ����Ȼ���Ա��������ͺ�������ʱ���ͺ����Ĳ�����ģ���������������ȡΪ��Ա���ͻ��߳�Ա������
// ���磬sizeof ��������Ա���Ϊ���½ӿ��ṩ;

template<typename T> 
struct TypeSize 
{
	static std::size_t const value = sizeof(T);
};

// TypeSize ��һ��ģ�壬 Ҳ���Ա���Ϊ ģ��ģ��������ݡ�

int main() 
{ 
	std::cout << "TypeSize<int>::value = " << TypeSize<int>::value << std::endl;

	return 0;
}

