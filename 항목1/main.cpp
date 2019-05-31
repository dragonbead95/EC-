/*
explicit-> 묵시적 변환을 막음
묵시적 변환을 왜 막아야 하는가?
const Reference type의 객체가 임시객체를 가리킬 경우를 방치할수 있다.
explicit는 타입 변환을 막아준다.
explicit을 사용해서 묵시적 객체 변환을 하는것을 막아준다.
묵시적 객체 변환을 사용할때 변환한 객체가 상속 관계인 경우 객체가 2개이상
으로 만들어질수있다.

NoneExplicit const & koneExplc = 0'
NoneExplicit 위에 상속 클래스가 있다면, 에러 비용이 더 커진다.
*/

#include <iostream>

class CBase
{
public:
	CBase();
};

class CNoneExplicit : CBase
{
public:
	CNoneExplicit(int iData)
	{
		std::cout << "NoneExplicit의 생성자입니다." << std::endl;
	}

	CNoneExplicit(CNoneExplicit const& rhs)
	{
		std::cout << "NoneExplicit의 복사 생성자입니다." << std::endl;
	}

	CNoneExplicit& operator=(CNoneExplicit const& rhs)
	{
		std::cout << "NoneExplicit의 대입 연산자입니다." << std::endl;
		return *this;
	}

	void test() const
	{
		std::cout << "text" << std::endl;
	}
};

class CExplicit
{
public:
	explicit CExplicit(int iData)
	{
		std::cout << "Explicit 생성자 : 오직 명시적인 생성자를 통해서만 접근이 가능합니다." << std::endl;
	}

	explicit CExplicit(CExplicit const& rhs)
	{
		std::cout << "Explicit의 복사 생성자입니다." << std::endl;
	}
	
	CExplicit& operator=(CExplicit const& rhs)
	{
		std::cout << "Explicit의 대입 연산자입니다." << std::endl;
		return *this;
	}
};

void explctFunc(CExplicit const& kExplct)
{//explicit

}

void noneExplctFunc(CNoneExplicit const& kNoneExplict)	//const를 빼면 error - 임시 객체를 래퍼런스를 받을때에는 const 삽입
{//none explicit
	//임시객체의 멤버함수를 호출한다.
	kNoneExplict.test();
}

int main(void)
{
	{
		CNoneExplicit kNoneExplct = 10;		//생성자
		CNoneExplicit kTemp = kNoneExplct;	//복사생성자
		kTemp = kNoneExplct;				//복사 대입연산자
		noneExplctFunc(10);					//클래스 참조자에 임시 객체를 넣어도 에러가 안난다.
	}

	std::cout << std::endl << std::endl;

	{
		CExplicit kExplct(10);				//명시적 호출
		//CExplicit kExplct = 10;			//생성자 error

		CExplicit kTempCopy(kExplct);		//
		//CExplicit kTempCopy = kExplct		//복사 생성자 error
		kTempCopy = kExplct;				//복사대입연산자

		//explctFunc(10);					//error
	}

	system("pause");
	return 0;
}