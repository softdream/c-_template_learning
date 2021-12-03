#include <iostream>

// Ϊ��ʵ���ۻ����ԣ�accumulation policy��������ѡ�� SumPolicy �� MultPolicy ʵ��Ϊ�г�Աģ��ĳ����ࡣ
// ��һ��ʹ����ģ����Ʋ�����ӿڵķ�ʽ����ʱ�Ϳ��Ա�����ģ��ģ�����ʹ�ã�template template arguments��;
// ���ǿ��Խ� SumPolicy ��дΪ����ģ�壺

template<typename T>
struct AccumulateTrait;

template<>
struct AccumulateTrait<char>
{
	using AccT = int;
	static constexpr AccT zero()
	{
		return 0;
	}
};

template<>
struct AccumulateTrait<short>
{
	using AccT = int;
	static constexpr AccT zero()
	{
		return 0;
	}
};

template<>
struct AccumulateTrait<int>
{
	using AccT = long;
	static constexpr AccT zero()
	{
		return 0;
	}
};

template<>
struct AccumulateTrait<unsigned int>
{
	using AccT = unsigned long;
	static constexpr AccT zero()
	{
		return 0;
	}
};

template<>
struct AccumulateTrait<float>
{
	using AccT = double;

	static constexpr AccT zero()
	{
		return 0;
	}
};

template<typename T1, typename T2>
class SumPolicy 
{ 
public: 
	static void accumulate(T1& total, T2 const& value) 
	{ 
		total += value; 
	}
};

// ��ʱ�Ϳ��Ե��� Accum������ʹ��һ��ģ��ģ�����:
// ͨ��ģ��ģ��������ʲ��������Ҫ�����ǣ���һ��������ͨ��һ��������ģ�����������
// Я��һЩ״̬��Ϣ�������һЩ������ static ���ݳ�Ա��;
// ģ��ģ�����������һ��ȱ���ǣ���������뱻ʵ��Ϊģ�壬����ģ�������������ǵĽӿ�������Ĳ���һ����
// ����ܻ�ʹ��ȡ����ı������ڷ�ģ�����ø�������Ҳ������Ȼ��
template<typename T, 
		 template<typename, typename> 
		 class Policy = SumPolicy, 
		 typename Traits = AccumulateTrait<T>>
auto accum(T const* beg, T const* end)
{
	using AccT = typename Traits::AccT;
	AccT total = Traits::zero();

	while (beg != end) {
		Policy<AccT, T>::accumulate(total, *beg);
		++beg;
	}

	return total;
}

int main()
{
	// create array of 5 integer values 
	int num[] = { 1, 2, 3, 4, 5 };
	// print product of all values 
	std::cout << "the product of the integer values is " << accum<int, SumPolicy>(num, num + 5) << std::endl;
	
	return 0;
}