/*항목10:대입 연산자는 *this의 참조자를 반환하게 하자
요점정리
대입 연산자는 *this의 참조라르 반환하도록 만드세요

왜?
일관성이 깨지기 때문에

관례가 무슨 말인지 아시죠?
따르지 않고 코드를 작성하더라도 컴파일이 안된다거나 하는것은 아닙니다.

하지만 이 관례는 모든 기본 제공 타입들이 따르고,표준 라이브러리에 속한 모든 타입
(string, vector, complex, trl::shared_ptr 등)에서도 따르고 있다는 점은 무시 못할 것입니다.

구태여 힘들게 다른길을 걸어야할 거창한 이유 같은게 없다면
까칠하게 굴지 않아도 엿애을 즐겁게 보낼 수 있습니다.
*/

#include <iostream>
using std::cout;
using std::endl;

class CBase
{
private:
	int m_iVal;
public:
	CBase() : m_iVal(0)
	{

	}

	CBase& operator=(CBase const& rhs)
	{//1. *this를 반환 하는 예시
		this->m_iVal = rhs.m_iVal;
		return *this;
	}

	CBase& operator=(int irhs)
	{//1. *this를 반환하는 예시
		m_iVal = irhs;
		return *this;
	}

	void output(void)
	{
		cout << m_iVal << endl;
	}
};

int main(void)
{//class도 데이터 타입이기 때문에 보통 int와 같이 동작하게 하면된다.
	//아래는 int와 대입연산자의 관련된 동작을 하는 부분이며,
	//자신의 참조라를 반환하는지 테스트 해볼수 있는 예제이다.

	int iVal = 0;

	//1을 iVal에 =연산자를 이용하여 집어넣은 다음에 반환받은 참조자를 이용하여 다시 10을 넣는다.
	//만약 =연산자에서 *this를 반환받지 않는다면 10을 넣을 수 없을것입니다.
	(iVal = 1) = 10;
	cout << iVal << endl;

	(iVal += 1) = 20;
	cout << iVal << endl;

	(iVal -= 1) = 30;
	cout << iVal << endl;

	(iVal *= 1) = 40;
	cout << iVal << endl;

	(iVal /= 1) = 50;
	cout << iVal << endl;
}