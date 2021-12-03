#include <iostream>

// ��ĿǰΪֹ���ǲ�û�������ۻ���accumulation������ͣ�summation������������Ҳ������������������ۻ���
// ���磬���ǿ��Զ�һ����ֵ���������˵�������Щֵ���ַ����Ļ��� ���ǿ��Խ���������������
// ��ʹ����һ�����������ֵ�����⣬Ҳ����ת����һ���ۻ����⡣ 
// ��������Щ�����У�Ψһ��Ҫ��õĲ����� accum()�е� total += *beg��
// ���ǿ��Գ���һ����Ϊ�ۻ�������һ�����ԣ�policy����

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

template<typename T, typename Policy = SumPolicy, typename Traits = AccumulateTrait<T>>
auto accum(T const* beg, T const* end) {
	using AccT = typename Traits::AccT;
	AccT total = Traits::zero(); 
	while (beg != end) { 
		Policy::accumulate(total, *beg); 
		++beg;
	}
	return total;
}

// ����һ��� accum()�У�SumPolicy ��һ�������࣬Ҳ����һ��ͨ��Ԥ���̶��õĽӿڣ�Ϊ�㷨ʵ����һ���������Ե��ࡣ
// SumPolicy ���Ա�ʵ�ֳ���������
class SumPolicy {
public: 
	template<typename T1, typename T2> 
	static void accumulate(T1& total, T2 const& value) { 
		total += value; 
	} 
};

// ����ṩһ����ͬ�Ĳ��Զ���ֵ�����ۻ��Ļ������ǿ��Լ�����ȫ��ͬ�����顣
// ���翼�����������������ͼ����һ����ֵ�ĳ˻���
class MultPolicy
{ 
public:
	template<typename T1, typename T2>
	static void accumulate(T1& total, T2 const& value) {
		total *= value; 
	}
};

// Ҫ��һ�����������ڶԲ�������һ���ʵ�ʹ�����������ƣ�����Ӧ����һЩ������ĳ������ ��ģ��������¶�������Ϊ���ࣻ
// ���Ժ���ȡ�кܶ�����֮����ֻ�����Ǹ���������Ϊ�����������͡�
// Ҫ����� ��ȡ�ࣺһ����������ģ��������ࡣ��Ϊһ���࣬�����������õ����ͺͳ�����
// ��Ϊһ��ģ�壬��Ϊʵ��һ�����Խ�������������ġ�������м�㡱�ṩ�˷�����

int main() 
{ 
	// create array of 5 integer values 
	int num[] = { 1, 2, 3, 4, 5 }; 
	// print product of all values 
	std::cout << "the product of the integer values is " << accum<int,MultPolicy>(num, num+5) << std::endl; 
	// ��ӡ����ǣ�the product of the integer values is 0
	// ���ǲ��Եġ�����������ǶԳ�ʼֵ��ѡȡ����Ȼ 0 �ܺܺõ�������͵����󣬵���ȴ����������˻�����ʼֵ 0 ���ó˻��Ľ��Ҳ�� 0����
	// ��˵����ͬ����ȡ�Ͳ��Կ��ܻ��໥Ӱ�졣


	return 0;
}
