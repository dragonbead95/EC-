/*�׸�10:���� �����ڴ� *this�� �����ڸ� ��ȯ�ϰ� ����
��������
���� �����ڴ� *this�� ������ ��ȯ�ϵ��� ���弼��

��?
�ϰ����� ������ ������

���ʰ� ���� ������ �ƽ���?
������ �ʰ� �ڵ带 �ۼ��ϴ��� �������� �ȵȴٰų� �ϴ°��� �ƴմϴ�.

������ �� ���ʴ� ��� �⺻ ���� Ÿ�Ե��� ������,ǥ�� ���̺귯���� ���� ��� Ÿ��
(string, vector, complex, trl::shared_ptr ��)������ ������ �ִٴ� ���� ���� ���� ���Դϴ�.

���¿� ����� �ٸ����� �ɾ���� ��â�� ���� ������ ���ٸ�
��ĥ�ϰ� ���� �ʾƵ� ������ ��̰� ���� �� �ֽ��ϴ�.
*/

#include <iostream>
using std::cout;
using std::endl;

class CBase
{
private:
	int m_iVal;
public:
	CBase() : m_iVal(0)
	{

	}

	CBase& operator=(CBase const& rhs)
	{//1. *this�� ��ȯ �ϴ� ����
		this->m_iVal = rhs.m_iVal;
		return *this;
	}

	CBase& operator=(int irhs)
	{//1. *this�� ��ȯ�ϴ� ����
		m_iVal = irhs;
		return *this;
	}

	void output(void)
	{
		cout << m_iVal << endl;
	}
};

int main(void)
{//class�� ������ Ÿ���̱� ������ ���� int�� ���� �����ϰ� �ϸ�ȴ�.
	//�Ʒ��� int�� ���Կ������� ���õ� ������ �ϴ� �κ��̸�,
	//�ڽ��� ������ ��ȯ�ϴ��� �׽�Ʈ �غ��� �ִ� �����̴�.

	int iVal = 0;

	//1�� iVal�� =�����ڸ� �̿��Ͽ� ������� ������ ��ȯ���� �����ڸ� �̿��Ͽ� �ٽ� 10�� �ִ´�.
	//���� =�����ڿ��� *this�� ��ȯ���� �ʴ´ٸ� 10�� ���� �� �������Դϴ�.
	(iVal = 1) = 10;
	cout << iVal << endl;

	(iVal += 1) = 20;
	cout << iVal << endl;

	(iVal -= 1) = 30;
	cout << iVal << endl;

	(iVal *= 1) = 40;
	cout << iVal << endl;

	(iVal /= 1) = 50;
	cout << iVal << endl;
}