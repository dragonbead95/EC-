/*
#include <iostream>

using std::cout;
using std::endl;

class Bitmap
{

};

class Widget
{
private:
	Bitmap* pb;
public:
	Widget& operator=(const Widget& rhs)
	{
		delete pb;
		pb = new Bitmap(*rhs.pb);
		return *this;
	}
};

int main(void)
{
	Widget a;
	Widget b;
	a = b;

	return 0;
}
*/

/*�׸�11 operator=������ �ڱ���Կ� ���� ó���� ������ �ʵ��� ����
��������
operator=�� �����Ҷ�, � ��ü�� �� �ڽſ� ���ԵǴ� ��츦 ����� ó���ϵ��� ����ô�.
���� ��ü�� ������ ��ü�� �ּҸ� ���ص� �ǰ�, ������ ������ ������ ������ �� �� ������
���� �� �¹ٲٱ� ����� �ᵵ �˴ϴ�.

�� �� �̻��� ��ü�� ���� �����ϴ� �Լ��� �ִٸ�, �� �Լ��� �Ѱ����� ��ü���� ���
���� ��ü�� ��쿡 ��Ȯ�ϰ� �����ϴ��� Ȯ���� ������.
*/

/*
�ڱ���Կ� ���� ���� �̷����̴�.
	kObj = kObj;

	�̿� ���� ���� ���� ������ ����
	���� ���� ������ �ϴ���
	
	�̻���� ���ư��� ���ڴ� �ֱ��(�翬�� �ֱ�)
	�Ʒ��� ���� ������ rhs�� ��ü �ڽ��϶� ������ �� �� ����.

	CBase& operator=(CBase const& rhs)	//rhs '=='this(�ڱ������ ���)
	{
		delete m_piVal;						//���� �̹� �����µ�.
		m_pIval = new int(*rhs.m_piVal);	//�̹� ��������� ������ �����°�?
		return *this;
	}

	//���� �Ʒ��� ���� �����Ǿ�� �ڱ� ���Կ��� �����ϴ�.
	CBase& operator=(CBase const& rhs)		//�ڱ� ������ �Ͼ ���
	{
		int* piTemp = m_pIVal;				//�ڱ� ��ü�� �ӽ�����
		m_pIval = new int(*rhs.m_piVal);	//�ڱ� ��ü�� �纻�� ����
											//���������� �Ͼ��
		delete piTemp;						//�ӽ÷� ������ ��ü ����
		piTemp = NULL;
		return *this;
	}

	�� if(this==&rhs)	//�̿� ���� �ּҰ��� ���� ���ʿ��� ������ ���̴� ����� �ִ�.(��ġ�� �˻�)
	{
		return *this;
	}

	swap�Լ��� �����Ѵٸ� ������ ���� �ϴ� ����� �ִ�.
	CBase& operator=(CBase const& rhs)
	{
		CBase kTemp(rhs);	//��ü����
		swap(kTemp);		//swap
		return *this;
	}

	�� �ڵ带 �ѹ��� ���̸�
	CBase& operator=(CBase rhs)	//call by value�� ��ü ����
	{
		swap(rhs);				//swap
		return *this;
	}
*/l