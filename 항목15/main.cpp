/*�׸�15 : �ڿ� ���� Ŭ�������� �����Ǵ� �ڿ��� �ܺο��� ������ �� �ֵ��� ����

��������
���� �ڿ��� ���� �����ؾ� �ϴ� ���� API�鵵 ���� ������ RAII Ŭ������ ���� ����
�� Ŭ������ �����ϴ� �ڿ��� ���� �� �ִ� ����� ���� �־�� �մϴ�.

�ڿ� ������ ����� ��ȯ Ȥ�� �Ͻ��� ��ȯ�� ���� �����մϴ�. �������� ������ �����
��ȯ�� ��ü������ �� ������, �� ���Ǽ��� ���� ���� �Ͻ��� ��ȯ�� �I�����ϴ�.
*/

#include <iostream>


std::tr1::shared_ptr<Investment> pInv(createInvestment);	//�׸� 13���� ������ ����
int daysHeld(const Investment* pi);	//���ڱ��� ���Ե� ���ķ� ����� ����
int days = daysHeld(pInv);	//����!
/*
������ �� ������ daysHeld�Լ��� Investment* Ÿ������ ���� �����͸� ���ϴµ�,
tr1::shared_ptr<Investment> Ÿ���� ��ü�� �ѱ�� �����Դϴ�.
*/

/* ������ RAII Ŭ����(������ tr1::shared_ptr)�� ��ü�� �� ��ü�� ���ΰ� �ִ�
���� �ڿ�(Investment*)���� ��ȯ�� ����� �ʿ�������.
�ΰ��� ����� ����, ����� ��ȯ, �Ͻ��� ��ȯ
*/

/*����� ��ȯ�ϴ� ���(get)
get�Լ��� ����ϸ� �� Ÿ������ ���� ����Ʈ ������ ��ü�� ����ִ� ���� ������(�� �纻)�� ���� �ִ�.
int days = daysHeld(pInv.get());	//���� ���������ϴ�. pInv�� ����ִ� ���� �����͸� daysHeld�� �ѱ��.
*/

class Investment {		//���� ������ ���ڸ� �𵨸��� ���� Ŭ�������� �ֻ��� Ŭ����
public:
	bool isTaxFree() const;
};

Investment* createInvestment();	//���丮 �Լ�

std::tr1::shared_ptr<Investment> pi1(createInvestment());	//tr1::shared_ptr�� �ڿ������� �õ��� �մϴ�.

bool taxable1 = !(pi1->isTaxFree());	//operator->�� �Ἥ �ڿ��� �����մϴ�.

std::auto_ptr<Investment> pi2(createInvestment());	//auto_ptr�� �Ͽ��� �ڿ� ������ �õ��� �մϴ�.

bool taxable2 = !((*pi2).isTaxFree());	//operator*�� �Ἥ �ڿ��� �����մϴ�.

//////////////////////////////////////////////////////////////////////////////////////

FontHandle getFont();	//C API���� ������ �Ű������� ������ �����ϱ� ������ ����

void releaseFont(FontHandle fh);	//���� ���� C API���� ������ �Լ�

class Font {						//RAIIŬ����
private:
	FontHandle f;					//���� ��Ʈ �ڿ�
public:
	explicit Font(FontHandle fh)	//�ڿ��� ŉ���մϴ�. ���⼭ ���� ���� ������ ����Ǵ°Ϳ� 
									//�����ϼ���. �ڿ� ������ C API�� �ϱ� �����̺��.
		: f(fh)
	{

	}
	~Font()
	{
		releaseFont(f);
	}
	FontHandle get() const	//����� ��ȯ �Լ�
	{
		return f;
	}
};

void changeFontSize(FontHandle f, int newSize);	//��Ʈ API�� �Ϻ�
Font f(getFont());
int newFontSize;

changeFontSize(f.get(), newFontSize);	//Font���� FontHandle�� ��������� �ٲ��Ŀ� �ѱ�ϴ�.


/*FontHandle���� �Ͻ��� ��ȯ �Լ�
class Font
{
public:
	operator FontHandle() const	//�Ͻ��� ��ȯ �Լ�
	{
		return f;
	}
}
*/

Font f(getFont());
int newFontSize();
changeFontSize(f, newFontSize);	//Font���� FontHandle�� �Ͻ��� ��ȯ�� �����մϴ�.


/*�Ͻ��� ��ȯ�� ���� �Ǽ��� ������ ������ ��������.
Font f1(getFont());
FontHandle f2 = f1;	//�����ǵ��� Font��ü�� �����ϴ� ���̾��µ�, �����ϰԵ� f1�� FontHandle�� �ٱͰ� ���� ����Ǿ� ���ȴ�.
�̷��� �Ǹ� f2�� f1�� �����ϴ� �ڿ��� ����Ҽ� �ְ� �Ǵµ�, f1�� �Ҹ��ϰ� �Ǹ� f2�� ������ ��Ʈ�� �Ŵ޷��ִ� ���̵ȴ�.
*/

int main(void)
{
	
}