#ifdef DEBUG 

#include <iostream>

/* ���� 1 ��򵥵ĺ���ģ�壺���������е����ֵ */
template<typename T>
T max(T a, T b)
{
	return a < b ? b : a;
}

int main()
{
	// ���� 1 ����
	std::cout << "max(2, 5) = " << max(2, 5) << std::endl;

	return 0;
}

#endif 