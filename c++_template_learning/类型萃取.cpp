#include <iostream>
#include <type_traits>

// ��׼���ṩ�˸��ָ����ı���Ϊ������ȡ��type traits���Ĺ��ߣ����ǿ��Ա����������Լ��޸����͡�
// �����Ϳ�����ʵ������ʱ���÷��ʹ�����Ӧ�������ͻ��߶Բ�ͬ������������ͬ����Ӧ��

template<typename T> 
class C
{ 
	// ensure that T is not void (ignoring const or volatile): 
	static_assert(!std::is_same<std::remove_cv_t<T>, void>::value, "invalid instantiation of class C for void type");

public:
	template<typename V> 
	void f( V&& v ) // ��������
	{
		if constexpr(std::is_reference<T>::value) { // special code if T is a reference type

		}

		if constexpr(std::is_convertible<std::decay_t<V>, T>::value) { // special code if V is convertible to T 

		}

		if constexpr(std::has_virtual_destructor<V>::value) {  // special code if V has virtual destructor

		}
	}

};

// ����ģ�� std::declval()���Ա�����ĳһ���͵Ķ�������õ�ռλ����
// �ú���ģ��û�ж��壬 ��˲��ܱ����ã�Ҳ���ᴴ�����󣩡�
// �����ֻ�ܱ��������ᱻ����Ĳ����������� decltype �� sizeof����
// Ҳ��ˣ��ڲ��������������£���Ȼ���Լ�������Ӧ���͵Ŀ��ö���
template<typename T1, typename T2, 
		 typename RT = std::decay_t<decltype(true ? std::declval<T1>() : std::declval<T2>())>
		>
RT max (T1 a, T2 b) 
{ 
	return b < a ? a : b; 
}


int main()
{

	return 0;
}