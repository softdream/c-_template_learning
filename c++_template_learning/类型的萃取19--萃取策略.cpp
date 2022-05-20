#include <iostream>
#include <type_traits>

// ��ĿǰΪֹ�����������е���ȡģ�屻�����ж�ģ����������ԣ�
// ���Ǵ��������һ�����ͣ� �����ڸ�������ֵ�Ĳ������ķ���ֵ�����ͣ��Լ��������ԡ�
// ��һ����ȡ����Ϊ������ȡ ��property traits����

// ��Ϊ�Աȣ�ĳЩ��ȡ������Ǹ���δ���ĳЩ���͡����ǳ�֮Ϊ������ȡ��policy traits����

// ��Ȼ������ȡͨ�������Ա�ʵ��Ϊ���ͺ�����������ȡȴͨ�������԰�װ����Ա�����С�

// ����һ��ֻ����������
// �� C++�� C �У������ĵ��ò�����call parameters��Ĭ��������ǰ���ֵ���ݵġ�
// ����ζ�ţ� ���ú�����������Ĳ�����ֵ���ᱻ�������ɱ����ú������Ƶ�λ�á�
// �󲿷ֳ���Ա��֪���� ���ڱȽϴ�Ľṹ�壬��һ�����ĳɱ���ǳ��ߣ�
// ��˶�����һ��ṹ������ܹ����䰴�� �������ã�reference-to-const������
// �� C �еĳ���ָ�루pointer-to-const�����д���;

// ��Ȼ������ģ��֮������Ҫ��ø���΢��һЩ��
// �������Ȳ���֪�������滻ģ����������ͽ����Ƕ�󡣶��ң�����Ҳ�����ǽ��������ڽṹ��Ĵ�С��
// ��ʹ�ǱȽ�С�Ľṹ�壬�俽�����캯���ĳɱ�Ҳ���ܻ�ܸߣ��������������Ӧ��ѡ�񰴳������ô��ݡ�

// ��һ������ͨ��Ӧ���ò�����ȡģ�壨һ�����ͺ�����������
// �ú�����Ԥ�ڵĲ������� T ӳ�䵽��ѵĲ������� T ������ T const&��
// ��Ϊ��һ���Ľ��ƣ���ģ��Ὣ��С����������ָ������Ͱ�ֵ���д��ݣ�
// ���������������Ͷ����ճ������ý��д��ݣ�

template<typename T> 
struct RParam 
{
	using Type = typename IfThenElseT<sizeof(T) <= 2 * sizeof(void*), T, T const&>::Type; 
};

// ��һ���棬������Щ�� sizeof ���������һ����С��ֵ��
// ���ǿ������캯���ɱ�ȴ�ܸߵ��������ͣ����ǿ�����Ҫ�ֱ�����ǽ����ػ�����ƫ�ػ�:
template<typename T>
struct RParam<Array<T>> 
{
	using Type = Array<T> const&; 
};

// ������һ�������� C++�кܳ��������ֻ����Щӵ�м򵥿����Լ��ƶ����캯�������Ͱ�ֵ���д��ݣ�
// ����Ҫ������������ʱ����ѡ���ԵĽ�����һЩ class ���ͼ��밴ֵ���ݵ����� 
// ��C++��׼���а����� std::is_trivially_copy_constructible �� std::is_trivially_move_constructible ������ȡ����
template<typename T> 
struct RParam 
{
	using Type = IfThenElse<(sizeof(T) <= 2 * sizeof(void*) && std::is_trivially_copy_constructible<T>::value && std::is_trivially_move_constructible<T>::value), T, T const&>; 
};

// ���۲�����һ�ַ�ʽ�����ڸò��Զ����Ա����ɵ���ȡģ��Ķ����У��ͻ�Ҳ����������ȥʵ�ָ��õ�Ч����
// ���磬�������������� class����������һ�� class ����ָ��Ҫ��ֵ����ֻ��������
class MyClass1 {
public:
	MyClass1() 
	{
	
	}
	
	MyClass1(MyClass1 const&)
	{
		std::cout << "MyClass1 copy constructor called\n";
	}

};

class MyClass2 
{ 
public: 
	MyClass2() 
	{ 
	
	}
	
	MyClass2(MyClass2 const&) 
	{
		std::cout << "MyClass2 copy constructor called\n";
	}

};

// pass MyClass2 objects with RParam<> by value 4
template<> 
class RParam<MyClass2> 
{
public: 
	using Type = MyClass2; 
};


