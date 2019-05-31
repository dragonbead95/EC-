//�׸�08:���ܰ� �Ҹ��ڸ� ������ ���ϵ��� �ٵ�� ����
/*��������
�Ҹ��ڿ����� ���ܰ� ���������� �� �˴ϴ�. ���� �Ҹ��� �ȿ��� ȣ��� �Լ��� ���ܸ�
���� ���ɼ��� �ִٸ�, � �����̵��� �Ҹ��ڿ��� ��� �޾Ƴ� �Ŀ� ���� �������� ���α׷���
�������� �ؾ� �մϴ�.

� Ŭ������ ������ ����Ǵٰ� ���� ���ܿ� ���� ����ڰ� �����ؾ� �� �ʿ䰡 �ִٸ�,
�ش� ������ �����ϴ� �Լ��� �ݵ�� ������ �Լ�(��, �Ҹ��ڰ� �ƴ� �Լ�)�̾�� �Ѵ�.
*/

//�̱��� �ڵ� �Ҹ�
//�Ҹ��ڿ��� �߻��� ���ܴ� �Ҹ��ڿ��� ó��

#include <iostream>
using std::cout;
using std::endl;

class MNSingleton
{
private:
	MNSingleton(void){}
	MNSingleton(MNSingleton const&);
	MNSingleton operator=(MNSingleton const&);
public:
	static MNSingleton* instance()		//�̱���
	{
		static MNSingleton instance;
		return &instance;
	}
	void close()				//���ҽ� �Ҹ�
	{
		cout << "MNSingleton ���ҽ� �Ҹ�" << endl;
	}
};

class MNSingletonMgr
{
public:
	MNSingletonMgr(MNSingleton* _Singleton) : m_pSingleton(_Singleton)
	{

	}
	~MNSingletonMgr(void)
	{
		m_pSingleton->close();	//������� ������ ������ ���ܽ�Ű�� ���
	}
private:
	MNSingleton* m_pSingleton;
};

void SingletonAutoDelete(void)
{
	MNSingletonMgr SingleMgr(MNSingleton::instance());
	//MNSingleton::instance()->close();	//��Ͽ��� �������� �ڵ� �Ҹ��� ���ش�.
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

class widget
{
private:
	bool m_bClosed;
public:
	widget() :m_bClosed(false)
	{

	}

	void close(void)
	{
		//������ ����Լ�.
		//
		//�� �Ҹ��� �Ҹ��ڿ��� ���ϰ� ����Լ����� �ϴ°�?
		//���ܸ� ����Ű�� �Ҹ��ڴ� ������ź�̳� ����������
		//���α׷��� �ҿ��� ����
		//Ȥ�� ������ ������ ������ �����ϰ� �ֱ� �����̴�.

		//Database�� �Ҹ��Ų��.
		//Database�� �Ҹ��� �����ϸ� throw�� ���ܸ� �߻�

		//Database�� �Ҹ��� �������̸� true�� ����
		//m_bClosed=true;
	}

	~widget()
	{
		//���⼭�� ó���� ���ϸ� ���ܰ� ���������� ������ ���߽�ų�� �ִ�.
		//�׷��� ������ �����ϱ� ���ؼ� �� if���� �ۼ��� ���̴�.
		//�׷��� �Ҹ��ڿ��� �߻��� ���ܴ� �Ҹ��ڿ��� ó���ؾ� �Ѵ�.
		if (!m_bClosed)
		{
			//Database ������ ������ ���� ���(�޸� �Ҹ��� �̷������ �ʾ��� ���).
			try {
				//����� ���� �Լ� ȣ��
				close();

			}
			catch (...)
			{
				//log ����� ���� ������ ���� ��ü�� ���� ������ ����
				cout << "�߻��� ���ܿ� ���� log�� �ۼ���" << endl;
				//
				//std::abort();	//���α׷� ����
				//�Ǵ� ���ܸ� ��Ŵ(���ܸ� ó������ ����, std::abort()�� �ּ�ó��)
			}
		}
	}
};��`