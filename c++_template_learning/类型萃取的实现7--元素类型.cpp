#include <iostream>
#include <list>
#include <vector>

// ���������кܶ������ģ�壬���� std::vector<>�� std::list<>��Ҳ���԰����������顣
// ����ϣ���õ�����һ�����ͺ�����������һ����������ʱ�������Է�����Ӧ��Ԫ�����͡�
// �����ͨ��ƫ�ػ�ʵ��:
// ƫ�ػ���ʹ��ʹ�����ǿ������������Ͳ�֪���������ͺ������ڵ������ȥʵ�����ͺ���;

template<typename T> 
struct ElementT; // primary template 

template<typename T>
struct ElementT<std::vector<T>> 
{ 
	//partial specialization for std::vector 
	using Type = T; 
};

template<typename T> 
struct ElementT<std::list<T>> 
{ 
	//partial specialization for std::list 
	using Type = T; 
};

template<typename T, std::size_t N> 
struct ElementT<T[N]> 
{ 
	//partial specialization for arrays of known bounds
	using Type = T;
};

template<typename T> 
struct ElementT<T[]> 
{ 
	//partial specialization for arrays of unknown bounds 
	using Type = T; 
};

template<typename T>
void printElementType(T const& c) 
{ 
	std::cout << "Container of " << typeid(typename ElementT<T>::Type).name() << " elements.\n";
}

int main() 
{ 
	std::vector<bool> s; 
	printElementType(s);
	int arr[42]; 
	printElementType(arr);
	return 0;
}