#include <iostream>
#include <type_traits>

/* ���� 3 ����ģ��ķ���ֵ */

// ����һ�������ķ���ֵ���ͺ��βε�����һ��ʱ //
template<typename T>
T max1(const T& a, const T& b) // 
{
	return a < b ? b : a;
}

// ���ζ�����ģ������͵��ò���֮��û�б�Ȼ����ϵ����ģ���������ȷ����ʱ�򣬾�Ҫ��ʽ��ָ��ģ�����//
template<typename T, typename RT> // �����¼���һ��ģ�������Ϊ����ֵ���ͣ�
RT max2(const T& a, const T& b)	  // ȱ������ڵ���ʱ�޷����Զ������Ƶ��ˡ�
								  // ģ�������ƶϲ��ῼ�Ƿ������ͣ��� RT ��û�б��������ò��������͡���� RT ���ᱻ�ƶϡ������ͱ�����ʽ��ָ��ģ����������ͣ�
{
	return a < b ? b : a;
}

// ��������Ϊ��֧�ַ���ֵ�����ƶϣ�c++11��д�����£�
template<typename T1, typename T2>
auto max3(const T1& a, const T2& b)->decltype(a < b ? b : a)
// �� C++11 �У�β�÷������ͣ�trailing return type����������ʹ�ú����ĵ��ò����� Ҳ����˵�����ǿ��Ի��������?:�Ľ��������������
{
	return a < b ? b : a;
}

// �����ģ�Ϊ��֧�ַ���ֵ�����ƶϣ�c++14��д�����£�
template<typename T1, typename T2>
auto max4(const T1& a, const T2& b)
// �� C++14 �У�ֻҪʹ�� auto �ؼ��ּ��ɣ����������Զ�������ֵ�����Ƶ���
{
	return a < b ? b : a;
}

// ������������������ĳЩ����»���һ�����ص����⣺���� T1��T2 �������������ͣ��������;�Ҳ���ܱ��ƶ�Ϊ�������͡������Ӧ�÷��ص��� decay ��� T��
// �����壺�Է���ֵ�������˻�
template<typename T1, typename T2>
auto max5(const T1& a, const T2& b)->typename std::decay<decltype(a < b ? b : a)>::type
// �����õ��˱�׼���е� std::decay �Է���ֵ���ͽ��С��˻���������ȥ�����á�const��volitile����������
{
	return a < b ? b : a;
}

// ����������������������Ϊ�������ͣ�Common Type��
// �� C++11 ��ʼ����׼���ṩ��һ��ָ������һ�����͡��ķ�ʽ��std::common_type<>::type ��������������������ģ������Ĺ������͡�
template<typename T1, typename T2>
std::common_type_t<T1, T2> max6(const T1& a, const T2& b)
// std::common_type Ҳ��һ��������ȡ��type trait����������<type_traits>�У�������һ���ṹ�壬�ṹ��� type ��Ա������Ŀ�����ͣ�
{
	return a < b ? b : a;
}


int main()
{
	
	std::cout << "1: max1(2, 5) = " << max1(2, 5) << std::endl;

	// ���������ʽָ������ֵ����
	std::cout << "2: max2(2, 5) = " << max2<int, int>(2, 5) << std::endl;
	
	std::cout << "3: max3(3,100) = " << max3(3, 100) << std::endl;


	std::cout << "4: max4(30,100) = " << max4(30, 100) << std::endl;

	std::cout << "5: max5(30,100) = " << max5(30, 100) << std::endl;

	std::cout << "6: max6(30,100) = " << max6(30, 100) << std::endl;

	return 0;
}
