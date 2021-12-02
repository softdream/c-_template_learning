#include <iostream>
#include <string>
#include <type_traits>

// ����Ҫ����������ǣ������ݵ�ģ����������Ͳ���ȷ��ʱ�򣨱��粻�� std::string ���߿� ��ת���� std::string �����ͣ����������¹��캯��ģ��;

// ����
class Person 
{
	template<typename T>
	using EnableIfString = std::enable_if_t<std::is_convertible<T, std::string>::value>;

	// ����ʹ��Ҫ������֮�������ʽת���� std::is_convertible<> ֮��,������ʹ�� std::is_constructible<>��
	// ��Ҫ���������ʽת��������ʼ����������Ҫע�����,���Ĳ���˳��� std::is_convertible<>�෴�� 
	// template<typename T> 
	// using EnableIfString = std::enable_if_t<std::is_constructible<std::string, T>::value>;

public: 
	// generic constructor for passed initial name: 
	template<typename STR, typename = EnableIfString<STR>> 
	// ע������ STR &&n �Ǹ��������ã�
	explicit Person(STR&& n) : name(std::forward<STR>(n)) 
	{ 
		std::cout << "TMPL-CONSTR for ��" << name << "��\n"; 
	}
	
	// copy constructor: 
	Person (Person const& p) : name(p.name) 
	{ 
		std::cout << "COPY-CONSTR Person ��" << name << "��\n"; 
	}
	
	// move constructor
	Person (Person&& p) : name(std::move(p.name)) 
	{ 
		std::cout << "MOVE-CONSTR Person ��" << name << "��\n"; 
	} 

private:
	std::string name;
};

// ע�����ǲ���ͨ��ʹ�� enable_if<>������ copy/move ���캯���Լ���ֵ���캯����
// ������Ϊ��Ա����ģ�岻�ᱻ���������Ա��������Ȼ������Ĭ�Ϲ��캯������
// ��������Ҫʹ�� copy ���캯���ĵط�����Ӧ�ĳ�Ա����ģ��ᱻ���Ե���

// ���磺 
class C 
{
public: 
	C()
	{
		std::cout << "default constructor" << std::endl;
	}

	// ģ�忽�����캯��
	template<typename T>
	C(T const& rhs) 
	{
		std::cout << "tmpl copy constructor" << std::endl;
	}
};

int main()
{
	std::string s = "sname";
	Person p1(s); // init with string object => calls TMPL-CONSTR

	Person p2("tmp"); // init with string literal => calls TMPL-CONSTR

	Person p3(p1); // OK => calls COPY-CONSTR 
	
	// std::move ����ֵ p1 ת��Ϊ��ֵ���������� �ƶ����캯��
	Person p4(std::move(p1)); // OK => calls MOVE-CONST
	
	C c;
	C d(c); // ������ԶҲ������õ�ģ�忽�����캯����

	return 0;
}