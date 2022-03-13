#include <iostream>

template<typename ...Args>
class Test
{
public:
	Test()
	{
		std::cout << "Test �����汾 ... this : " << this <<std::endl;
	}
};

template<typename First, typename ...Others>
class Test<First, Others...> : private Test<Others...>
{
public:
	Test()
	{
		std::cout << "-------------------------------------" << std::endl;
		std::cout << "Test ƫ�ػ��汾 ... this : " << this << std::endl;
		std::cout << "type of First = " << typeid(First).name() << std::endl;
	}
};

template<>
class Base<>
{

};

template <typename ...Args>
class Base
{
public:
	Base()
	{
		std::cout << "Base �����汾 ... this : " << this << std::endl;
	}
};

template <typename First, typename ...Others>
class Base<First, Others ...> : private Base<Others ...>
{
public:
	Base(const First &value, const Others... args) : value_(value), Base<Others ...>(args ...)
	{
		std::cout << "-------------- Base ƫ�ػ��汾 ---------------" << std::endl;
		std::cout << "��ַ��" << this << std::endl;
		std::cout << "value �ĵ�ַ��" << &this->value_ << std::endl;
		std::cout << "type of value = " << typeid(value_).name() << std::endl;
		std::cout << "value : " << value_ << std::endl;
		std::cout << "----------------------------------------------" << std::endl;
	}

private:
	First value_ = 0;
};

int main()
{
	//Test<int, float, double> t;
	Base<int, float, double> t(30, 40.1f, 50.3);
	std::cout << "����ĵ�ַ��" << &t << std::endl;

	return 0;
}

