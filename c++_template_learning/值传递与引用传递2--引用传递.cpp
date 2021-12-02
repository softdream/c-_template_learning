#include <iostream>
#include <string>

// �����ô��ݲ��´��������Ϊ�βν����ñ����ݵ�ʵ�Σ���
// ���Ұ����ô���ʱ��������Ҳ�����˻���decay��;
// ������������������¶���ʹ�ð����ô��ݣ���ʹ����ʹ�õĵط�����ʱ���ƶϳ�����ģ���������Ҳ������������⡣

// ����һ���� const ���ô��ݣ�
// Ϊ�˱��⣨����Ҫ�ģ��������ڴ��ݷ���ʱ������Ϊ����ʱ������ʹ�� const ���ô��ݣ�
template<typename T> 
void printR1(T const& arg) // ���ģ����Զ���´�������ݶ��󣨲��ܿ����ɱ��Ǹ߻��ǵͣ���
{
	std::cout << "typeof arg = " << typeid(arg).name() << std::endl;
}

// Ҫ��һ�������ô��ݲ���ʱ�������Ͳ����˻���decay����
// Ҳ����˵�����������ת��Ϊָ�룬Ҳ�����Ƴ� const �� volatile �����Ʒ���
// �������ڵ��ò���������Ϊ T const &�����ƶϳ�����ģ ����� T �����ͽ������� const��
// �����ζ���

// ������������ const ���ô��ݣ�
// �����ͨ�����ò��������ر���ֵ�������޸ı����ݱ�����ֵ����
// ����Ҫʹ�÷� const ���� ��Ҫô��ʹ��ָ�룩��
// ͬ����ʱ��Ҳ���´�������ݵĲ����������õĺ���ģ�����ֱ�ӷ��ʱ����ݵĲ���;
template<typename T> 
void outR(T& arg) 
{ 
	std::cout << "typeof arg = " << typeid(arg).name() << std::endl;

	// �������ﴫ�ݵķ� const ���͵������飬������Ҳ���� decay��
	// �����Ϳ����޸�������Ԫ�ص�ֵ��Ҳ���Դ�������ĳ��ȡ�
	if (std::is_array<T>::value) { 
		std::cout << "got array of " << std::extent<T>::value << " elems" << std::endl;
	}
}

// �����壺
// ������ֹ��� const Ӧ�ô��� const ����������ѡ��:
// 1. ʹ�� static_assert ����һ�������ڴ���:
template<typename T> 
void outR1(T& arg)
{
	static_assert(!std::is_const<T>::value, "out parameter of foo<T>(T&) is const"); 
	std::cout << "typeof arg = " << typeid(arg).name() << std::endl;
 }
// 2. ͨ��ʹ�� std::enable_if<>���ø�����µ�ģ�壺
template<typename T, typename = std::enable_if_t<!std::is_const<T>::value>>
void outR2(T& arg) 
{
	std::cout << "typeof arg = " << typeid(arg).name() << std::endl;
}

int main()
{
	// ����һ��
	std::string returnString();
	std::string s = "hi"; 
	printR1(s); // no copy 
	printR1(std::string("hi")); // no copy 
	//printR1(returnString); // no copy // ��仰���в��ˣ�����֣�
	printR1(std::move(s)); // no copy

	std::cout << "------------------------------------" << std::endl;
	// ���ζ���
	std::string const c = "hi"; 
	printR1(c); // T deduced as std::string, arg is std::string const&��
	printR1("hi"); // T deduced as char[3], arg is char const(&)[3]��
	int arr[4]; 
	printR1(arr); // T deduced as int[4], arg is int const(&)[4]��

	std::cout << "------------------------------------" << std::endl;
	// ������
	outR(s); //OK: T deduced as std::string, arg is std::string&��
	// ע����� outR()��ͨ����������ʱ������prvalue������ͨ�� std::move()��������Ѵ��ڵı�����xvalue�������������
	//outR(std::string("hi")); //ERROR: not allowed to pass a temporary (prvalue)��
	//outR(returnString()); // ERROR: not allowed to pass a temporary (prvalue)��
	//outR(std::move(s)); // ERROR: not allowed to pass an xvalue��

	// ͬ�����Դ��ݷ� const ���͵������飬������Ҳ���� decay�� 
	outR(arr); // OK: T deduced as int[4], arg is int(&)[4];

	std::cout << "------------------------------------" << std::endl;
	// �����ģ�
	// ��ʱ������ݵĲ����� const �ģ�arg �����;��п��ܱ��ƶ�Ϊ const ���ã�
	// Ҳ����˵��ʱ���Դ���һ����ֵ��rvalue����Ϊ����������ģ���������Ĳ�������ȴ����ֵ��lvalue����
	
	const int d = 100;
	// ���������ϻὫ d �ƶ�Ϊ const int, �������н������ int������֡�
	outR(d); // OK: T deduced as int const; 
	outR(std::move(d)); // OK: T deduced as int; 
	//outR(100); //���ﱨ��error C2664: ��void outR<int>(T &)��: �޷������� 1 �ӡ�int��ת��Ϊ��int &����
	
	// ������:
	//outR1(d); //���˱�����assert������ error C2338: out parameter of foo<T>(T&) is const��
	//outR2(d); // ���� SFINAE�� �����ھͲ�ͨ��

	return 0;
}