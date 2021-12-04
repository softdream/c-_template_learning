#include <iostream>
#include <type_traits>

// ��һ�ֶԻ��� SFINAE ����ȡ��Ӧ���ǣ�����һ�������ж�һ���������� T �Ƿ�
// ������Ϊ X �ĳ�Ա�����ͻ��߷����ͳ�Ա������ȡ��

// ̽�����ͳ�Ա��Detecting Member Types��:

// ���ȶ���һ�������жϸ������� T �Ƿ������ͳ�Ա size_type ����ȡ:

// defines true_type and false_type 
// helper to ignore any number of template parameters:
template<typename ...> 
using VoidT = void;

// primary template: 
template<typename, typename = VoidT<>>
struct HasSizeTypeT : std::false_type
{

};

// partial specialization (may be SFINAE��d away): 
template<typename T> 
struct HasSizeTypeT<T, VoidT<typename T::size_type>> : std::true_type
	// ������ֻ���� T �������ͳ�Ա size_type ��ʱ�����Ч;
	// �������ĳ������ T����������Ч����ô SFINAE ��ʹƫ�ػ�ʵ�ֱ����������Ǿ��˻ص���ģ������;
{

} ;


struct CX { 
	using size_type = std::size_t; 
};

// �ڴ����������͵�ʱ����ܻ�����������������顣���磬��Ȼ���µĴ���������������� 
struct CXR {
	using size_type = char&; // Note: type size_type is a reference type
};

// ��������ȷʵû�г�Ա�����ǵ�����ʹ�����õ�ʱ�򣬽�����ʽ��������������ָ������ͣ�
// ������ǿ��ܻ�ϣ���������Ǵ��ݽ�����ģ��������������� ��ʱ����Ȼ������ָ����������жϡ�
// Ϊ����һĿ�ģ������� HasSizeTypeT ��ƫ�ػ���ʹ������֮ǰ���ܵ� RemoveReference ��ȡ��
template<typename T> 
struct HasSizeTypeT<T, VoidT<std::remove_reference_t<T>::size_type>> : std::true_type
{ 

};

int main()
{
	std::cout << HasSizeTypeT<int>::value << std::endl; // false

	std::cout << HasSizeTypeT<CX>::value << std::endl; // true

	std::cout << HasSizeTypeT<CXR>::value << std::endl; // OK: prints true

	// ������֮���ƵĴ���ȴ������������������Ľ��
	std::cout << HasSizeTypeT<CXR&>::value << std::endl; // OOPS: prints false 
	std::cout << HasSizeTypeT<CXR&&>::value << std::endl; // OOPS: prints false

	return 0;
}