#include <iostream>

// ��Ա����ģ��Ҳ���Ա�ȫ�����߲��ֵ���������

class BoolString {
private:
	std::string value;
public: 
	BoolString(std::string const& s) : value(s) 
	{
	
	}
	
	template<typename T = std::string>
	T get() const { // get value (converted to T)
		std::cout << "default template function " << std::endl;
		return value; 
	}

	template<>
	bool get<bool>() const { // ȫ�ػ�
		std::cout << "Full Specifilized Template Function " << std::endl;
		return value == "true" || value == "1" || value == "on";
	}
};

int main()
{
	BoolString a("true");

	std::cout << a.get<bool>() << std::endl; // ������õ����ػ��汾

	BoolString b("hello");
	std::cout << b.get().c_str() << std::endl; // ������õ�����ͨ�汾

	return 0;
}