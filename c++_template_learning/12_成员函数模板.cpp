#include <iostream>
#include <deque>
#include <cassert>

// ��ĳ�ԱҲ������ģ�壬��Ƕ����ͳ�Ա������������ -- ��ջΪ��
// ���ڵ����⣺ͨ��ֻ�е����� stack ������ͬ��ʱ��ſ����໥��ֵ��stack ��������ͬ˵�����ǵ�Ԫ������Ҳ��ͬ����
// ��ʹ���� stack ��Ԫ������֮�������ʽת���� Ҳ�����໥��ֵ��
// ����취��
// ֻҪ����ֵ����������ģ�壬�Ϳ��Խ�����Ԫ�����Ϳ�����ת���� stack �໥��ֵ
template<typename T>
class Stack
{
public:
	Stack()
	{
		std::cout << "-------------- Template Stack ------------" << std::endl;
	}

	void push(const T &elem)
	{
		s.push_back(elem);
	}

	void pop()
	{
		assert(!s.empty());

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

	// ʹ�ó�Աģ�庯�����ؿ�����ֵ����
	template<typename T2>
	const Stack& operator=(const Stack<T2> &rhs)
	{
		Stack<T2> tmp(rhs); // create a copy of the assigned stack 
		s.clear(); // remove existing elements 
		
		while (!tmp.empty()) { // copy all elements 
			s.push_front(tmp.top()); 
			tmp.pop(); 
		}
		
		return *this;
	}

private:
	std::deque<T> s;
};

int main()
{
	Stack<int> intStack;
	intStack.push(10);
	intStack.push(20);
	intStack.push(30);
	Stack<float> floatStack;

	floatStack = intStack; // OK: stacks have different types, 
						   // but int converts to float
	// �����ĸ�ֵ�Ͳ���ı� floatStack �����ͣ�Ҳ����ı�����Ԫ�ص����͡�
	// �ڸ�ֵ֮�� floatStack �洢��Ԫ����Ȼ�� float ���ͣ�top()���ص�ֵҲ��Ȼ�� float ���͡�

	floatStack.printStack();

	return 0;
}