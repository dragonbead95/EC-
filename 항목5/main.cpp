/*
항목5 : C++가 은글슬쩍 만들어 호출해 버리는 함수들에 촉각을 세우자

클래스가 만드는 묵시적 함수의 종류.
기본생성자, 복사생성자, 복사 대입 연산자, 소멸자

디폴트 복사 생성자 문제. 얕은 복사 생상자.
디폴트 복사 대입 연산자 문제->래퍼런스 복사가 정의되어 있지 않음

*/

#include <iostream>

class CEmpty 
{//아래는 class에서 묵시적으로 만드는 함수 4개
public:
	//클래스가 만드는 묵시적 함수
	//디폴트 생성자는 public 접근성을 가지고 inline 함수이다.
	//CEmpty(){}								//생성자
	//~CEmpty(){}								//소멸자
	//CEmpty(CEmpty const& rhs){}				//복사 생성자
	//CEmpty& operator=(CEmpty const& rhs){}	//복사 대입 연산자

	CEmpty(std::string& sStr) : m_iId(0), m_piId(NULL), m_sStr(sStr) {}
	~CEmpty() { delete m_piId;}
	//CEmpty& operator=(CEmpty const& rhs){return *this;};

	void output()
	{
		std::cout << m_sStr.c_str() << std::endl;
	}
	//초기화
	void initialize()
	{
		m_piId = new int;
		*m_piId = 10;
	}
private:
	int m_iId;
	int* m_piId;
	std::string& m_sStr;
};

int main(void)
{
	std::string str = "abc";
	CEmpty Emp1(str);
	//Emp1.initialize();	//error 얕은 복사에 의한 에러
	Emp1.output();
	CEmpty Emp1Copy(Emp1);
	Emp1Copy.output();
	str += "d";
	Emp1Copy.output();

	//<error- 클래스 내의 레퍼런스 멤버변수 
	//존재시, 디폴트 복사 생성자 컴파일 에러>
	CEmpty Emp2(Emp1);	//디폴트 복사 생성자는 문제없다.
						//디폴트 복사 생성자는 멤버변수안에 래퍼런스 변수가 있더라도 문제없이 넣을 수 있다.
						//하지만 복사 대입 연산자에서 객체에 래퍼런스 변수가 있다면 에러가 발생하게 된다.
						//이 문제를 해결하려면 복사 대입 연산자를 직접 정의해야 한다.
	str += "e";
	Emp2.output();
	//Emp2=Emp1		//디폴트 복사 대입 연산자 시행 안됨(컴파일러 에러 발생)
					// 참조자에 대한 기본적인 대입 연산이 정의되지 않았기 때문에 직접 정의해야 한다.
	return 0;
}