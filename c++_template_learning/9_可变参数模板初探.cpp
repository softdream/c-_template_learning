#include <iostream>

// �ɱ����ģ�壺�� C++11 ��ʼ��ģ����Խ���һ�������ɱ�Ĳ����������Ϳ����ڲ��������Ͳ������Ͷ���ȷ���������ʹ��ģ�壻

// ��һ����κ���ģ��
// Ϊ�˽����ݹ飬�����˲����ܲ����ķ�ģ�庯�� print()�������ڲ�����Ϊ�յ�ʱ�򱻵���;
void print()  // �ݹ��˳�������
{
	std::cout << std::endl;
}

// typename... Types ��ģ���������template parameter pack��
template<typename T, typename... Types>
void print(T firstArg, Types... args) {
	// ������ͨ������һ���������������� �Ϳ����ȴ�ӡ��һ��������Ȼ���ٵݹ�ĵ��� print()����ӡʣ��Ĳ���
	std::cout << firstArg << ", "; //print first argument 

	// C++11 Ϊ���ģ��������һ���µ� sizeof �������sizeof...�����ᱻ��չ�ɲ��������������Ĳ�����Ŀ��
	std::cout << "sizeof...(args): " << sizeof...(args) << std::endl;

	// ��Щ����Ϊ args ��ʣ���������һ��������������function parameter pack��
	print(args...); // call print() for remaining arguments 
}

// ��һҲ����д�ɣ�
template<typename T>
void print2( T arg )
{
	std::cout << arg << ", ";
}

template<typename T, typename... Types>
void print2(T firstArg, Types... args)
{
	print2( firstArg );
	print2( args... ); // ������������ģ�������ֻ����β���Ĳ�������ʱ�򣬻�����ѡ��û��β������������һ������ģ��
	std::cout << std::endl;
}

// Ҫ��һ���ɱ����ģ���һ����Ҫ��������ת���������ͺ������Ĳ�����
// Ҫ���������ת�����в���֮�⣬��������Щ������顣����������ǵ�ֵ��

// �ɱ����ģ��Ҳ֧����ģ�壬����std::tuple
template<typename... Values> 
class tuple; // �������

template<>
class tuple<> // һ����ģ�����������Ϊ�ݹ��������
{

};

// tuple��̳г���֮���������������tuple�࣬�Դ����ƣ����ռ̳пղ�����tuple������ǵݹ�̳з�ʽ��
// �������ڴ��еķֲ����ڴ����ȴ洢����ı�����Ա���ٱ�������ı�����Ա;
template<typename Head, typename... Tail>
class tuple<Head, Tail...> : private tuple<Tail...> // ����ģ���������ͨ���̳���ʵ�ֵ�
{
	typedef tuple<Tail...> inherited;
public:
	tuple() 
	{
	
	}

	tuple(Head v, Tail... vtail) : m_head(v), inherited(vtail...) 
	{
	
	}

	Head& head() { 
		return m_head; 
	}

	// tail()�������ص��Ǹ�����󣬸����������������ڴ���ʼ��ַ��ʵ��һ���ģ���˷���*this����ǿ��ת��Ϊinherited����
	inherited& tail() { 
		return *this; 
	}

protected:
	Head m_head;
};


int main()
{
	print( 20, 19.8, 9.8 );
	print2(20, 19.8, 9.8);

	std::string s = "hello";
	tuple<int, float, std::string> t(1, 2.3, s);
	std::cout << t.head() << " " << t.tail().head()  << std::endl;


	return 0;
}