/*�׸�3 : ������ ���̸� const�� ���̴� ����*/

/*��������*/
/*const�� �ٿ� �����ϸ� �����Ϸ��� ������ ������ ��Ƴ��µ� ������ �ݴϴ�. const
�� � ��ȿ������ �ִ� ��ü���� ���� �� ������, �Լ� �Ű����� �� ��ȯ Ÿ�Կ��� ����
�� ������, ��� �Լ����� ���� �� �ֽ��ϴ�.*/
/*�����Ϸ� �ʿ��� ���� ��Ʈ���� ������� ��Ŀ�� ������, �������� ��������(������)
������� ����ؼ� ���α׷����ؾ� �մϴ�.*/
/*��� ��� �� ���� ��� �Լ��� ��������� ���� �Ȱ��� �����Ǿ� ���� ����� �ڵ� �ߺ���
���ϴ� ���� ������, �̶� ���� ������ ��� ������ ȣ���ϵ��� ���弼��.*/

#include <iostream>
#include <cstring>
#include <vector>

//1. ���ڿ��� ������ �ٲܶ� ������
#define TEST_MSG "Yiku"
char const* const STR_TESTMSG1 = "Yiku";	//1-1, ���� ���ȭ, �������� ���ȭ�� ��������
std::string const STR_TESTMSG2("Yiku");		//1-2 char* ���� string ��ü�� ����ϴ� ����, ����ϱ� ���ϴ�.

char g_strText[] = "Hello";						//���� ������, ����������
char* g_pDataPtr = g_strText;					//���� ������, ����������
const char* g_pCDataPtr = g_strText;			//���� ������, ���������
char* const g_pDataCPtr = g_strText;			//��� ������, ����������
const char* const g_pCDataCPtr = g_strText;		//��� ������, ���������


//////////////////////////////////////////////�ڵ��ǹ��� ��������////////////////////////////////////////////////
class COverLapCode
{
private:
	std::string m_sName;
public:
	explicit COverLapCode(std::string _sName) : m_sName(_sName)
	{

	}

	const char& operator[](std::size_t uiPos) const	//�ڵ� �ߺ�(�ڵ� �ǹ��� ����)
	{
		return m_sName[uiPos];
	}

	char& operator[](std::size_t uiPos)				// �ڵ� �ߺ�(�ڵ� �ǹ��� ����)
	{
		return m_sName[uiPos];
	}
};

//////////////////////////////////////////////�ڵ��ǹ��� ���� ���� ���////////////////////////////////////////////////
class COverLapCodeImprove
{
private:
	std::string m_sName;
public:
	//explicit�� �ڵ� �� ��ȯ�� �����ִ� Ű�����̴�.
	explicit COverLapCodeImprove(std::string _sName) : m_sName(_sName)
	{

	}

	const char& operator[](std::size_t uiPos) const						//��� ��ü�� ���� operator[]
	{
		return m_sName[uiPos];
	}

	char& operator[](std::size_t uiPos)									//��� ���� op[]�� ȣ���ϰ� ��
	{
		return
			const_cast<char&>											//op[]�� ��ȯ Ÿ�Կ� ĳ������ ���� const�� �����ϰ� char&�� �ٲ۴�.
			(static_cast<const COverLapCodeImprove&>					//*this�� Ÿ�Կ� const�� ���Դϴ�.
			(*this)[uiPos]);											//op[]�� ��� ������ ȣ���մϴ�.
	}
};

//////////////////////////////��� �Լ��� ���ȭ �ǹ�////////////////////////////////////////
//�ǹ� ù��°:������ �����
class CPhysical
{
private:
	char* m_cpName;
public:
	CPhysical(const char* _cpName) : m_cpName(NULL)
	{
		m_cpName = new char[sizeof(_cpName)];
		strcpy_s(m_cpName,sizeof(_cpName),_cpName);
	}

	//��������(�׷��� ��Ʈ ���� ����� �־�� ���Ǵ�)operator[]����
	char& operator[](std::size_t uiPos) const
	{
		return m_cpName[uiPos];
	}
};

//�ǹ� �ι�°:���� �����
class Clogical
{
private:
	const char* m_cpName;
	mutable std::size_t m_uiPos;		//mutable�� ������ ������� ��� ��쿡�� ������ �����ϴ�.
	mutable bool m_bLengthCheck;		//(������ ��� ��� �Լ� �ȿ����� ������ �� �ֽ��ϴ�.

public:
	explicit Clogical(const char* _cpName) : m_cpName(_cpName),m_uiPos(), m_bLengthCheck(false)
	{

	}

	std::size_t length() const
	{
		if (!m_bLengthCheck)
		{
			m_uiPos = std::strlen(m_cpName);	//const ��� �Լ� ���ο��� ������
			m_bLengthCheck = true;
		}
		return m_uiPos;
	}
};

class CMultiplication
{
private:
	int m_iNum;
public:
	CMultiplication(int iNum) : m_iNum(iNum) 
	{

	}

	//operator* ���ϰ��� const�� ���ش�.
	const CMultiplication& operator*(const CMultiplication Input)
	{
		m_iNum *= Input.getNum();
		return *this;
	}

	//�⺻ �޸ٺ��� get
	int getNum(void) const
	{
		return m_iNum;
	}
};

int main(void)
{
	//STL �ݺ��ڿ��� const ��� ���
	std::vector<int> vInt;
	vInt.push_back(1);

	//��� ������, �� ��� ������
	const std::vector<int>::iterator iter = vInt.begin();
	*iter = 10;	//����
	//++iter;	//error

	//���� ������, ��� ������
	std::vector<int>::const_iterator cIter = vInt.begin();
	//*cIter = 10;	//error
	++cIter;		//����

	//operator* ���ϰ��� const��
	CMultiplication A(2);
	CMultiplication B(4);
	CMultiplication C(6);
	//(A*B)=C;	//error ���(A*B)���ٰ� operator*�� �߱� ������

	//�ڵ� �ǹ��� ���� ���� ���
	const COverLapCodeImprove cCodeMonster("Dron");
	std::cout << cCodeMonster[0] << std::endl;
	//cCodeMonster[0]='H';		//error

	COverLapCodeImprove CodeMonster("Mutal");
	std::cout << CodeMonster[0] << std::endl;
	CodeMonster[0] = 'H';		//�� ���� ��

	//��� �Լ��� ��� ������ ���� �ǹ�
	//1. ������ ������� ����
	const CPhysical Physical("Physical");
	//const ��ü�� const ����Լ��ε�, ���� ����ȴ�.(������ ����� const error)
	//const ����Լ��ȿ��� ���游 ���� �ʴ´ٸ� �ܺο��� ������ �ص� ������� ����� ���ܳ��ϴ�.
	Physical[0] = 'H';
	std::cout << Physical[0] << std::endl;
	char* pc = &Physical[0];
	*pc = 'c';
	std::cout << Physical[0] << std::endl;


	//2. ���� �����
	Clogical Logical("MNLogical");
	std::cout << "Logical Str Length" << Logical.length() << std::endl;

	system("pause");
	return 0;
}