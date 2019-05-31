/*
�׸�6: �����Ϸ��� ���� �Լ��� �ʿ� ������ Ȯ���� �̵��� ����� ���� ������

������ �Լ��� ���ʿ��Ҷ� ���� ���ϵ��� ���� ����?
��Ÿ�� ������ ����, ��ũ������ ������ ������ �ٲٱ� ����
*/

#include <iostream>

class CNoneCopy
{//���1 : ���� �����ڿ�, ������� ������ �Լ� ���ٱ����� ����
public:
	CNoneCopy() {};
private:
	CNoneCopy(CNoneCopy const&);				//���� �κ��� ������ ����(�Ϲ� ���ٽ� ������ ����)
	CNoneCopy& operator=(CNoneCopy const&) {}		//����Լ� or friend �Լ����� ���ٽ�(��ũ����)

};

class CUncopyable
{//���2 private�� ���
protected:	//���� Ŭ�������� ����ؾ� �ϹǷ� protected
	CUncopyable() {};
	virtual ~CUncopyable() {};

private:
	CUncopyable(const CUncopyable&);
	CUncopyable& operator=(const CUncopyable&) {}	//���ǹ��� ���ּ� ������ ������ �߻��ϰ� �����.
};

class CTest : private CUncopyable	//Uncopyable�� �Ļ� Ŭ����
{//���2
	//���� �����ڿ� ���Կ������� ����θ� �� ������.
public:
	CTest() {};
};

int main(void)
{
	CTest kFirst;
	CTest kSecond;

	kFirst = kSecond;	//private ����̱� ������ �ܺο��� Uncopyable ���� ���� �����ڸ� �����Ҽ� ����.
}