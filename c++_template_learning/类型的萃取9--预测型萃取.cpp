#include <iostream>

// ������ƻ��ڶ�����������ͺ�������ͬ������������һ�������������ȡ--����Ԥ�⣨����һ�� bool ��ֵ�����ͺ�����;

// IsSameT : IsSameT ���ж����������Ƿ���ͬ;
// �������ģ��˵��ͨ�����Ǵ��ݽ��������������ǲ�ͬ�ģ������ value ��Ա�� false
template<typename T1, typename T2> 
struct IsSameT 
{ 
	static constexpr bool value = false;
};

// ͨ��ʹ��ƫ�ػ������������ݽ�����������ͬ���͵����������value ��Ա���� true ��;
template<typename T> 
struct IsSameT<T, T> 
{ 
	static constexpr bool value = true; 
};

// ���ڲ���һ����������ȡ������û��Ϊ֮����һ������ģ�壬
// ���ǿ���Ϊ֮����һ�����ݿ���ͬ��ɫ�� constexpr �ı���ģ��:
//template<typename T1, typename T2> 
//constexpr bool isSame = IsSameT<T1, T2>::value;// ��仰�� vs2015 �±�����consexpr���ڴ˴���Ч��

// C++��׼���ṩ����֮��Ӧ�� std::is_same<>;

// true_type �� false_type:
// ͨ��Ϊ���ܵ������� true �� false �ṩ��ͬ�����ͣ����ǿ��Դ�����߶� IsSameT �Ķ���:
// �����������һ�� BoolConstant ģ���Լ��������ܵ�ʵ�� TrueType �� FalseType��
template<bool val> 
struct BoolConstant 
{ 
	using Type = BoolConstant<val>;
	static constexpr bool value = val;
};

using TrueType = BoolConstant<true>;
using FalseType = BoolConstant<false>;

// �Ϳ��Ի������������Ƿ�ƥ�䣬����Ӧ�� IsSameT �ֱ�̳��� TrueType �� FalseType:
template<typename T1, typename T2> 
struct IsSameT2 : FalseType
{

}; 

template<typename T> 
struct IsSameT2<T, T> : TrueType
{

};

// ���� IsSameT<T, int> �ķ������ͻᱻ��ʽ��ת��������� TrueType ���� FalseType��
// �����Ͳ����ṩ����Ӧ�� value ��Ա���������ڱ����ڼ佫��Ӧ�������ɷ�����Ӧ�ĺ���ʵ��
// ������ģ���ƫ�ػ��ϡ�
// ���磺
template<typename T> 
void fooImpl(T, TrueType) {
	std::cout << "fooImpl(T,true) for int called\n";
}

template<typename T> 
void fooImpl(T, FalseType) 
{ 
	std::cout << "fooImpl(T,false) for other type called\n";
}

template<typename T> 
void foo(T t) 
{
	fooImpl(t, IsSameT2<T, int>{}); // choose impl. depending on whether T is int
}

// ��һ��������Ϊ����ɷ���tag dispatching��;

// �� C++11 ��ʼ C++ ��׼����<type_traits>���ṩ����Ӧ�����ͣ�std::true_type �� std::false_type;

int main()
{

	foo(42); // calls fooImpl(42, TrueType)
	foo(7.7); // calls fooImpl(42, FalseType)

	return 0;
}