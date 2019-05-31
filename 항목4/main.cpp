/*�׸�4: ��ü�� ����ϱ� ���� �ݵ�� �� ��ü�� �ʱ�ȭ����*/

/*��������*/
/*�⺻���� Ÿ���� ��ü�� ���� ������ �ʱ�ȭ�մϴ�. ��쿡 ���� ������ �Ǳ⵵ �ϰ� �ȵǱ⵵ �ϱ� �����Դϴ�.*/

/*�����ڿ�����, ������ ����� ���� ���Թ��� ������ ���� ���ο� �ִ� ������� ����� �ʱ�ȭ�������� ��� �ʱ�ȭ
����Ʈ�� ��� ����սô�. �׸��� �ʱ�ȭ ����Ʈ�� ������ ����� ������ ���� Ŭ������ �� ������ ����� �����
������ �Ȱ��� �����սô�.*/

/*���� ���� ������ �ִ� ������ ���� ��ü���� �ʱ�ȭ ���� ������ ���ؼ� �����ؾ� �մϴ�. ������ ���� ��ü��
���� ���� ��ü�� �ٲٸ� �˴ϴ�.*/

#include <cstring>
#include <iostream>

class CInit {
private:
	//�⺻���� Ÿ���� ��쿡�� (������ �ȿ���) ���ԵǱ� ���� �ʱ�ȭ�Ǹ���� ������ ����.
	int				m_iVal;
	std::string		m_sName;
	int const		m_ciVal;	//���
	std::string&	m_csName;	//���۷���
public:
	CInit(int _ival, std::string _sName) :	m_iVal(_ival)	//�ʱ�ȭ ����Ʈ.
											,m_sName()
		
											//����� ���۷����� �ǹ������� �ʱ�ȭ ����Ʈ���� ���ش�.
											//���� ��ü�� �Ұ��� �ϴ�.
											, m_ciVal(_ival)
											, m_csName(_sName)
	{
		//�ʱ�ȭ�� �ƴ϶� �����̴�.
		//(�⺻ ���� Ÿ���� ��� �ʱ�ȭ�� ���Կ� �ɸ��� ����� ���̰� ����.)
		//m_ival=_ival;
		//m_sName=_sName;
	}
};

////////////////////////////����������������ü, ������������ü���ǹ�////////////////////////////
//��.����.����.��ü: ��������, Namespace������ ����, (�Լ����ο��� �������� ����)static ����.
//����.����.��ü: �Լ� ���ο��� static���� ����� ��ü

//<�ʱ�ȭ ��ġ>
//������.����.��ü�� �ʱ�ȭ ����:����-����-�������� ��������.
//������������:cpp���ϰ� �� �ȿ� #include�� ������ ���ϵ��� ����
//���� ������ü�� �ʱ�ȭ ����:�� ó�� ȣ�� ����

//1. ����											: ������ ���� ��ü(non-local-static-object)
//2. ���ӽ����̽� ��ȿ�������� ���ǵ� ��ü			: ������ ���� ��ü(non-local-static-object)
//3. Ŭ���� ���ο��� static���� ����� ��ü			: ������ ���� ��ü(non-local-static-object)
//4. �Լ� ���ο��� static���� ����� ��ü			: ���� ���� ��ü(local-static object)
//5. ���� ��ȿ �������� static���� ����� ��ü		: ������ ���� ��ü(non-local-static-object)

int iInt = 0;					//���� ��ü.
namespace nFirst
{
	int g_iInt = 0;				//Ŭ���� ���ο��� static���� ����� ��ü

	void output()
	{
		printf("vikFirst\n");
	}
}

class CSecond
{
private:
	static int m_iInt;					//Ŭ���� ���ο��� static���� ����� ��ü

	CSecond();
	CSecond(const CSecond&);
	CSecond& operator=(const CSecond&);
public:
	static CSecond* Instance()
	{
		static CSecond instance;		//�Լ� ���ο��� static���� ����� ��ü(����������ü)
		return &instance;
	}
};

////////////////////////////////������ ���� ��ü�� ����////////////////////////////////
//�� ���� ���� ��ü�� �ʱ�ȭ ������ ������ ���� �ʴ�.
//���� ������ ���� �������� �ִ�.
//ActionFirst.h
class CActionFirst
{
public:
	void output(void)
	{
		printf("CActionFirst::output\mn");
	}
};

//ActionSecond.h
extern CActionFirst ActionFirst;		//����ڰ� ���� �� ��ü
class CActionSecond
{
public:
	CActionSecond()
	{
		ActionFirst.output();
	}
};

//CActionSecond g_InitOrder;	//MNActionFirst�� ��ü�� ���� �������� �ʰ�,
//								//MNAActionSecond�� �����Ǹ� error
//								//(���ǵ��� ���� ��ü�� ���ٽõ� �߱� ������)

/////////////////////////////////������ ���� ��ü�� ������ �ذ�///////////////////////////////////
class ActionFirstModify
{
public:
	void output(void)
	{
		printf("CActionFirstModify\n");
	}
};
ActionFirstModify& actionFirstModify(void)
{
	//static���� ��ü ����
	static ActionFirstModify instance;
	return instance;
}

class CActionSecondModify
{
public:
	CActionSecondModify()
	{
		actionFirstModify().output();
	}
};
CActionSecondModify ActionSecondModify;

/////////////////////////////////�ʱ�ȭ ���� ����/////////////////////////////////
class CInitOrder
{
private:
	int m_iNum1;	//�ʱ�ȭ ������ ����� ������(����ʱ�ȭ����Ʈ�� ������ �ƴϴ�)
	int m_iNum2;
	int m_iNum3;
public:
	CInitOrder() :	m_iNum1(0)
					, m_iNum3(2)
					, m_iNum2(m_iNum3)	//������ ���� ��(�ʱ�ȭ ������ �ʱ�ȭ ����Ʈ ������ �ƴϴ�.)
	{
		printf("m_iNum1 == %d\n", m_iNum1);
		printf("m_iNum2 == %d\n", m_iNum2);
		printf("m_iNum3 == %d\n", m_iNum3);
	}
};

int main(void)
{
	CInitOrder InitOrder;
	system("pause");
	return 0;
}