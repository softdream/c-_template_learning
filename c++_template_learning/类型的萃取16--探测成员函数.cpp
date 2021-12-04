#include <iostream>
#include <type_traits> // for true_type, false_type, and void_t
#include <vector>

// primary template: 
template<typename, typename = std::void_t<>> 
struct HasBeginT : std::false_type 
{

};

// partial specialization (may be SFINAE��d away): 
template<typename T> 
struct HasBeginT<T, std::void_t<decltype(std::declval<T> ().begin())>> : std::true_type 
// ��������ʹ�� decltype(std::declval<T> ().begin())�������Ƿ��ܹ����� T �� begin()��
{

};

int main()
{
	std::cout << HasBeginT<std::vector<int>>::value << std::endl;

	return 0;
}