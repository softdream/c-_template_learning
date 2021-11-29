#include <iostream>

/* ���� 2 ģ�������ƶ� */


/* ���������е����ֵ*/
template<typename T>
T max1(T& a, T& b) // ���ʹ�����ô��Σ��κ�����ת�����ǲ��������
{
	std::cout << "type of a = " << typeid(a).name() << std::endl
	std::cout << "type of b = " << typeid(b).name() << std::endl;

	return a < b ? b : a;
}

template<typename T>
T max2(T a, T b) // �����ֵ���ݣ��������˻���decay�����ּ򵥵�����ת����
{				 // decay��ָ��const �� volatile ���Ʒ��ᱻ���ԣ����ñ�ת���ɱ����õ����ͣ�
				 // raw array �ͺ�����ת��Ϊ��Ӧ��ָ�����͡�
	std::cout << "type of a = " << typeid(a).name() << std::endl;
	std::cout << "type of b = " << typeid(b).name() << std::endl;

	return a < b ? b : a;
}

int main()
{
	// ���� 2 ����
	
	const int& a = 40;
	const int& b = 20;

	std::cout<<typeid(a).name()<<std::endl;

	max1(a, b);
	max2(a, b);

	return 0;
}