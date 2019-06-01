/*�׸�12: ��ü�� ��� �κ��� �������� ��������
��������
��ü ���� �Լ��� �־��� ��ü�� ��� ������ ��� �� ��� �⺻ Ŭ���� �κ��� ���帮�� ����
�����ؾ� �մϴ�.

Ŭ������ ���� �Լ� �� ���� ������ ��, ������ �̿��ؼ� �ٸ� ���� �����Ϸ��� �õ��� �����
����������. �� ���, ����� ������ ��3�� �Լ����� �и��� ���� ���ʿ��� �̰��� ȣ���ϰ� ����
�ذ��սô�.


*/

/*
������ �ϸ� ���� ������, ���� ���� ������ �ΰ��� ���÷��� �Ѵ�.
�� �ΰ��� �����Լ��� �Ѵ�.
*/
#include <iostream>

class CBase
{
private:
	int m_iVal;
public:
	CBase() :m_iVal(0)
	{}
	CBase(int const iVal) : m_iVal(iVal)
	{}

	CBase(CBase const& rhs)
	{//���������
		m_iVal = rhs.m_iVal;
	}

	virtual ~CBase()
	{

	}

	CBase& operator=(CBase const& rhs)
	{//������Կ�����
		m_iVal = rhs.m_iVal;
		return *this;
	}
	virtual void vPrintInfo()
	{
		std::cout << m_iVal << std::endl;
	}
};

class CDerived : public CBase
{
private:
	float m_fVal;
public:
	CDerived(int const iVal, float const fVal)
		:CBase(iVal), m_fVal(fVal)
	{

	}

	CDerived(CDerived const& rhs)
	{//���� ������
		m_fVal = rhs.m_fVal;
	}

	virtual ~CDerived()
	{

	}

	CDerived& operator=(CDerived const& rhs)
	{//���� ���� ������
		m_fVal = rhs.m_fVal;
		return *this;
	}
	virtual void vPrintInfo()
	{
		CBase::vPrintInfo();
		std::cout << m_fVal << std::endl;
	}
};

int main(void)
{
	CDerived kObj(1, 2.5f);
	CDerived kObj1(3, 4.5f);

	kObj = kObj1;	//���� ���� ������
	kObj.vPrintInfo();	//����� "3,4.5"�� ��µɱ�?
	std::cout << std::endl;	/*������ : 1 4.5*/

	CDerived kObj2(kObj1);	//���������
	kObj.vPrintInfo();	//����� "3,4.5"�� �ɰ�?
						/*0 4.5*/
	
	/*
		�� ������ ���� �ذ�å�� �Ʒ��� ����.
		CDerived(CDerived const& rhs)
			: CBase(rhs)
		{//���������
			m_fVal = rhs.m_fVal;
		}

		CDerived& operator=(Cderived const& rhs)
		{
			CBase::operator=(rhs);
			m_fVal = rhs.m_fVal;
			return *this;
		}

		���⿡ �ߺ��ڵ�� ��� �Ѱ��� �ϰ� �ʹٰ� �ؼ�
		��������ڿ��� ���� �����ڷ� ȣ���Ѵٰų�
		������ �ȵƴµ� ���縦 �Ѵٴ°� ��ü�� ���� �ȵȴ�.
		�ݴ�� ���Կ����ڿ��� ��������ڸ� ȣ���ϴ� �͵� ���� �ȵȴ�.
		�̹� �����ߴµ� �� �����ڸ� �¿�°� �¾ �ֺ��� ���� ������� ������� ���̴�.

		private������ Init��¼�� ���� �̸����� ���� �κ��� ��� ȣ���ϴ°��� �����ϴ�.
		������ void CopyFrom(typename const& T)�� ���� ���뼺�� �̾� �۾��ϱ⿡�� �������  �����.
		(���� Ʋ�������� �ִ�.)

	*/

	return 0;
}