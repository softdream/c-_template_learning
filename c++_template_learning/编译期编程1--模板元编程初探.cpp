#include <iostream>

// ģ���ʵ���������ڱ����ڼ䣨����̬���Եķ������ڳ��������ڼ�����ģ���
// ��ʵ֤�� C++ģ���ĳЩ���Կ��Ժ�ʵ�����������ϣ������Ͳ�����һ�� C++�Լ��ڲ���ԭʼ�ݹ�ġ�������ԡ���
// ���ģ���������������һ������Ľ����;

// ��һ��c++11��ǰ�﷨ʵ�ֱ���������--�ж�����
template<unsigned p, unsigned d> // p: number to check, d: current divisor
struct DoIsPrime {
	static constexpr bool value = (p % d != 0) && DoIsPrime<p, d - 1>::value; // �ݹ�
};

template<unsigned p> // end recursion if divisor is 2 
struct DoIsPrime<p,2> { 
	static constexpr bool value = (p % 2 != 0); 
};

template<unsigned p> // primary template 
struct IsPrime { // start recursion with divisor from p/2: 
	static constexpr bool value = DoIsPrime<p, p / 2>::value; 
};

// special cases (to avoid endless recursion with template instantiation): 
template<> struct IsPrime<0> { 
	static constexpr bool value = false; 
}; 
template<> struct IsPrime<1> { 
	static constexpr bool value = false; 
}; 
template<> struct IsPrime<2> { 
	static constexpr bool value = true;
}; 
template<> struct IsPrime<3> { 
	static constexpr bool value = true;
};

// C++11 ������һ������ constexpr �������ԣ��������˸������͵ı����ڼ��㡣
// ��������˺��ʵ����룬constexpr �����Ϳ����ڱ����ڼ������Ӧ�ļ��㣻
// �������� C++11 �У��ж�һ�����ǲ���������ʵ�ַ�ʽ����

constexpr bool doIsPrime1(unsigned p, unsigned d) // p: number to check, d: current divisor
{
	return d != 2 
		? (p % d != 0) && doIsPrime1(p, d - 1) // check this and smaller divisors
		: (p % 2!=0); // end recursion if divisor is 2 
}
constexpr bool isPrime1(unsigned p)
{
	return p < 4 ? !(p < 2) // handle special cases
		: doIsPrime1(p,p / 2); // start recursion with divisor from p/2
}

// �� C++14 �У�constexpr ��������ʹ�ó��� C++�����д󲿷ֵĿ��ƽṹ;
// ע�� vs2015 û��ʵ���� c++14 ������
/*constexpr bool isPrime(unsigned int p) 
{
	for (unsigned int d = 2; d <= p / 2; ++d) {
		if (p % d == 0) {
			return false; // found divisor without remainder}
		}
	}
	return p > 1; // no divisor without remainder found
}*/

int main()
{
	IsPrime<56>::value; // ���ֵ�����ڼ���ܼ�������ˣ�

	isPrime1(56);

	return 0;
}