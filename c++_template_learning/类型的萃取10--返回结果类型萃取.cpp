#include <iostream>
#include <array>
#include <type_traits>

// ��һ�����Ա��������������͵����ͺ����������Ƿ���ֵ������ȡ��
// �ڱ�д������ģ���ʱ�����ǻ�����á�

// ���磺������дһ�����Զ����� Array ������͵ĺ���ģ�壺
template<typename T, int N = 10> 
std::array<T, N> operator+ (std::array<T, N> const& a, std::array<T, N> const& b)
{

}

// �����������Ա����������Ƕ�һ�� char ����ֵ��һ��������ֵ��ͣ�
// ������ȻҲ��ϣ���ܹ��� Array Ҳִ�����ֻ�����ͣ�mixed-type���Ĳ�����
// �������Ǿ�Ҫ�������ξ������ģ��ķ���ֵ������;
// һ�����Խ����������ķ�ʽ���Ƿ���ֵ����ģ�壺
// template<typename T1, typename T2> 
// std::array<typename PlusResultT<T1, T2>::Type> operator+ (std::array<T1> const& a, std::array<T2> const& b)
// {

// }

// ���е� PlusResultT ��ȡ�������ж�ͨ��+���������������ͣ������ǲ�ͬ���ͣ�����ֵ������õ�������:
template<typename T1, typename T2> 
struct PlusResultT
{
	using Type = decltype(T1() + T2());
};
// ��һ��ȡģ��ͨ��ʹ�� decltype ��������ʽ T1()+T2()�����ͣ����������������һ��޵Ĺ���
// ����������������������promotion rules������������أ������˱�����;

template<typename T1, typename T2> 
using PlusResult = typename PlusResultT<T1, T2>::Type;

/*template<typename T1, typename T2, int N = 10> 
std::array<typename PlusResultT<T1, T2>::Type, N> operator+ (std::array<T1, N> const& a, std::array<T2, N> const& b)
{
	return a + b;
}*/

// ���decltype ���ܻᱣ���˹������Ϣ�����磬���ǵ� PlusResultT ���ܻ᷵��һ���������ͣ�
// �������ǵ� Array ģ��ȴ�ܿ��ܲ���Ϊ����������Ƶġ�
// ���ǿ�����֮ǰ˵��ȥ�����ã�ȥ�������Ե���ȡ�����ˣ�
/*template<typename T1, typename T2, int N = 10>
std::array<std::remove_const_t<std::remove_reference_t<PlusResult<T1, T2>>>, N> operator+ (std::array<T1, N> const& a, std::array<T2, N> const& b)
{
	std::array<std::remove_const_t<std::remove_reference_t<PlusResult<T1, T2>>>, N> ret;

	for (int i = 0; i < N; i++) {
		ret[i] = a[i] + b[i];
	}

	return ret;
}*/
// ��������д��Ȼ���鷳����дΪ��
template<typename T1, typename T2, int N = 10, 
		 typename RT = std::array<std::remove_const_t<std::remove_reference_t<PlusResult<T1, T2>>>, N>
		>
 RT operator+ (std::array<T1, N> const& a, std::array<T2, N> const& b)
{
	RT ret;

	for (int i = 0; i < N; i++) {
		ret[i] = a[i] + b[i];
	}

	return ret;
}

// ���ڱ��ʽ T1() + T2()��ͼ������ T1 �� T2 ����ֵ����ֵ��ʼ�������������ͱ���Ҫ�пɷ��ʵġ�δ��ɾ����Ĭ�Ϲ��캯���������Ƿ� class ���ͣ���
// Array �౾����ܲ�û��Ҫ����Ԫ�����Ϳ��Ա�����ֵ��ʼ�����������һ������ġ�����Ҫ�����ơ�

// �����ǿ��Ժܼ򵥵��ڲ���Ҫ���캯��������¼���+���ʽ��ֵ����������ʹ��һ������Ϊһ���������� T ������ֵ�ĺ�����
// Ϊ����һĿ�ģ�C++��׼�ṩ�� std::declval<>;

// ���ʽ declval<>�����ڲ���Ҫʹ��Ĭ�Ϲ��캯����������������������������Ϊ���� T ����һ��ֵ��

// ���� declval�����ǾͿ��Բ����� PlusResultT ��ʹ��ֵ��ʼ����:
template<typename T1, typename T2> 
struct PlusResultT2 
{ 
	using Type = decltype(std::declval<T1>() + std::declval<T2>()); 
}; 
template<typename T1, typename T2>
using PlusResult2 = typename PlusResultT2<T1, T2>::Type;

int main()
{
	std::array<int, 10> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	std::array<char, 10> b = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	auto c = a + b;

	for (auto it : c) {
		std::cout << it << std::endl;
	}

	return 0;
}