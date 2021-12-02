#include <iostream>

// ʹ�����õ��ã�Call-By-Reference����һ��ԭ���ǿ��ԶԲ�����������ת����Perfect Forward��;
// �������ס��ʹ��ת������ʱ��Forwarding Reference���������һ��ģ���������ֵ���ã�rvalue Reference������
// �����Լ�����Ĺ���;

// ����һ��
// ��������д���Խ��������͵Ĳ������ݸ�ת�����ã����Һ������İ����ô���һ����
// �����ᴴ�������ݲ����ı��ݣ�
template<typename T>
void passR(T&& arg) // ע�ⰴ�ա�Effective Mordern C++����д���������--�������ã�
{ 
	std::cout << "typeof arg = " << typeid(arg).name() << std::endl;
}

int main()
{
	std::string s = "hi"; 
	std::string returnString();
	passR(s); // OK: T deduced as std::string& (also the type of arg) 
	passR(std::string("hi")); // OK: T deduced as std::string, arg is std::string&& 
	//passR(returnString()); // OK: T deduced as std::string, arg is std::string&& 
	passR(std::move(s)); // OK: T deduced as std::string, arg is std::string&& 
	int arr[4];
	passR(arr); // OK: T deduced as int(&)[4] (also the type of arg��

	// ���ǣ���������������ƶϵ����������ܻᵼ�����벻���Ľ����
	std::string const c = "hi"; 
	passR(c); //OK: T deduced as std::string const& 
	passR("hi"); //OK: T deduced as char const(&)[3] (also the type of arg) 
	int arr[4]; passR(arr); //OK: T deduced as int (&)[4] (also the type of arg)
	// ��������������У��������� passR()�ڲ��� arg �����͵�֪�����ݵĲ�����һ����ֵ ��rvalue��
	// ����һ�� const ���߷� const ����ֵ��lvalue��������Ψһһ�ֿ��Դ���һ�������� 
	// ������������������������ķ���


	return 0;
}