//항목08:예외가 소멸자를 떠나지 못하도록 붙들어 놓자
/*요점정리
소멸자에서는 예외가 빠져나가면 안 됩니다. 만약 소멸자 안에서 호출된 함수가 예외를
던질 가능성이 있다면, 어떤 예외이든지 소멸자에서 모두 받아낸 후에 삼켜 버리든지 프로그램을
끝내든지 해야 합니다.

어떤 클래스의 연산이 진행되다가 던진 예외에 대해 사용자가 반응해야 할 필요가 있다면,
해당 연산을 제공하는 함수는 반드시 보통의 함수(즉, 소멸자가 아닌 함수)이어야 한다.
*/

//싱글톤 자동 소멸
//소멸자에서 발생한 예외는 소멸자에서 처리

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
	static MNSingleton* instance()		//싱글톤
	{
		static MNSingleton instance;
		return &instance;
	}
	void close()				//리소스 소멸
	{
		cout << "MNSingleton 리소스 소멸" << endl;
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
		m_pSingleton->close();	//사용자의 망각을 사전에 차단시키는 방법
	}
private:
	MNSingleton* m_pSingleton;
};

void SingletonAutoDelete(void)
{
	MNSingletonMgr SingleMgr(MNSingleton::instance());
	//MNSingleton::instance()->close();	//블록에서 나가서면 자동 소멸을 해준다.
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
		//보통의 멤버함수.
		//
		//왜 소멸을 소멸자에서 안하고 멤버함수에서 하는가?
		//예외를 일으키는 소멸자는 시한폭탄이나 마찬가지라서
		//프로그램의 불완전 종료
		//혹은 미정의 동작의 위험을 내포하고 있기 때문이다.

		//Database를 소멸시킨다.
		//Database를 소멸을 실패하면 throw로 예외를 발생

		//Database를 소멸이 성공적이면 true로 갱신
		//m_bClosed=true;
	}

	~widget()
	{
		//여기서도 처리를 못하면 예외가 빠져나가서 에러를 유발시킬수 있다.
		//그래서 사전에 예방하기 위해서 이 if문을 작성한 것이다.
		//그래서 소멸자에서 발생한 예외는 소멸자에서 처리해야 한다.
		if (!m_bClosed)
		{
			//Database 연결이 닫히지 않을 경우(메모리 소멸이 이루어지지 않았을 경우).
			try {
				//사용자 정의 함수 호출
				close();

			}
			catch (...)
			{
				//log 남기기 위한 정보를 담은 객체를 따로 받으면 좋음
				cout << "발생한 예외에 대한 log를 작성함" << endl;
				//
				//std::abort();	//프로그램 종료
				//또는 예외를 삼킴(예외를 처리하지 않음, std::abort()를 주석처리)
			}
		}
	}
};ㅌ`