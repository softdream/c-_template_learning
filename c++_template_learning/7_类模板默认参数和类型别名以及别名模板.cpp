#include <iostream>
#include <vector>
#include <cassert>
#include <deque>

/* ��ģ��Ĭ�ϲ��������ͱ����Լ�����ģ�壨ģ�������Alias Templates��--�� stack Ϊ�� */

// �ͺ���ģ��һ����Ҳ���Ը���ģ���ģ�����ָ��Ĭ��ֵ
template<typename T, typename Container = std::vector<T>>
class Stack
{
	using Iterator = typename Container::iterator; 

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

private:

	//std::vector<T> s; // �滻�ɣ�
	Container s;
};


// Ҫ�㣺ͨ������ģ�嶨��һ���µ����֣�����ʹ��ģ���ʹ�ñ�ø�����
// ����һ��ʹ�� typedef �ؼ���
typedef Stack<int> IntStack; // ���ǳ�����������ʽΪ typedef�� ����������ֽ��� typedef-name

// ��������ʹ�� using �ؼ��֣�c++11��
using DoubleStack = Stack<double>; // ��һ���̽��� alias declaration

// �������ָ�һ���Ѿ����ڵ����Ͷ��������ֵķ�ʽ������Ϊ type alias declaration���µ����ֱ���Ϊ type alias;

// ����ģ���龰һ����ͬ�� typedef�� alias declaration Ҳ���Ա�ģ�廯�������Ϳ��Ը�һ������ȡһ����������֡�
// ��һ���Դ� C++11 ��ʼ��Ч�������� alias templates������ģ�壩��
template<typename T> 
using DequeStack = Stack<T, std::deque<T>>; // DequeStack �� ģ��Stack<T, std::deque<T>>��һ��������Ԫ������ T ��Ȼδ֪��
											// ֻ�ǻ���һ��Ƥ��ע������ͱ������ֿ�����
// DequeStack<int>�� Stack<int, std::deque<int>> �������ͬһ�����͡�

// ʹ�� alias templates ���Ժܷ���ĸ���ģ��ĳ�Ա���Ͷ���һ����ݷ�ʽ

// ����ģ���龰����ʹ�� alias templates ���Ժܷ���ĸ���ģ��ĳ�Ա���Ͷ���һ����ݷ�ʽ
template<typename T>
using StackIterator = typename Stack<T>::Iterator; // ע������Ҫ�� typename

// ������ ���� std::vector<T>�У�
template<typename T>
using VectorIterator = typename std::vector<T>::iterator;

int main()
{
	
	Stack<int> s; 

	for (int i = 0; i < 10; i++) {
		s.push(i);
	}

	s.printStack();
	
	// stack of doubles using a std::deque<> to manage the elements
	Stack<double, std::deque<double>> s2;

	for (double i = 10; i < 100; i += 10.0) {
		s2.push( i );
	}
	s2.printStack();

	std::cout << "type of IntStack : " << typeid(IntStack).name() << std::endl;
	std::cout << "type of DoubleStack : " << typeid(DoubleStack).name() << std::endl;

	std::vector<int> vec = { 1, 2, 3, 4, 5, 6 };
	VectorIterator<int> iter = vec.begin(); // ���� VectorIterator ���� std::vector<T>::iterator��һ��������
	for (; iter != vec.end(); iter++) {
		std::cout << *iter << std::endl;
	}

	return 0;
}
