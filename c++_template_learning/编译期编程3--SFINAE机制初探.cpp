#include <iostream>
#include <vector>

// �� C++�У����غ�����֧�ֲ�ͬ���͵Ĳ����Ǻܳ���Ĳ�����������������һ�����غ����ĵ���ʱ��
// ������ֱ���ÿһ�����ذ汾����ѡ������������ƥ�����һ��;

// ��һ���������õı�ѡ�����а�������ģ��ʱ��
// 1. ����������Ҫ����Ӧ�ý�ʲô����ģ��������ڸ���ģ�巽����
// 2. Ȼ������Щ�����滻����ģ��Ĳ����б��Լ��������ͣ�
// 3. ��������滻��ĺ���ģ���������õ�ƥ����������񳣹溯��һ����;

// ������һ�滻���̿��ܻ����� ���⣺�滻�����Ľ������û�����塣
// ������һ���͵��滻���ᵼ�´���C++���Թ���Ҫ����Ե���һ���͵��滻�����

// ��һԭ����Ϊ SFINAE��������ǡ�substitution failure is not an error����

// ����
// number of elements in a raw array: 
template<typename T, unsigned N> 
std::size_t len ( T(&)[N] ) 
{
	return N; 
}

// number of elements for a type having size_type: 
template<typename T>
typename T::size_type len (T const& t) 
{ 
	return t.size(); 
}

// ���ﶨ������������һ�����Ͳ����ĺ���ģ�� len()��
// 1. ��һ������ģ��Ĳ��������� T (&)[N]��Ҳ����˵����һ�������� N �� T ��Ԫ�ص�����;
// 2. �ڶ�������ģ��Ĳ������;��Ǽ򵥵� T�����˷�������Ҫ�� T::size_type ֮��û�б�� ���ƣ���Ҫ�󱻴��ݵĲ������ͱ�����һ�� size_type ��Ա;

int main()
{
	// �����ݵĲ���������������ַ�������ʱ��ֻ���Ǹ�Ϊ�����鶨��ĺ���ģ���ܹ�ƥ��;
	int a[10]; 
	std::cout << len(a); // OK: only len() for array matches 
	std::cout << len("tmp"); //OK: only len() for array matches

	// ���ֻ�ǴӺ���ǩ�������Ļ����Եڶ�������ģ��Ҳ���Էֱ��� int[10]�� char const [4]�滻���Ͳ��� T��
	// ���������滻�ڴ��������� T::size_type ʱ�ᵼ�´�����˶������������ã� �ڶ�������ģ��ᱻ���Ե���

	// ������� std::vector<>��Ϊ�����Ļ�����ֻ�еڶ���ģ������ܹ�ƥ�䣺 
	std::vector<int> v; 
	std::cout << len(v); // OK: only len() for a type with size_type matches

	// ������ݵ�����ָ�뻰����������ģ�嶼���ᱻƥ���ϣ����ǲ�����˶�������
	// ��ʱ�����ڻᱧԹ˵û�з��ֺ��ʵ� len()������ 
	int* p; 
	//std::cout << len(p); // ERROR: no matching len() function found

	// ������ʹ���һ���� size_type ��Ա����û�� size()��Ա�����������һ����
	// ����������ݵĲ����� std::allocator<>: 
	std::allocator<int> x; 
	std::cout << len(x); // ERROR: len() function found, but can��t size()
	// ��ʱ��������ƥ�䵽�ڶ�������ģ�塣��˲��ᱨ��˵û�з��ֺ��ʵ� len()������
	// ���ǻᱨһ�������ڴ���˵�� std::allocator<int>���� size()��һ����Ч���á�
	// ��ʱ�ڶ���ģ�庯�����ᱻ���Ե���



	return 0;
}