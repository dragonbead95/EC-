/*
항목6: 컴파일러가 만들어낸 함수가 필요 없으면 확실히 이들의 사용을 금해 버리자

묵시적 함수가 불필요할때 쓰지 못하도록 막는 이유?
런타임 에러를 막고, 링크에러나 컴파일 에러로 바꾸기 위해
*/

#include <iostream>

class CNoneCopy
{//방법1 : 복사 생성자와, 복사대입 연산자 함수 접근권한을 막음
public:
	CNoneCopy() {};
private:
	CNoneCopy(CNoneCopy const&);				//정의 부분을 만들지 않음(일반 접근시 컴파일 에러)
	CNoneCopy& operator=(CNoneCopy const&) {}		//멤버함수 or friend 함수에서 접근시(링크에러)

};

class CUncopyable
{//방법2 private로 상속
protected:	//하위 클래스들이 사용해야 하므로 protected
	CUncopyable() {};
	virtual ~CUncopyable() {};

private:
	CUncopyable(const CUncopyable&);
	CUncopyable& operator=(const CUncopyable&) {}	//정의문을 없애서 컴파일 에러를 발생하게 만든다.
};

class CTest : private CUncopyable	//Uncopyable의 파생 클래스
{//방법2
	//복사 생성자와 대입연사자의 선언부를 빼 버린다.
public:
	CTest() {};
};

int main(void)
{
	CTest kFirst;
	CTest kSecond;

	kFirst = kSecond;	//private 상속이기 때문에 외부에서 Uncopyable 복사 대입 연산자를 실행할수 없다.
}