#include <iostream>

// ���˿��Ա������������������͵�ĳЩ���ԣ���ȡ�����Ա�����������ת����
// ����Ϊĳ���� ����ӻ��Ƴ����á�const �Լ� volatile ���Ʒ�;

// ɾ������
// ���ǿ���ʵ��һ�� RemoveReferenceT ��ȡ����������������ת������ײ������ߺ��������ͣ����ڷ����������򱣳ֲ���;

template<typename T>
struct RemoveReferenceT 
{ 
	using Type = T; 
};

template<typename T>
struct RemoveReferenceT<T&>
{ 
	using Type = T; 
};

template<typename T>
struct RemoveReferenceT<T&&> {
	using Type = T; 
};

template<typename T> 
using RemoveReference = typename RemoveReference<T>::Type;

// C++��׼���ṩ��һ����Ӧ�� std::remove_reference<> ��ȡ;


// �������
// ����Ҳ���Ը�һ���������������ֵ������ֵ����;
template<typename T> 
struct AddLValueReferenceT 
{ 
	using Type = T&; 
};

template<typename T>
using AddLValueReference = typename AddLValueReferenceT<T>::Type;

template<typename T> 
struct AddRValueReferenceT
{
	using Type = T&&;
};

template<typename T>
using AddRValueReferenceT = T&;

template<typename T>
using AddRValueReferenceTT = T&&;

// C++ ��׼����Ҳ�ṩ����֮��Ӧ��������ȡ: std::add_lvalue_reference<> �� std::add_rvalue_reference<>;

// �Ƴ����Ʒ�
// ת����ȡ���Էֽ����������������ĸ������ͣ���������������;
// ���磬���һ�������� ���� const ���Ʒ������ǿ��Խ����Ƴ���
template<typename T>
struct RemoveConstT 
{ 
	using Type = T;
};

template<typename T>
struct RemoveConstT<T const> 
{ 
	using Type = T;
};

template<typename T> 
using RemoveConst = typename RemoveConstT<T>::Type;

// ת����ȡ�����Ƕ๦�ܵģ����紴��һ�����Ա������Ƴ� const �� volatile �� RemoveCVT ��ȡ:
template<typename T> 
struct RemoveCVT : RemoveConstT<typename RemoveVolatileT<T>::Type> 
{

};

template<typename T> 
using RemoveCV = typename RemoveCVT<T>::Type;

// �����Է��ձ�׼���е� std::decay ʵ��һ���˻���ȡ��
// �������ǶԷ����顢�Ǻ������� �����ж��壬�����ֻ��Ҫɾ�� const �� volatile ���Ʒ����ɣ�
template<typename T> 
struct DecayT : RemoveCVT<T> 
{

};

// Ȼ�����Ǵ������鵽ָ����˻�������Ҫ��ƫ�ػ����������е��������ͣ��н���޽����飩��
template<typename T> 
struct DecayT<T[]> 
{ 
	using Type = T*; 
};

template<typename T, std::size_t N>
struct DecayT<T[N]>
{
	using Type = T*; 
};

// �������������ָ����˻�������ҪӦ�����еĺ������ͣ�������ʲô���������Լ��ж���������
template<typename R, typename... Args> 
struct DecayT<R(Args...)>
{
	using Type = R(*)(Args...);
};

template<typename R, typename... Args>
struct DecayT<R(Args..., ...)> {
	using Type = R(*)(Args..., ...);
};

template <typename T> 
using Decay = typename DecayT<T>::Type;

int main()
{

	return 0;
}