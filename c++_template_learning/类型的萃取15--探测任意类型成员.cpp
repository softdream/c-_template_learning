#include <iostream>
#include <type_traits> // for true_type, false_type, and void_t

// �ڶ��������� HasSizeTypeT ����ȡ֮�����ǻ����Ȼ���뵽����ν�����ȡ���������Զ� �������Ƶ����ͳ�Ա��̽�⡣
// Ŀǰ��һ����ֻ��ͨ������ʵ�֣���Ϊ��û�����Ի��ƿ��Ա�����������Ǳ�ڡ� �����֡���ǰ��ʹ�ú�ġ���ù�����ӽ��ķ�����ʹ�÷��� lambda��

// ���µĺ�����������ǵ�����
#define DEFINE_HAS_MEMBER(Member) \
template<typename, typename = std::void_t<>> \
struct HasMemberT_##Member \
: std::false_type { }; \
template<typename T> \
struct HasMemberT_##Member<T, std::void_t<decltype(&T::Member)>> \
: std::true_type { } // ; intentionally skipped

int main()
{

	return 0;
}