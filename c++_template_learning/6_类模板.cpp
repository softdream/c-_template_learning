#include <iostream>
#include <vector>
#include <cassert>

/* ��ģ���̽--�� stack Ϊ�� */

// ������������ Stack<T>�� ���� T ��ģ�����
template<typename T>
class Stack
{
public:
	Stack()
	{
		std::cout << "-------------- Template Stack ------------" << std::endl;
	}

	// ע�⣺ģ�����ֻ��Ҫ�ṩ��Щ�ᱻ�õ��Ĳ����������ǿ��ܻᱻ�õ��Ĳ�����
	void push(const T &elem)
	{
		s.push_back( elem );
	}

	void pop()
	{
		assert( !s.empty() );

		s.pop_back();
	}

	const T& top()
	{
		assert(!s.empty());

		return s.back();
	}

	bool empty() const
	{
		return s.empty();
	}

	void printStack() const
	{
		for (auto it : s) {
			std::cout << it << std::endl;
		}
	}

private:
	// ����ģ���ڲ���T ��������ͨ����һ��������������Ա�����ͳ�Ա����;
	std::vector<T> s;
};

// ���ζ�����ģ���ػ�:���Զ���ģ���ĳһ��ģ����������ػ�
// ��ģ���"�ػ�"�������Ƕ�ĳһ�ض��������Ż�������ȥ������ģ�����ĳһ�ض�����ʵ����֮�����Ϊ;
template<> // Ϊ���ػ�һ����ģ�壬����ģ��������ǰ����Ҫ��һ�� template<>��������Ҫָ����ϣ���ػ�������
class Stack<std::string>
{
public:
	Stack()
	{
		std::cout << "-------------- Template Stack Full Specialization ------------" << std::endl;
	}

	void push(const std::string &elem)
	{
		s.push_back(elem);
	}

	void pop()
	{
		assert(!s.empty());

		s.pop_back();
	}

	const std::string& top()
	{
		assert(!s.empty());

		return s.back();
	}

	bool empty() const
	{
		return s.empty();
	}

	void printStack() const
	{
		for (auto it : s) {
			std::cout << it.c_str() << std::endl;
		}
	}

private:
	// ���ڱ��ػ���ģ�壬���г�Ա�����Ķ��嶼Ӧ�ñ�����ɡ����桱��Ա������Ҳ����˵���� ���� T �ĵط�����Ӧ�ñ��滻�������ػ���ģ�������
	std::vector<std::string> s; 
};


// ����������ģ��ƫ�ػ��������ػ���:��ģ�����ֻ�����ֵ��������������Ϳ���ΪĳЩ��������ṩ�����ʵ�֣�����ʹ���߻���Ҫ����һ����ģ�����
template<typename T> 
class Stack<T*> // ������һ����Ȼ�Ǳ����� T �����������Ǳ��ػ���������ָ�����ģ�壨Stack<T*>��
{
public:

	Stack()
	{
		std::cout << "-------------- Template Stack Partial Specialization ------------" << std::endl;
	}

	void push(T* elem)
	{
		s.push_back(elem);
	}

	void pop()
	{
		assert(!s.empty());

		s.pop_back();
	}

	const T* top()
	{
		assert(!s.empty());

		return s.back();
	}

	bool empty() const
	{
		return s.empty();
	}

	void printStack() const
	{
		for (auto it : s) {
			std::cout << *it << std::endl;
		}
	}

private:
	std::vector<T*> s;
};


int main()
{
	// ֱ�� C++17����ʹ����ģ���ʱ����Ҫ��ʽ��ָ��ģ�����;
	Stack<int> s; // ͨ������ Stack<int>���ͣ�����ģ���ڲ� int �ᱻ�������� T;
				  // ��ʵ����֮�����ģ�����ͣ�Stack<int>֮�ࣩ������������������һ��ʹ��


	// ע�⣺ģ�庯����ģ���Ա����ֻ���ڱ����õ�ʱ��Ż�ʵ����
	for (int i = 0; i < 10; i ++ ){
		s.push(i);
	}
	
	s.printStack();

	Stack<std::string> s1;
	s1.push("hello ");
	s1.push("world ");
	s1.push(" !");

	s1.printStack();

	Stack<int*> s2;
	int i1 = 10;
	int i2 = 20;
	int i3 = 30;
	int i4 = 40;
	s2.push( &i1 );
	s2.push(&i2);
	s2.push(&i3);
	s2.push(&i4);

	s2.printStack();

	return 0;
}
