#include <iostream>

// ���� isPrime()�����ڱ����ڽ�����ز��ԵĹ��ܣ�
// ��һ������˼��Ӧ�ó����������ڱ����ڼ�ͨ�������������ڲ�ͬ��ʵ�ַ���֮����ѡ��

constexpr bool doIsPrime(unsigned p, unsigned d) // p: number to check, d: current divisor
{
	return d != 2
		? (p % d != 0) && doIsPrime(p, d - 1) // check this and smaller divisors
		: (p % 2 != 0); // end recursion if divisor is 2 
}
constexpr bool isPrime(unsigned p)
{
	return p < 4 ? !(p < 2) // handle special cases
		: doIsPrime(p, p / 2); // start recursion with divisor from p/2
}

// ���磬������һ��������ģ������ǲ�������Ϊ�������ڲ�ͬ��ģ��֮����ѡ��:
// �ȶ���һ������ģ�壻
template<int SZ, bool = isPrime(SZ)> 
struct Helper;

// SZ ����������ƫ�ػ�
template<int SZ>
struct Helper<SZ, false>
{
	bool value = false;
};

// SZ ��������ƫ�ػ�
template<int SZ>
struct Helper<SZ, true>
{
	bool value = true;
};

// ��һƫ������ ��ʹ�÷��������㷺���ڻ���ģ��������ԣ��ڲ�ͬģ��ʵ�ַ���֮����ѡ��

template<int SZ>
void test()
{
	Helper<SZ> h;
	if (h.value == true) {
		std::cout << " SZ ��������ƫ�ػ�" << std::endl;
	}
	else {
		std::cout << " SZ ����������ƫ�ػ�" << std::endl;
	}

}

int main()
{

	test<53>();

	return 0;
}