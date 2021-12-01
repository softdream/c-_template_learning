#include <iostream>
#include <vector>

// ������ָ�浽ĳ�ͱ� T ����ֵ���ã���д�� ��T &&��;��T &&�������ֺ��壺
// ��һ�ֺ��壬������Ȼ���� ��ֵ���ã�
// �ڶ��ֺ���, ���ʾ��ȿ�������ֵ���ã����������ֵ���ã����߾�һ���������ֺ���������ڴ�����������ֵ���ã�T &&��,
// �����ǿ�������ֵ����һ��������T &��������˫������ʹ֮�ȿ��԰󶨵���ֵ��Ҳ���԰󶨵���ֵ��
// ���н��ߣ�����Ҳ���԰󶨵� const ������� ��const �����Լ� volatile ������� ��volatile ���������󶨵��ȴ���
// const �ִ��� volatile ���εĶ������Ǽ������԰󶨵��κ����͵Ķ��������������ó�֮Ϊ--�������ã�universal reference����

// �������õ�ʹ�ó�����
// 1. ��Ϊ����ģ����βΣ�����
template<typename T>
void f(T &&param) // ע������� const �Ͳ������������ˣ�������� ��ֵ���á�
{
	std::cout << "typeof param: " << typeid(param).name() << std::endl;
}

// 2. �ڶ��������� auto ����������
// auto&& var2 = var1;

// ����������Ĺ�ͬ�㶼���漰���ͱ��Ƶ���
// ��Ҫʹһ�����ó�Ϊ�������ã����漰���ͱ��Ƶ��Ǳ�Ҫ�����������ǳ��������

int main()
{
	int a = 10;
	f( a );

	f(std::move(a));

	auto&& var = a;
	std::cout << "typeof var: " << typeid(var).name() << std::endl;

	std::vector<int> vec;
	vec.emplace_back(10);
	// �� vector ������ emplace_back ����Ϊ�����·�������ʵ��Դ�룺
	// template<class... _Valty>
	//	void emplace_back(_Valty&&... _Val)
	//	{	// insert bool at end
	//		bool _Tmp(_STD forward<_Valty>(_Val)...);
	//		push_back(_Tmp);
	//	}
	// ���Կ��� emplace_back ���� variadic template��ʵʵ���ڵ��漰���ͱ��Ƶ����������� _Valty&&... ����һ���������á�

	return 0;
}