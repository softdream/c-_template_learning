#include <iostream>
#include <vector>
#include <deque>
#include <cassert>

// ����ģ�����Ҳ��һ����ģ��

// �� 5.5 ���е� stack ģ�壬�������ʹ��Ĭ�ϵ��ڲ��������� std::deque����ô����Ҫ����ָ�� stack Ԫ�ص����͡�
// Ҳ����˵Ϊ��ָ���ڲ����������ͣ�����ͬʱָ�����������ͺ�Ԫ�� �����ͣ� 
// Stack<int, std::vector<int>> vStack; // integer stack that uses a vector

// ʹ��ģ�����ģ�壬������ Stack ��ģ���ʱ��Ϳ���ָֻ�����������Ͷ���ȥָ��������Ԫ�ص����ͣ� 
// Stack<int, std::vector> vStack; // integer stack that uses a vector

// Ϊ�˾���Ҫ�� Stack �Ķ����н��ڶ���ģ���������Ϊģ�����ģ�塣
// template<typename T, typename Container = std::vector<T>> �滻Ϊ��
template<typename T, 
template<typename Elem, typename Alloc = std::allocator<Elem>> class Container = std::vector>
// ����� Alloc ����ʡ�Բ�д
class Stack
{
	using Iterator = typename Container<T>::iterator;

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

	// ʹ��ģ�����ؿ�����ֵ���� ͬ����Ҫ��д
	template<typename T2, template<typename Elem2, 
			 typename Alloc2 = std::allocator<Elem2>> class Container2 >
		// ���� Alloc2 ��������ֿ���ʡ��
	const Stack& operator=(const Stack<T2, Container2> &rhs)
	{
		Stack<T2, Container2> tmp(rhs); // create a copy of the assigned stack 
		s.clear(); // remove existing elements 

		while (!tmp.empty()) { // copy all elements 
			s.push_front(tmp.top());
			tmp.pop();
		}

		return *this;
	}

private:
	Container<T> s;
};


int main()
{
	Stack<int, std::deque> s1;
	s1.push(10);
	s1.push(20);
	s1.push(30);
	s1.printStack();

	Stack<float, std::deque> s2;
	s2 = s1;
	s2.printStack();

	return 0;
}