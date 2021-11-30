#include <iostream>
#include <cassert>

// ���ں���ģ�����ģ�壬��ģ�������һ���ǵ���ĳ�־�������ͣ�Ҳ�����ǳ�����ֵ��
// �Է�����ģ������������Ĳ��������ͣ�����ĳ����ֵ

// ������ջΪ��
template<typename T, int Size = 10> // �ڶ����µ�ģ����� Size �� int ���͵�,�Է�����ģ�������Ҳ����ָ��Ĭ��ֵ;
class Stack
{
public:
	void push(const T &elem)
	{
		assert( nums < Size );

		s[nums] = elem;
		nums++;
	}

	void pop()
	{
		assert( !isEmpty() );
		nums--;
	}

	const T& top()
	{
		assert(!isEmpty());
		return s[ nums - 1 ];
	}

	bool isEmpty() const
	{
		return nums == 0;
	}

	const int size() const
	{
		return nums;
	}

	void printStack() const
	{
		for (int i = 0; i < nums; i++) {
			std::cout << s[i] << std::endl;
		}
	}

private:
	int nums = 0;
	T s[Size];
};

// Ҫ��һ��ʹ�÷�����ģ������������Ƶġ�ͨ������ֻ�������γ���������ö�٣���ָ�� objects/functions/members ��ָ�룬objects ���� functions ����ֵ���ã������� std::nullptr_t �������� nullptr����
// Ҫ�������������ֵ���� class ���͵Ķ��󶼲�����Ϊ������ģ�����ʹ��;
// Ҫ�����������ݶ����ָ�����������Ϊģ�����ʱ�����������ַ�����������ʱ�����������ݳ� Ա�Լ������Ӷ���

int main()
{
	// Ϊ��ʹ�������ģ�壬��Ҫͬʱָ�� Stack ��Ԫ�ص����ͺ� Stack ���������
	Stack<int, 10> stack;
	for (int i = 10; i <= 50; i += 10) {
		stack.push( i );
	}
	stack.printStack();

	return 0;
}