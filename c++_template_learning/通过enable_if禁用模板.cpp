#include <iostream>
#include <type_traits>

// �� C++11 ��ʼ��ͨ�� C++��׼���ṩ�ĸ���ģ�� std::enable_if<>��������ĳЩ�����������º��Ե�����ģ�塣

// ��һ��
template<typename T>
//typename std::enable_if<(sizeof(T) > 4)>::type // c++ 11
std::enable_if_t<(sizeof(T) > 4)> // c++ 14 
fun( T a )// ��һģ�嶨����� sizeof(T) > 4 ��������ʱ�򱻺��Ե�
{
	std::cout << "test" << std::endl;
}

// Ҳ����˵ std::enable_if<>��һ��������ȡ��type trait�����������һ����Ϊ�䣨��һ����ģ������ı����ڱ��ʽ��������Ϊ:
// 1. ���������ʽ���Ϊ true������ type ��Ա�᷵��һ������:
//		a) ���û�еڶ���ģ����������������� void;
//		b) ����еڶ���ģ�������������������ڶ������������͡�
// 2. ������ʽ��� false�������Ա������δ����ġ�����ģ���һ������ SFINAE ��substitute failure is not an error���Ĺ��� 
// ��ᵼ�°��� std::enable_if<>���ʽ�ĺ���ģ�屻���Ե���

// ����������� std::enable_if<>���� std::enable_if_t<>���ݵڶ���ģ�������
// ��ô�� sizeof(T) > 4 ʱ��enable_if �ᱻ��չ����ڶ���ģ�����
template<typename T>
std::enable_if_t<(sizeof(T) > 4), T>
fun2( T a )
{
	return a;
}

// �������ڽ� enable_if ���ʽ�����������м䲻��һ�����ǵ�������
// ���ʹ�� std::enable_if<> �ĸ������ķ�����ʹ��һ������ġ���Ĭ��ֵ��ģ�������
// ������ʹ��ģ�������
template<typename T, typename RT = std::enable_if_t<(sizeof(T) > 4), T>>
RT fun3(T a)
{
	return a;
}
// ����������ñ���ģ�壨alias template����������һ��������
template<typename T>
using ReturnType = std::enable_if_t < (sizeof(T) > 4), T > ;

template<typename T>
ReturnType<T> fun4(T a) // fun4 �� fun3 һ����ֻ��д����ͬ���ѣ�
{
	return a;
}


int main()
{
	// ��һ��
	double a = 10;
	fun(a); // sizoef(double) = 8,����ʹ�����ģ�庯����

	int b = 10;
	//fun(b);// error C2893: δ��ʹ����ģ�塰enable_if<_Test,_Ty>::type fun(T)��ר�û�;

	// ������
	std::cout << fun2(10.0) << std::endl;

	int d = 10;
	//std::cout << fun2(d) << std::endl; // error C2893: δ��ʹ����ģ�塰enable_if<_Test,T>::type fun2(T)��ר�û�;

	// ������
	double e = 10.0;
	std::cout << fun3(e) << std::endl;// ����÷�������һ����
	

	// 
	double f = 10.0;
	std::cout << fun4(f) << std::endl;

	return 0;
}