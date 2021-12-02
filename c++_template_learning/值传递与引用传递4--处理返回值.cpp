#include <iostream>

// ����ֵҲ���Ա������û��߰�ֵ���ء����ǰ����÷��ؿ��ܻ����һЩ�鷳��
// ��Ϊ�������õĶ����ܱ��ܺõĿ���;
// �������ճ�����У�Ҳ��һЩ����������ڰ����÷���:
// 1. �������������ַ����е�Ԫ�أ�����ͨ��[]��������� front()��������Ԫ�أ�;
// 2. �����޸������ĳ�Ա;
// 3. Ϊ��ʽ���÷���һ�����󣨱���>>��<<������Լ���ֵ�������;
// 4. ����Գ�Ա��ֻ�����ʣ�ͨ��Ҳͨ������ const ����ʵ�֡�

// Ҫ��һ������Ҫȷ����������ֵ�ǰ�ֵ���ص�����£�
// ʹ�ú���ģ�� T ��Ϊ�������Ͳ����ܱ�֤����ֵ���������ã�
// ��Ϊ T ��ĳЩ����»ᱻ��ʽ�ƶ�Ϊ�������ͣ�
// ��һ��
template<typename T> 
T retR(T&& p) // p is a forwarding reference 
{ 
	return p; // OOPS: returns by reference when called for lvalues 
}

// ��ʹ����ģ�屻����Ϊ��ֵ���ݣ�Ҳ������ʽ�ؽ� T ָ��Ϊ��������:
// ������
template<typename T> 
T retV(T p) //Note: T might become a reference
{ 
	return p; // OOPS: returns a reference if T is a reference 
}

// ��ȫ�����������ѡ��:
// 1. ��������ȡ std::remove_reference<>�� T תΪ����������:
template<typename T> 
typename std::remove_reference<T>::type 
retV1(T p) 
{
	return p; // always returns by value 
}

// 2. ��������������Ϊ auto���Ӷ��ñ�����ȥ�ƶϷ������ͣ�������Ϊ auto Ҳ�ᵼ�������˻�;
template<typename T>
auto retV2(T p) // by-value return type deduced by compiler 
{ 
	return p; // always returns by value
}

int main()
{
	// ������
	int x = 10; 
	std::cout<<"type = "<<typeid(retV<int&>(x)).name()<<std::endl; // retT() instantiated for T as int&



	return 0;
}