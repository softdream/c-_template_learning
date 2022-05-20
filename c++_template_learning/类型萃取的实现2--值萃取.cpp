#include <iostream>

// ��ĿǰΪֹ���ǿ�������ȡ������Ķ����ض����������͵Ķ����������Ϣ��
// ʵ������һ���������Ϣ������������������Ϣ�������Խ������Լ�������ֵ���һ�����͹���������

// ����ԭʼ�� accum()ģ���У�����ʹ��Ĭ�Ϲ��캯���Է���ֵ�����˳�ʼ����
// ϣ�������ʼ��Ϊһ�������㣨zero like����ֵ�� 
// AccT total {}; // assume this actually creates a zero value 
// ��
// return total;
// ����Ȼ���Ⲣ���ܱ�֤һ��������һ�����ʵĳ�ʼֵ, ��Ϊ AccT ���ܸ�����û��Ĭ�Ϲ��캯����

// ���ǿ���Ϊ AccumulateTraits ���һ���µ�ֵ��ȡ��value trait�������������⣻
template<typename T>
struct AccumulateTrait;

template<>
struct AccumulateTrait<char>
{
	using AccT = int;
	static AccT const zero = 0;
};

template<>
struct AccumulateTrait<short>
{
	using AccT = int;
	static AccT const zero = 0;
};

template<>
struct AccumulateTrait<int>
{
	using AccT = long;
	static AccT const zero = 0;
};

template<>
struct AccumulateTrait<unsigned int>
{
	using AccT = unsigned long;
	static AccT const zero = 0;
};

template<>
struct AccumulateTrait<float>
{
	using AccT = double;
	// ��������ȱ���� C++ ֻ�������������ж�һ�����λ���ö�����͵� static const ���ݳ�Ա���г�ʼ����
	//static AccT const zero = 0; // ��仰�ᱨ��
	
	// constexpr �� static ���ݳ�Ա����΢��һЩ���������Ƕ� float �����Լ���������ֵ���ͽ������ڳ�ʼ��;
	constexpr static AccT zero = 0.0;
};

// �����µ���ȡ�ṩ��һ�������ڱ����ڼ����ģ�const��zero��Ա;

template<typename T>
auto accum(T const* beg, T const* end)
{
	// return type is traits of the element type 
	using AccT = typename AccumulateTrait<T>::AccT;

	AccT total = AccumulateTrait<T>::zero; // ֵ��ȡ��

	while (beg != end) {
		total += *beg;
		++beg;
	}

	return total;
}

// ��������ֵ��ȡ��д�����ڵ������ǣ������� const ���� constexpr ����ֹ�Է�����ֵ���ͽ�����һ���ʼ����
// ���磺��һ���Զ������ͣ�
class MyType
{
public:
	MyType() : a(0), b(0), c(0)
	{

	}

	MyType( const int a_, const int b_, const int c_ ) : a(a_), b(b_), c(c_)
	{

	}

	MyType(const std::initializer_list<int>& tmp)
	{
		std::cout << "initializer_list constructor ..." << std::endl;
		a = *tmp.begin();
		b = *(tmp.begin() + 1);
		c = *(tmp.begin() + 2);
	}

	const MyType operator+=( const MyType& x) const
	{
		std::cout << "operator overload ..." << std::endl;
		return MyType(x.a + a, x.b + b, x.c + c);
	}

	void print() const
	{
		std::cout << "a = " << a << std::endl;
		std::cout << "b = " << b << std::endl;
		std::cout << "c = " << c << std::endl;
	}

private:
	int a;
	int b;
	int c;
};

// Ϊ�������ʵ��һ�� ֵ��ȡ��
template<>
struct AccumulateTrait<MyType>
{
	using AccT =  MyType;

	//constexpr static MyType zero = MyType{0, 0, 0};// ERROR: not a literal type ,���캯������ constexpr ��

	// �������������
	static const MyType zero;
};
// һ���Ƚ�ֱ�ӵĽ�������ǣ��������ж���ֵ��ȡ��ֻ��������;
// Ȼ�������������г�ʼ����
MyType const AccumulateTrait<MyType>::zero = MyType{0, 0, 0};
// ������Ȼ���Թ���������ȴ��Щ�鷳�������������ط�ͬʱ�޸Ĵ��룩���������ܻ�����Щ��Ч����Ϊ������ͨ������֪���������ļ��еı�������;


// �� C++17 ֮ǰ����һ�ֽ���취�ǣ�������Щ����������������ֵ��ֵ��ȡ��ʹ�� inline ��Ա������
// ���ǿ���������������д AccumulateTraits��

template<typename T>
struct AccumulateTrait2;

template<>
struct AccumulateTrait2<char>
{
	using AccT = int;
	static constexpr AccT zero()
	{
		return 0;
	}
};

template<>
struct AccumulateTrait2<short>
{
	using AccT = int;
	static constexpr AccT zero()
	{
		return 0;
	}
};

template<>
struct AccumulateTrait2<int>
{
	using AccT = long;
	static constexpr AccT zero()
	{
		return 0;
	}
};

template<>
struct AccumulateTrait2<unsigned int>
{
	using AccT = unsigned long;
	static constexpr AccT zero()
	{
		return 0;
	}
};

template<>
struct AccumulateTrait2<float>
{
	using AccT = double;

	static constexpr AccT zero()
	{
		return 0;
	}
};

template<>
struct AccumulateTrait2<MyType>
{
	using AccT = MyType;

	static const AccT zero() // ע�����ﲻ���� constexpr �ؼ��֣�
	{
		return AccT{ 0, 0, 0 };
	}
};

// accum �����ɸ�Ϊ��
template<typename T>
auto accum2(T const* beg, T const* end)
{
	// return type is traits of the element type 
	using AccT = typename AccumulateTrait2<T>::AccT;

	//AccT total = AccumulateTrait<T>::zero; // ֵ��ȡ��
	AccT total = AccumulateTrait2<T>::zero(); // ���ﻻ�ɺ���

	while (beg != end) {
		total += *beg;
		++beg;
	}

	return total;
}

int main()
{

	char name[] = "hello world";
	int length = sizeof(name) - 1;
	std::cout << "accum = " << accum(name, name + length) << std::endl; // OK��accum = 1116;


	MyType a[3] = { { 1, 3, 4 },{ 1, 3, 4 },{ 1, 3, 4 } };

	for (int i = 0; i < 3; i++) {
		a[i].print();
		std::cout << std::endl;
	}

	MyType ret = accum2(a, a + 3 );
	ret.print();

	return 0;
}



