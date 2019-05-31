/*�׸� 07. �⺻ Ŭ������ �����Լ�*/

/*class Child : public std::string ����
virtual�� ���� string Ŭ������ ��ӹ�����
�Ҹ�� ������ �ڿ�, �ڷᱸ�� ����, ���� ¥���� ����� �߻��� �� �� �ִ�.
*/

/* class A
class B : public A
B kobj;	//�θ� Ŭ���� �Ҹ��ڿ� virtual�� ��� �θ� �ڽ� �Ҹ��� ���� ����ȴ�.
A* pkBase = new B;	//�θ� Ŭ������ �Ҹ��ڰ� ������, �ڽ� Ŭ������ �Ҹ��ڰ� ������� ����.
delete pkBase;
*/

#include <iostream>

class NoneVtbl
{
public:
	NoneVtbl() : m_iData(0)
	{

	}
	~NoneVtbl()
	{

	}
private:
	int m_iData;
};

class ExistVtbl
{//�����Լ��� 1���� ���� Ŭ������ ���� �Ҹ��ڸ� �������Ѵ�.
public:
	ExistVtbl() : m_iData(0)
	{
		std::cout << "ExistVtbl ������ ����" << std::endl;
	}
	virtual ~ExistVtbl()
	{
		std::cout << "ExistVtbl �Ҹ��� ����" << std::endl;
	}
private:
	int m_iData;
};

class ExistVtblChild : public ExistVtbl
{
public:
	ExistVtblChild()
	{
		std::cout << "ExistVtblChild ������ ����" << std::endl;
	}
	~ExistVtblChild()
	{
		std::cout << "ExistCtblChild �Ҹ��� ����" << std::endl;
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
class VBase
{//�߻� Ŭ���� ����� �ϳ�, ������ �ʿ��� ���� �����Լ��� ������
public:
	VBase() {};
	virtual ~VBase() = 0;	//�Ҹ��ڸ� ���� �����Լ��� ������
};

VBase::~VBase()
{
	std::cout << "VBase �Ҹ��� ����" << std::endl;
}

class NWChild : public VBase
{
public:
	NWChild() {};
	~NWChild() {};
};

int main(void)
{
	//���α׷� ����ȯ�濡 ���� vptr�� ũ��� ���� �ɼ��� �ִ�.
	//32bit-4byte
	//64bit-8byte
	std::cout << sizeof(NoneVtbl) << std::endl;		//int 1�� ũ��
	std::cout << sizeof(ExistVtbl) << std::endl;	//int 1��ũ�� + vptr ũ��

	/*
		virtual Ű���尡 �߰��Ǹ� class�� vtbl(�����Լ� ���̺�)�̶�
		������ �߰����� �ڷᱸ���� ���� �ȴ�.

		vtbl�̶�?
		�����ֿ� �־��� ��ü�� � �����Լ��� ȣ���ؾ� �ϴ��� �����ϴµ� ���̴� ������.
		
		�밳�� �����ͷ� �����Ǿ� �ֱ� ������ sizeof�� ���� üũ�� ����
		�������� ����ŭ size�� �����Ȱ��� �˼��� �ִ�.(�� ����)

		��ü�� � �����Լ��� ȣ��Ƿ��ϸ� ȣ��Ǵ� �����Լ���
		�� ��ü�� vptr�� ����Ű�� vtbl�� ���� �����ȴ�.
	*/

	{//class�� ���ο� vptr�� �����ϱ� ������ ��ó�� �޸� ���縦 �ϰ� �Ǹ�
		//vptr�� ������ ������ �ۿ� ����.(memcpy�� ��������)
		//��ü�� �޸� �����ϴ� �ٺ��������� ���� ����
		//memset �޸� �ʱ�ȭ keyword
		ExistVtbl* kTemp = new ExistVtblChild;
		::memset(&kTemp, 0, sizeof(kTemp));	//��ģ�� vtbl�� ���ư���.
		delete kTemp;

	}

	std::cout << std::endl << std::endl;
	NWChild Child;	//VBase::~VBase(){} �ּ��޸� error��
}