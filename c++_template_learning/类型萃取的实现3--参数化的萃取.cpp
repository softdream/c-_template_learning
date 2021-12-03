#include <iostream>

// ��ǰ�漸���У��� accum()��ʹ�õ���ȡ����Ϊ�̶��ģ�fixed����������Ϊһ�������˽������ȡ��
// ���㷨�����Ͳ����Ա��滻��������ĳЩ����£���һ����д��overriding����Ϊȴ���������������ġ�
// ���磬���ǿ�������֪��ĳһ�� float ��ֵ�ĺͿ��Ա���ȫ�ش洢�� һ�� float �����У�
// �������������ֻ����һЩ���ܵ�������

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


// Ϊ�˽����һ���⣬����Ϊ��ȡ����һ���µ�ģ����� AT����Ĭ��ֵ����ȡģ�����:
template<typename T, typename AT = AccumulateTrait<T>>
auto accum(T const* beg, T const* end)
{
	typename AT::AccT total = AT::zero();

	while (beg != end) {
		total += *beg;
		++beg;
	}

	return total;
}

// �������ַ�ʽ��һ�����û����Ժ��Ե�����ģ���������������Щ��������������û����� �ǿ���ָ��һ���µ�������ȡ��Ĭ������;

int main()
{
	int a[3] = { 1, 2, 3 };
	std::cout << "accum = " << accum(a, a + 3) << std::endl; // OK��accum = 6;

	return 0;

}
