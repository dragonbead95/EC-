/*
explicit-> ������ ��ȯ�� ����
������ ��ȯ�� �� ���ƾ� �ϴ°�?
const Reference type�� ��ü�� �ӽð�ü�� ����ų ��츦 ��ġ�Ҽ� �ִ�.
explicit�� Ÿ�� ��ȯ�� �����ش�.
explicit�� ����ؼ� ������ ��ü ��ȯ�� �ϴ°��� �����ش�.
������ ��ü ��ȯ�� ����Ҷ� ��ȯ�� ��ü�� ��� ������ ��� ��ü�� 2���̻�
���� ����������ִ�.

NoneExplicit const & koneExplc = 0'
NoneExplicit ���� ��� Ŭ������ �ִٸ�, ���� ����� �� Ŀ����.
*/

#include <iostream>

class CBase
{
public:
	CBase();
};

class CNoneExplicit : CBase
{
public:
	CNoneExplicit(int iData)
	{
		std::cout << "NoneExplicit�� �������Դϴ�." << std::endl;
	}

	CNoneExplicit(CNoneExplicit const& rhs)
	{
		std::cout << "NoneExplicit�� ���� �������Դϴ�." << std::endl;
	}

	CNoneExplicit& operator=(CNoneExplicit const& rhs)
	{
		std::cout << "NoneExplicit�� ���� �������Դϴ�." << std::endl;
		return *this;
	}

	void test() const
	{
		std::cout << "text" << std::endl;
	}
};

class CExplicit
{
public:
	explicit CExplicit(int iData)
	{
		std::cout << "Explicit ������ : ���� ������� �����ڸ� ���ؼ��� ������ �����մϴ�." << std::endl;
	}

	explicit CExplicit(CExplicit const& rhs)
	{
		std::cout << "Explicit�� ���� �������Դϴ�." << std::endl;
	}
	
	CExplicit& operator=(CExplicit const& rhs)
	{
		std::cout << "Explicit�� ���� �������Դϴ�." << std::endl;
		return *this;
	}
};

void explctFunc(CExplicit const& kExplct)
{//explicit

}

void noneExplctFunc(CNoneExplicit const& kNoneExplict)	//const�� ���� error - �ӽ� ��ü�� ���۷����� ���������� const ����
{//none explicit
	//�ӽð�ü�� ����Լ��� ȣ���Ѵ�.
	kNoneExplict.test();
}

int main(void)
{
	{
		CNoneExplicit kNoneExplct = 10;		//������
		CNoneExplicit kTemp = kNoneExplct;	//���������
		kTemp = kNoneExplct;				//���� ���Կ�����
		noneExplctFunc(10);					//Ŭ���� �����ڿ� �ӽ� ��ü�� �־ ������ �ȳ���.
	}

	std::cout << std::endl << std::endl;

	{
		CExplicit kExplct(10);				//����� ȣ��
		//CExplicit kExplct = 10;			//������ error

		CExplicit kTempCopy(kExplct);		//
		//CExplicit kTempCopy = kExplct		//���� ������ error
		kTempCopy = kExplct;				//������Կ�����

		//explctFunc(10);					//error
	}

	system("pause");
	return 0;
}