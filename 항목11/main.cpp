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

/*항목11 operator=에서는 자기대입에 대한 처리가 빠지지 않도록 하자
요점정리
operator=을 구현할때, 어떤 객체가 그 자신에 대입되는 경우를 제대로 처리하도록 만듭시다.
원본 객체와 복사대상 객체의 주소를 비교해도 되고, 문장의 순서를 적절히 조정할 수 도 있으며
복사 후 맞바꾸기 기법을 써도 됩니다.

두 개 이상의 객체에 대해 동작하는 함수가 있다면, 이 함수에 넘겨지는 객체들이 사실
같은 객체인 경우에 정확하게 동작하는지 확인해 보세요.
*/

/*
자기대입에 대한 예는 이런것이다.
	kObj = kObj;

	이와 같이 쓸데 없는 연산을 막고
	쓸데 없는 연산을 하더라도
	
	이상없게 돌아가게 하자는 애기다(당연한 애기)
	아래와 같은 구문은 rhs가 객체 자신일때 정상동작 할 수 없다.

	CBase& operator=(CBase const& rhs)	//rhs '=='this(자기대입의 경우)
	{
		delete m_piVal;						//내껄 이미 지웠는데.
		m_pIval = new int(*rhs.m_piVal);	//이미 지운곳에서 무엇을 얻어오는가?
		return *this;
	}

	//위는 아래와 같이 수정되어야 자기 대입에도 안전하다.
	CBase& operator=(CBase const& rhs)		//자기 대입이 일어날 경우
	{
		int* piTemp = m_pIVal;				//자기 객체를 임시저장
		m_pIval = new int(*rhs.m_piVal);	//자기 객체의 사본을 생성
											//성공적으로 일어나면
		delete piTemp;						//임시로 저장한 객체 해제
		piTemp = NULL;
		return *this;
	}

	또 if(this==&rhs)	//이와 같이 주소값을 비교해 불필요한 연산을 줄이는 방법도 있다.(일치성 검사)
	{
		return *this;
	}

	swap함수를 지원한다면 다음과 같이 하는 방법도 있다.
	CBase& operator=(CBase const& rhs)
	{
		CBase kTemp(rhs);	//객체생성
		swap(kTemp);		//swap
		return *this;
	}

	이 코드를 한번더 줄이면
	CBase& operator=(CBase rhs)	//call by value로 객체 생성
	{
		swap(rhs);				//swap
		return *this;
	}
*/l