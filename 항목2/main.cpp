/*
02. define�� �����ŵ� const, enum, inline�� ���ø���.

#define ��ũ�δ� ��ó���⿡�� ���� �Ǳ� ������
�����Ϸ��� ���� üũ�� ���Ѵ�.
*/
#include <iostream>
#include <cstring>

//1. ���ڿ��� ����� �ٱ��� ������
#define TEST_MSG "viku"
char const* const STR_TESTMSG1 = "viku";	//�������� �Ϻ��� ���ȭ ������ ��� and ������ ���
std::string const STR_TESTMSG2("viku");	//���ڴٸ� char* ���� ����, ����ϱ� ���ϹǷ� �� ����.

void ConstExplain(void)
{// ������ ����ϴ� const�� ���� ����
	int							iVal1 = 0;		//����
	int		const				iVal2 = 0;		//���
	int		const&				riVal = 0;		//���
	int		const*				pival1 = 0;		//������ ����,	������ ���
	int*	const				pival2 = 0;		//������ ���,		������ ����
	int		const* const		pival3 = 0;		//������ ���,		������ ���

	// ������ ��� : ���� �ٲܼ� ����
	// ������ ��� : �ٸ����� ����ų �� ����

	// *�� �������� ������ const�� ������ ������ ����� ���� �ٲܼ�����
	// *�� �������� ������ const�� ������ ������ ����� �ٸ����� ����ų�� ����
}

//2. class�� ��� ����� �Բ� ����
class AvailConstPoiter_InitSuccess
{
private:
	static int const MAX_INDEX = 5;	//�������
									//�̷��� �ϸ� �ȵǴ� ����
									//�������Ϸ��� ������ �߻��� �� �ִ�.
									//����κп��� ���� �ʱ�ȭ �ϴ� ���� �ϰ����� ������ �ִ�.
	int m_iArr[MAX_INDEX];
};

//class�� ����, cpp����
class AvailConstPoiter_InitFail
{
private:
	static int const MAX_INDEX;	//��� ����
	//int m_iArr[MAX_INDEX];	//�迭 ���𿡼� error
};

//cpp�� ���� �ص� int m_iArr[MAX_INDEX]; ��������.
int const AvailConstPoiter_InitFail::MAX_INDEX = 10;	//��� ����(cpp�� ���� �ؾ���)

//enum�� Ȱ��
class AvailEnum
{
public:
	enum{MAX_INDEX = 5,};
private:
	int m_iArr[MAX_INDEX];
};

//3. define�� ����
#define VALUE_COMPARE(a,b) ((a)>(b) ? (a) : (b))

//(iNum1>iNum2) ����� ���� ���� �޶���
void showDefineProblem(void)
{
	int iNum1 = 5;
	int iNum2 = 0;
	std::cout << "���� �� " << iNum1 << std::endl;
	VALUE_COMPARE(++iNum1, iNum2);
	//(++iNum1)>(iNum2) ? (++iNum1) : (iNum2))�� �ǹǷ� �ι������ϰ� �ȴ�.
	std::cout << "�ι�����" << iNum1 << std::endl;

	VALUE_COMPARE(++iNum1, iNum2 + 10);
	std::cout << "�ѹ�����" << iNum1 << std::endl;	//iNum1�� �ѹ� ����
}

//define�� inlineȭ
//�Լ��� ����ȭ
inline void VALUECOMPARE(int const& iLhs, int const& iRhs)
{
	((iLhs) > (iRhs) ? (iLhs) : (iRhs));
}

void AvailInLine(void)
{
	int iNum1 = 5;
	int iNum2 = 0;

	std::cout << "������ " << iNum1 << std::endl;

	VALUECOMPARE(++iNum1, iNum2);	//iNum1�� �ѹ������ϰ� �ζ��� �Լ��� ��ü�ȴ�.
	std::cout << "�ѹ�����" << iNum1 << std::endl;

	VALUECOMPARE(++iNum1, iNum2);
	std::cout << "�ѹ�����" << iNum1 << std::endl;
}


///////////////////////////////////////////////
