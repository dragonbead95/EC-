/*
�׸�5 : C++�� ���۽�½ ����� ȣ���� ������ �Լ��鿡 �˰��� ������

Ŭ������ ����� ������ �Լ��� ����.
�⺻������, ���������, ���� ���� ������, �Ҹ���

����Ʈ ���� ������ ����. ���� ���� ������.
����Ʈ ���� ���� ������ ����->���۷��� ���簡 ���ǵǾ� ���� ����

*/

#include <iostream>

class CEmpty 
{//�Ʒ��� class���� ���������� ����� �Լ� 4��
public:
	//Ŭ������ ����� ������ �Լ�
	//����Ʈ �����ڴ� public ���ټ��� ������ inline �Լ��̴�.
	//CEmpty(){}								//������
	//~CEmpty(){}								//�Ҹ���
	//CEmpty(CEmpty const& rhs){}				//���� ������
	//CEmpty& operator=(CEmpty const& rhs){}	//���� ���� ������

	CEmpty(std::string& sStr) : m_iId(0), m_piId(NULL), m_sStr(sStr) {}
	~CEmpty() { delete m_piId;}
	//CEmpty& operator=(CEmpty const& rhs){return *this;};

	void output()
	{
		std::cout << m_sStr.c_str() << std::endl;
	}
	//�ʱ�ȭ
	void initialize()
	{
		m_piId = new int;
		*m_piId = 10;
	}
private:
	int m_iId;
	int* m_piId;
	std::string& m_sStr;
};

int main(void)
{
	std::string str = "abc";
	CEmpty Emp1(str);
	//Emp1.initialize();	//error ���� ���翡 ���� ����
	Emp1.output();
	CEmpty Emp1Copy(Emp1);
	Emp1Copy.output();
	str += "d";
	Emp1Copy.output();

	//<error- Ŭ���� ���� ���۷��� ������� 
	//�����, ����Ʈ ���� ������ ������ ����>
	CEmpty Emp2(Emp1);	//����Ʈ ���� �����ڴ� ��������.
						//����Ʈ ���� �����ڴ� ��������ȿ� ���۷��� ������ �ִ��� �������� ���� �� �ִ�.
						//������ ���� ���� �����ڿ��� ��ü�� ���۷��� ������ �ִٸ� ������ �߻��ϰ� �ȴ�.
						//�� ������ �ذ��Ϸ��� ���� ���� �����ڸ� ���� �����ؾ� �Ѵ�.
	str += "e";
	Emp2.output();
	//Emp2=Emp1		//����Ʈ ���� ���� ������ ���� �ȵ�(�����Ϸ� ���� �߻�)
					// �����ڿ� ���� �⺻���� ���� ������ ���ǵ��� �ʾұ� ������ ���� �����ؾ� �Ѵ�.
	return 0;
}