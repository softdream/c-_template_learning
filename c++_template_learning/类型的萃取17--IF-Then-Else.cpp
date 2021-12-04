#include <iostream>
#include <type_traits>

// ���ǿ�����һ�����������ģ�� IfThenElse �������һ if-then-else ����Ϊ��
// ������һ�� bool �͵�ģ������������ݸò����������������Ͳ����м���ѡ��;

// primary template: yield the second argument by default and rely on 
// a partial specialization to yield the third argument 
// if COND is false 
template<bool COND, typename TrueType, typename FalseType> 
struct IfThenElseT 
{ 
	using Type = TrueType;
};

// partial specialization: false yields third argument 
template<typename TrueType, typename FalseType> 
struct IfThenElseT<false, TrueType, FalseType> 
{
	using Type = FalseType;
};

template<bool COND, typename TrueType, typename FalseType>
using IfThenElse = typename IfThenElseT<COND, TrueType, FalseType>::Type;

// ����
template<auto N> 
struct SmallestIntT
{
	typename IfThenElseT<N <= std::numeric_limits<char>::max(), char,
		typename IfThenElseT<N <= std::numeric_limits<short>::max(), short, 
			typename IfThenElseT<N <= std::numeric_limits<int>::max(), int, 
				typename IfThenElseT<N <= std::numeric_limits<long>::max(), long, 
					typename IfThenElseT<N <= std::numeric_limits<long long>::max(), long long, //then void //fallback 
					>::Type 
				>::Type 
			>::Type 
		>::Type 
	>::Type;
};

// �� C++��׼�������� IfThenElseT ģ���Ӧ��ģ�壨std::conditional<>��;

int main()
{
	SmallestIntT<10>();

	return 0;
}