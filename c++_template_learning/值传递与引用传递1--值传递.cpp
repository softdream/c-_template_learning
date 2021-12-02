#include <iostream>

// ����ֵ���ݲ���ʱ��ԭ�������еĲ������ᱻ������
// ���ÿһ�����������Ǳ�����ʵ�ε�һ �ݿ�����
// ���� class �Ķ��󣬲�����ͨ�� class �Ŀ������캯��������ʼ����

// ���ÿ������캯���ĳɱ����ܸܺߡ������ж��ַ������Ա��ⰴֵ���ݵĸ߰��ɱ���
// ��ʵ�� ����������ͨ���ƶ����壨move semantics�����Ż�������Ŀ�����
// ������ʹ�ǶԸ������� �Ŀ�������ɱ�Ҳ����ܸߡ�

// ��һ��
template<typename T> 
void printV(T arg) 
{
	std::cout << "arg = " << arg.c_str() << std::endl;
}

// Ҫ��һ������ֵ���ݲ���ʱ���������ͻ��˻���decay���� 
// Ҳ����˵����������˻���ָ�룬const �� volatile �����Ʒ��ᱻɾ��;
// ��һ��Ϊ�̳��� C ���ԣ������ŵ�Ҳ��ȱ�㡣
// ͨ������򻯶Ա������ַ��������Ĵ���
// ����ȱ������ printV()�ڲ��޷����ֱ����ݵ���һ�������ָ�뻹��һ���洢һ����������;
template<typename T>
void printV2(T arg)
{
	std::cout << "type of arg = " << typeid(arg).name() << std::endl;
}


int main()
{
	std::string s = "hi";
	
	// ���ﱻ���ݵĲ�������ֵ��lvalue������˿������캯���ᱻ���ã�
	printV( s ); // �ڴ����ַ���ʱ��arg ��� s ��һ�ݿ�����
				 // ��ʱ��һ������ͨ�� std::string �Ŀ������캯���� ���ģ�
				 // ����ܻ���һ���ɱ��ܸߵĲ�������Ϊ��������������Դ������һ�������
				 // ����Ҫ�����㹻���ڴ����洢�ַ�����ֵ��

	// ���ǲ��������е����������ÿ������캯��:
	// �����������������ݵĲ����Ǵ���ֵ��prvalue��pure right value����ʱ�������ĳ�������ķ���ֵ����
	// ��ʱ���������Ż��������ݣ�ʹ�ÿ������캯�����ᱻ���á�
	printV(std::string("hi")); //copying usually optimized away (if not, move constructor);
	printV(std::move(s)); // move constructor
	// �� C++17 ��ʼ��C++��׼Ҫ����һ�Ż��������뱻ʵ�֡�
	// �� C++17 ֮ǰ�����������û���Ż�����һ�࿽����������Ӧ���ȳ���ʹ���ƶ����壬
	// ��ͨ��Ҳ��ʹ�����ɱ���ñȽϵ�����

	std::cout << "---------------------------------" << std::endl;

	std::string const c = "hello";
	printV2(c); // c decays so that arg has type std::string;
	printV2("hello"); //decays to pointer so that arg has type char const*;
	int arr[4]; 
	printV2(arr); // decays to pointer so that arg has type int *;

	return 0;
}