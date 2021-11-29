#include <iostream>

/* Ĭ��ģ����������Ը�ģ�����ָ��Ĭ��ֵ����ЩĬ��ֵ����ΪĬ��ģ��������ҿ��������������͵�ģ�� */

// ����һ��ʹ�� decltype
// ע�⣺��һʵ�ַ�ʽҪ�������ܹ���������ģ�������Ĭ�Ϲ������������� T1(), T2()
template<typename T1, typename T2, typename RT = std::decay_t<decltype( true ? T1() : T2() )>>
RT max7(const T1& a, const T2& b)
	// ���������ʽ��ָ�� RT �����ͣ�Ҳ����ʹ��Ϊ��������һ��Ĭ�����ͣ����Ĭ�������Ǵ� T1��T2 �˻�������
{
	return a < b ? b : a;
}

// ���ζ�������Ҳ��������������ȡ std::common_type<>��Ϊ�������͵�Ĭ��ֵ
template<typename T1, typename T2, typename RT = std::common_type_t<T1, T2>>
RT max8(const T1& a, const T2& b)
// ע�� ������ std::common_type<>Ҳ�ǻ��������˻��ġ�
{
	return a < b ? b : a;
}

int main()
{

	std::cout << "7: max7 " << max7(3, 50) << std::endl;

	auto rt2 = max8(3, 50);
	std::cout << "8: max8 " << rt2 << std::endl;

	auto rt3 = max8<int, int, double>(3, 100);// ����д���������ڣ�Ϊ����ʽָ���������ͣ����Ǳ�����ʽ��ָ��ȫ������ģ����������ͣ�
	std::cout << "8: max8 = " << rt3 << std::endl;

	return 0;
}