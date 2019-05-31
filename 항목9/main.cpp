/*항목9:객체 생성 및 소멸 과정 중에는 절대로 가상 함수를 호출하지 말자
요점정리
생성자 혹은 소멸자 안에서 가상 함수를 호출하지 마세요. 가상 함수라고 해도
지금 실행 중인 생성자나 소멸자에 해당되는 클래스의 파생 클래스 쪽으로는 내려가지 않으니까요.
*/

#include <iostream>

using std::endl;
using std::cout;


class CBase
{
public:
	CBase()
	{
		cout << "CBase의 생성자" << std::endl;
		//vFun();	//1. 이렇게 직접 호출하면 링크 에러가 난다.
		Init();		//2. 하지만 이렇게 다른함수에 엮어서 래핑하면 컴파일 에러가 나지 않는다.
	}

	virtual ~CBase()
	{
		cout << "CBase의 소멸자" << endl;
		Init();
	}

	void Init()
	{//다른 함수에 래핑되어 가상함수 호출
		vFun();	//컴파일 에러 나지 않음
		//컴파일러에서 링크에러를 잡아주지 못함
	}
	virtual void vFun() = 0;
};

class CBranch : public CBase
{
public:
	CBranch()
	{
		cout << "CBranch의 생성자" << endl;
	}
	virtual ~CBranch()
	{
		cout << "CBranch의 소멸자" << endl;
	}
	virtual void vFun()
	{
		cout << "CBranch의 가상함수 실행" << endl;
	}
};

int main(void)
{
	CBranch kObj;	//어떻게 될까?

	/*
		생성자와 소멸자에서 가상함수 호출은
		다른함수에 래핑이 되어있던, 되어있지 않던 동일하게
		자신의 가상함수가 호출된다.

		다라서 위의 예제는 런타임에
		순수 가상함수가 호출되었다고 에러를 발생시킨다.

		결론 : 생성자와 소멸자에선, 가상함수 호출을 하면 안된다고 못박아 기억하자.
	*/

	return 0;
}