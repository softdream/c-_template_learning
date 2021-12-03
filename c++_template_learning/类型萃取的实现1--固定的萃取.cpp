#include <iostream>

// ģ�����������ö������Ͷ���ͺ������в�����;
// ���Ǵ�ʵ�ʵĽǶ������� ���ǲ���ϣ����������ģ�������ʵ����󻯵Ĳ�����;
// ���˵��ǣ�ʱ��֤���󲿷ֱ�����Ķ����ģ��������к����Ĭ��ֵ����һЩ����£��� ���ģ�����������ȫ�ɺ��ٵġ���Ҫ��ģ���������;
// �ڴ��������£�����һЩ������Ĭ��ֵ���Դ���ģ������� ��������Ĭ��ֵ��Ҫż�������أ��������Ӧ�ã���

//��ȡ�����߽���ȡģ�壬traits/traits template���� C++��̵���������ǶԹ�����Щ����ƹ�ҵ��Ӧ��ģ��ʱ����Ҫ����Ķ���������а���;

// �̶���ȡ--Fixed Traits
// ��һ������͵����ݴ洢��һ�������У�Ȼ��������һ��ָ�������е�һ��Ԫ�ص�ָ�룬��һ��ָ�����һ��Ԫ�ص�ָ�룬�����ܺͣ�
template<typename T> 
T accum(T const* beg, T const* end)
{
	// ���ʼ��
	T total{}; // assume this actually creates a zero value 

	// ������Ӽ���
	while (beg != end) {
		total += *beg; 
		++beg;
	}
	return total; 
}

// һ�����Ա���ʹ�ö����ģ������ķ�ʽ�ǣ���ÿ��������ʵ���� accum()�� T ��
// ��֮��Ӧ��Ӧ�ñ������洢����ֵ������֮�佨��ĳ����ϵ����һ��ϵ���Ա���Ϊ�� T ��ĳ�����ԡ� 
// ����������չʾ��һ��������ͨ��ģ���ƫ�ػ�����������ϵ;
template<typename T>
struct AccumulateTrait;

template<>
struct AccumulateTrait<char>
{
	using AccT = int;
};

template<>
struct AccumulateTrait<short>
{
	using AccT = int;
};

template<>
struct AccumulateTrait<int>
{
	using AccT = long;
};

template<>
struct AccumulateTrait<unsigned int>
{
	using AccT = unsigned long;
};

template<>
struct AccumulateTrait<float>
{
	using AccT = double;
};

// AccumulationTraits ģ�屻��Ϊ��ȡģ�壬��Ϊ������ȡ����������͵����ԡ�
// ��ͨ�����Կ� ���в�ֻһ����ȡ��Ҳ�����в�ֻһ��������;

template<typename T> 
auto accum1(T const* beg, T const* end)
{ 
	// return type is traits of the element type 
	using AccT = typename AccumulateTrait<T>::AccT;

	AccT total{}; // assume this actually creates a zero value
	while (beg != end) { 
		total += *beg; 
		++beg; 
	}
	
	return total; 
}

int main()
{
	// ��һ��
	int num[] = { 1, 2, 3, 4, 5 };
	std::cout << "accum = " << accum( num, num + 5 )<<std::endl; // OK��accum = 15;

	char name[] = "hello world";
	int length = sizeof(name) - 1;
	std::cout << "accum = " << accum(name, name + length) << std::endl; // OK��accum = '\';

	std::cout << "accum = " << accum1(name, name + length) << std::endl; // OK, accum = 1116;
 
	return 0;
}
