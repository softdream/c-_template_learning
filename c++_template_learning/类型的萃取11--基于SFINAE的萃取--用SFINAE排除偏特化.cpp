#include <iostream>
#include <type_traits>

// ��һ��ʵ�ֻ��� SFINAE ����ȡ�ķ�ʽ���õ�ƫ�ػ�;
// ��Ȼ���ж����� T �Ƿ��ǿ��Ա�Ĭ�ϳ�ʼ��Ϊ���ӣ�

// ����ģ�壬helper to ignore any number of template parameters: 
template<typename ...> 
using VoidT = void;

// primary template:
template<typename, typename = VoidT<>> 
struct IsDefaultConstructibleT : std::false_type 
{

};

// partial specialization (may be SFINAE��d away): 
template<typename T> 
struct IsDefaultConstructibleT<T, VoidT<decltype( T() )>> : std::true_type 
{

} ;
// ����ֻ��Ҫһ�����͹��죺 decltype(T()) �����Ϳ��Լ������ T �Ƿ��ǿ��Ա�Ĭ�ϳ�ʼ���ģ�

// �������ĳ���ض������� T����Ĭ�Ϲ��캯������Ч�ģ���ʱ SIFINEAE ����ʹ��ƫ�ػ�����������
// ������ʹ����ģ�塣�����ƫ�ػ�������Ч�ģ����һᱻѡ��;


struct S
{
	S() = delete; // S ��Ĭ�Ϲ��캯�������ˣ�
};

int main()
{
	IsDefaultConstructibleT<int>::value; // Ok, true;

	IsDefaultConstructibleT<S>::value;

	return 0;
}