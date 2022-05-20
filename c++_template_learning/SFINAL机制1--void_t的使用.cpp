#include <iostream>
#include <type_traits>

/*
std::voit_t ���ܣ�
	�ܹ���⵽Ӧ��SFINAL����ʱ���ֵķǷ����ͣ�����ģ���н��������ͱ�����һ����Ч�����͡�
std::voit_tӦ�ã�
	1. �ж������Ƿ���ĳ�����ͱ�����
	2. �ж������Ƿ����ĳ����Ա������
	3. �ж������Ƿ����ĳ����Ա������
*/

// 1. �ж������Ƿ���ĳ�����ͱ�����
struct NoInerType
{

};

struct HaveInerType
{
	int m_i;
	using type = int; // ĳ�����ͱ���

	void myfunc()
	{

	}
};

template<typename T, typename U = std::void_t<>>
struct HasTypeMember : std::false_type
{

};

template<typename T>
struct HasTypeMember<T, std::void_t<typename T::type>> : std::true_type
{

};

// 2. �ж������Ƿ����ĳ����Ա����
template<typename T, typename U = std::void_t<>>
struct HasMemberVariable 
{
	const static bool value = false;
};

template<typename T>
struct HasMemberVariable<T, std::void_t<typename decltype(T::m_i)>> 
{
	const static bool value = true;
};

// 3. �ж������Ƿ����ĳ����Ա������
template<typename T, typename U = std::void_t<>>
struct HasMemberFunction : std::false_type
{

};

template<typename T>
struct HasMemberFunction<T, std::void_t<decltype(std::declval<T>().myfunc())>> : std::true_type
{

};

int main()
{
	// HaveTypeMember<NoInerType> ������ػ��汾ʱ������û������type����T::typeΪ�Ƿ����ͣ�
	// ���Ժ����ػ��汾���Ӷ�ʵ���������汾�������汾�̳�std::false_type,�г�ԱvalueֵΪ0��
	std::cout << HasTypeMember<NoInerType>::value << std::endl;

	//  HaveTypeMember<HaveInerType> ������ػ��汾ʱ���г�Ա����type��
	// �Ӷ�std::voit_t<typename T::type> ��ⲻ�ǷǷ����ͣ���ֵΪvoid���Ӷ�ʵ�����ػ��汾��
	// ����std::true_type��value = 1��
	std::cout << HasTypeMember<HaveInerType>::value << std::endl;

	// ԭ��ͬ�ϣ�ע��delctype�����ھ�̬�����Ƶ�
	std::cout << HasMemberVariable<NoInerType>::value << std::endl;

	std::cout << HasMemberVariable<HaveInerType>::value << std::endl;

	// ע��std::declval�÷�
	std::cout << HasMemberFunction<NoInerType>::value << std::endl;
	std::cout << HasMemberFunction<HaveInerType>::value << std::endl;

	return 0;
}