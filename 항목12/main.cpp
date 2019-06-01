/*항목12: 객체의 모든 부분을 빠짐없이 복사하자
요점정리
객체 복사 함수는 주어진 객체의 모든 데이터 멤버 및 모든 기본 클래스 부분을 빠드리지 말고
복사해야 합니다.

클래스의 복사 함수 두 개를 구현할 때, 한쪽을 이용해서 다른 쪽을 구현하려는 시도는 절대로
하지마세요. 그 대신, 공통된 동작을 제3의 함수에다 분리해 놓고 양쪽에서 이것을 호출하게 만들어서
해결합시다.


*/

/*
복사라고 하면 복사 생성자, 복사 대입 연산자 두개가 떠올려야 한다.
이 두개를 복사함수라 한다.
*/
#include <iostream>

class CBase
{
private:
	int m_iVal;
public:
	CBase() :m_iVal(0)
	{}
	CBase(int const iVal) : m_iVal(iVal)
	{}

	CBase(CBase const& rhs)
	{//복사생성자
		m_iVal = rhs.m_iVal;
	}

	virtual ~CBase()
	{

	}

	CBase& operator=(CBase const& rhs)
	{//복사대입연산자
		m_iVal = rhs.m_iVal;
		return *this;
	}
	virtual void vPrintInfo()
	{
		std::cout << m_iVal << std::endl;
	}
};

class CDerived : public CBase
{
private:
	float m_fVal;
public:
	CDerived(int const iVal, float const fVal)
		:CBase(iVal), m_fVal(fVal)
	{

	}

	CDerived(CDerived const& rhs)
	{//복사 생성자
		m_fVal = rhs.m_fVal;
	}

	virtual ~CDerived()
	{

	}

	CDerived& operator=(CDerived const& rhs)
	{//복사 대입 연산자
		m_fVal = rhs.m_fVal;
		return *this;
	}
	virtual void vPrintInfo()
	{
		CBase::vPrintInfo();
		std::cout << m_fVal << std::endl;
	}
};

int main(void)
{
	CDerived kObj(1, 2.5f);
	CDerived kObj1(3, 4.5f);

	kObj = kObj1;	//복사 대입 연산자
	kObj.vPrintInfo();	//결과는 "3,4.5"가 출력될까?
	std::cout << std::endl;	/*예상결과 : 1 4.5*/

	CDerived kObj2(kObj1);	//복사생성자
	kObj.vPrintInfo();	//결과는 "3,4.5"가 될가?
						/*0 4.5*/
	
	/*
		위 문제에 대한 해결책은 아래와 같다.
		CDerived(CDerived const& rhs)
			: CBase(rhs)
		{//복사생성자
			m_fVal = rhs.m_fVal;
		}

		CDerived& operator=(Cderived const& rhs)
		{
			CBase::operator=(rhs);
			m_fVal = rhs.m_fVal;
			return *this;
		}

		보기에 중복코드라 어떻게 한개로 하고 싶다고 해서
		복사생성자에서 대입 연산자로 호출한다거나
		생성도 안됐는데 복사를 한다는것 자체가 말도 안된다.
		반대로 대입연산자에서 복사생성자를 호출하는 것도 말이 안된다.
		이미 생성했는데 또 생성자를 태우는건 태어난 애보고 엄마 뱃속으로 들어가리라는 꼴이다.

		private영역에 Init어쩌고 등의 이름으로 공통 부분을 모아 호출하는것은 가능하다.
		하지만 void CopyFrom(typename const& T)와 같은 공통성을 뽑아 작업하기에는 어려움이  생긴다.
		(내가 틀렸을수도 있다.)

	*/

	return 0;
}