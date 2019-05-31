/*
02. define을 쓰려거든 const, enum, inline을 떠올리자.

#define 매크로는 전처리기에서 실행 되기 때문에
컴파일러가 에러 체크를 못한다.
*/
#include <iostream>
#include <cstring>

//1. 문자열을 상수로 바굴때 유의점
#define TEST_MSG "viku"
char const* const STR_TESTMSG1 = "viku";	//포인터의 완벽한 상수화 데이터 상수 and 포인터 사숭
std::string const STR_TESTMSG2("viku");	//구닥다리 char* 쓰지 말자, 사용하기 편하므로 더 좋다.

void ConstExplain(void)
{// 변수에 사용하는 const에 대한 설명
	int							iVal1 = 0;		//비상수
	int		const				iVal2 = 0;		//상수
	int		const&				riVal = 0;		//상수
	int		const*				pival1 = 0;		//포인터 비상수,	데이터 상수
	int*	const				pival2 = 0;		//포인터 상수,		데이터 비상수
	int		const* const		pival3 = 0;		//포인터 상수,		데이터 상수

	// 데이터 상수 : 값을 바꿀수 없음
	// 포인터 상수 : 다른것을 가르킬 수 없음

	// *를 기준으로 좌측에 const가 있으면 데이터 상수로 값을 바꿀수없음
	// *를 기준으로 우측에 const가 있으면 포인터 상수로 다른것을 가르킬수 없음
}

//2. class내 상수 선언과 함께 정의
class AvailConstPoiter_InitSuccess
{
private:
	static int const MAX_INDEX = 5;	//상수선언
									//이렇게 하면 안되는 이유
									//구컴파일러는 에러가 발생될 수 있다.
									//선언부분에서 값을 초기화 하는 것은 일관성에 문제가 있다.
	int m_iArr[MAX_INDEX];
};

//class내 선언, cpp정의
class AvailConstPoiter_InitFail
{
private:
	static int const MAX_INDEX;	//상수 선언
	//int m_iArr[MAX_INDEX];	//배열 선언에서 error
};

//cpp에 정의 해도 int m_iArr[MAX_INDEX]; 에러난다.
int const AvailConstPoiter_InitFail::MAX_INDEX = 10;	//상수 정의(cpp에 존재 해야함)

//enum의 활용
class AvailEnum
{
public:
	enum{MAX_INDEX = 5,};
private:
	int m_iArr[MAX_INDEX];
};

//3. define의 문제
#define VALUE_COMPARE(a,b) ((a)>(b) ? (a) : (b))

//(iNum1>iNum2) 결과에 따라 값이 달라짐
void showDefineProblem(void)
{
	int iNum1 = 5;
	int iNum2 = 0;
	std::cout << "원래 값 " << iNum1 << std::endl;
	VALUE_COMPARE(++iNum1, iNum2);
	//(++iNum1)>(iNum2) ? (++iNum1) : (iNum2))가 되므로 두번증가하게 된다.
	std::cout << "두번증가" << iNum1 << std::endl;

	VALUE_COMPARE(++iNum1, iNum2 + 10);
	std::cout << "한번증가" << iNum1 << std::endl;	//iNum1가 한번 증가
}

//define의 inline화
//함수를 최적화
inline void VALUECOMPARE(int const& iLhs, int const& iRhs)
{
	((iLhs) > (iRhs) ? (iLhs) : (iRhs));
}

void AvailInLine(void)
{
	int iNum1 = 5;
	int iNum2 = 0;

	std::cout << "원래값 " << iNum1 << std::endl;

	VALUECOMPARE(++iNum1, iNum2);	//iNum1이 한번증가하고 인라인 함수로 대체된다.
	std::cout << "한번증가" << iNum1 << std::endl;

	VALUECOMPARE(++iNum1, iNum2);
	std::cout << "한번증가" << iNum1 << std::endl;
}


///////////////////////////////////////////////
