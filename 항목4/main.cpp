/*항목4: 객체를 사용하기 전에 반드시 그 객체를 초기화하자*/

/*요점정리*/
/*기본제공 타입의 객체는 직접 손으로 초기화합니다. 경우에 따라 저절로 되기도 하고 안되기도 하기 때문입니다.*/

/*생성자에서는, 데이터 멤버에 대한 대입문을 생성자 본문 내부에 넣는 방법으로 멤버를 초기화하지말고 멤버 초기화
리스트를 즐겨 사용합시다. 그리고 초기화 리스트에 데이터 멤버를 나열할 때는 클래스에 각 데이터 멤버가 선언된
순서와 똑같이 나열합시다.*/

/*여러 번역 단위에 있는 비지역 정적 객체들의 초기화 순서 문제는 피해서 설계해야 합니다. 비지역 정적 객체를
지역 정적 객체로 바꾸면 됩니다.*/

#include <cstring>
#include <iostream>

class CInit {
private:
	//기본제공 타입의 경우에는 (생성자 안에서) 대입되기 전에 초기화되리라는 보장이 없다.
	int				m_iVal;
	std::string		m_sName;
	int const		m_ciVal;	//상수
	std::string&	m_csName;	//래퍼런스
public:
	CInit(int _ival, std::string _sName) :	m_iVal(_ival)	//초기화 리스트.
											,m_sName()
		
											//상수와 래퍼런스는 의무적으로 초기화 리스트에서 해준다.
											//대입 자체가 불가능 하다.
											, m_ciVal(_ival)
											, m_csName(_sName)
	{
		//초기화가 아니라 대입이다.
		//(기본 제공 타입의 경우 초기화와 대입에 걸리는 비용의 차이가 없다.)
		//m_ival=_ival;
		//m_sName=_sName;
	}
};

////////////////////////////비·지역·정적·객체, 지역·정적객체·의미////////////////////////////
//비.지역.정적.객체: 전역변수, Namespace범위의 변수, (함수내부에서 생성하지 않은)static 변수.
//지역.정적.객체: 함수 내부에서 static으로 선언된 객체

//<초기화 위치>
//비지역.정적.객체의 초기화 순서:개별-번역-단위에서 정해진다.
//개별번역단위:cpp파일과 그 안에 #include로 포함한 파일들을 말함
//지역 정적객체의 초기화 순서:맨 처음 호출 지정

//1. 전역											: 비지역 정적 객체(non-local-static-object)
//2. 네임스페이스 유효범위에서 정의된 객체			: 비지역 정적 객체(non-local-static-object)
//3. 클래스 내부에서 static으로 선언된 객체			: 비지역 정적 객체(non-local-static-object)
//4. 함수 내부에서 static으로 선언된 객체			: 지역 정적 객체(local-static object)
//5. 파일 유효 범위에서 static으로 선언된 객체		: 비지역 정적 객체(non-local-static-object)

int iInt = 0;					//전역 객체.
namespace nFirst
{
	int g_iInt = 0;				//클래스 내부에서 static으로 선언된 객체

	void output()
	{
		printf("vikFirst\n");
	}
}

class CSecond
{
private:
	static int m_iInt;					//클래스 내부에서 static으로 선언된 객체

	CSecond();
	CSecond(const CSecond&);
	CSecond& operator=(const CSecond&);
public:
	static CSecond* Instance()
	{
		static CSecond instance;		//함수 내부에서 static으로 선언된 객체(지역정적객체)
		return &instance;
	}
};

////////////////////////////////비지역 정적 객체의 단점////////////////////////////////
//비 지역 정적 객체의 초기화 순서는 정해져 있지 않다.
//실행 순서에 따라 에러날수 있다.
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
extern CActionFirst ActionFirst;		//사용자가 쓰게 될 객체
class CActionSecond
{
public:
	CActionSecond()
	{
		ActionFirst.output();
	}
};

//CActionSecond g_InitOrder;	//MNActionFirst의 객체가 먼저 생성되지 않고,
//								//MNAActionSecond가 생성되면 error
//								//(정의되지 않은 객체를 접근시도 했기 때문에)

/////////////////////////////////비지역 정적 객체의 단점을 해결///////////////////////////////////
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
	//static으로 객체 생성
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

/////////////////////////////////초기화 실행 순서/////////////////////////////////
class CInitOrder
{
private:
	int m_iNum1;	//초기화 순서는 선언된 순서다(멤버초기화리스트의 순서가 아니다)
	int m_iNum2;
	int m_iNum3;
public:
	CInitOrder() :	m_iNum1(0)
					, m_iNum3(2)
					, m_iNum2(m_iNum3)	//쓰레기 값이 들어감(초기화 순서는 초기화 리스트 순서가 아니다.)
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