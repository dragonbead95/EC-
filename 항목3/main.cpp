/*항목3 : 낌새만 보이면 const를 들이대 보자*/

/*요점정리*/
/*const를 붙여 선언하면 컴파일러가 사용상의 에러를 잡아내는데 도움을 줍니다. const
는 어떤 유효범위에 있는 객체에도 붙을 수 있으며, 함수 매개변수 및 반환 타입에도 붙을
수 있으며, 멤버 함수에도 붙을 수 있습니다.*/
/*컴파일러 쪽에서 보면 비트수준 상수성을 지커야 하지만, 여러분은 개념적인(논리적인)
상수성을 사용해서 프로그래밍해야 합니다.*/
/*상수 멤버 및 비상수 멤버 함수가 기능적으로 서로 똑같이 구현되어 있을 경웨는 코드 중복을
피하는 것이 좋은데, 이때 비상수 버전이 상수 버전을 호출하도록 만드세요.*/

#include <iostream>
#include <cstring>
#include <vector>

//1. 문자열을 변수로 바꿀때 유의점
#define TEST_MSG "Yiku"
char const* const STR_TESTMSG1 = "Yiku";	//1-1, 값의 상수화, 포인터의 상수화를 잊지말자
std::string const STR_TESTMSG2("Yiku");		//1-2 char* 보다 string 객체를 사용하는 것이, 사용하기 편하다.

char g_strText[] = "Hello";						//비상수 포인터, 비상수데이터
char* g_pDataPtr = g_strText;					//비상수 포인터, 비상수데이터
const char* g_pCDataPtr = g_strText;			//비상수 포인터, 상수데이터
char* const g_pDataCPtr = g_strText;			//상수 포인터, 비상수데이터
const char* const g_pCDataCPtr = g_strText;		//상수 포인터, 상수데이터


//////////////////////////////////////////////코드판박이 괴물예시////////////////////////////////////////////////
class COverLapCode
{
private:
	std::string m_sName;
public:
	explicit COverLapCode(std::string _sName) : m_sName(_sName)
	{

	}

	const char& operator[](std::size_t uiPos) const	//코드 중복(코드 판박이 괴물)
	{
		return m_sName[uiPos];
	}

	char& operator[](std::size_t uiPos)				// 코드 중복(코드 판박이 괴물)
	{
		return m_sName[uiPos];
	}
};

//////////////////////////////////////////////코드판박이 괴물 제거 방법////////////////////////////////////////////////
class COverLapCodeImprove
{
private:
	std::string m_sName;
public:
	//explicit은 자동 형 변환을 막아주는 키워드이다.
	explicit COverLapCodeImprove(std::string _sName) : m_sName(_sName)
	{

	}

	const char& operator[](std::size_t uiPos) const						//상수 객체에 대한 operator[]
	{
		return m_sName[uiPos];
	}

	char& operator[](std::size_t uiPos)									//상수 버전 op[]를 호출하고 끝
	{
		return
			const_cast<char&>											//op[]의 반환 타입에 캐스팅을 적용 const를 제거하고 char&로 바꾼다.
			(static_cast<const COverLapCodeImprove&>					//*this의 타입에 const를 붙입니다.
			(*this)[uiPos]);											//op[]의 상수 버전을 호출합니다.
	}
};

//////////////////////////////멤버 함수의 상수화 의미////////////////////////////////////////
//의미 첫번째:물리적 상수성
class CPhysical
{
private:
	char* m_cpName;
public:
	CPhysical(const char* _cpName) : m_cpName(NULL)
	{
		m_cpName = new char[sizeof(_cpName)];
		strcpy_s(m_cpName,sizeof(_cpName),_cpName);
	}

	//부적절한(그러나 비트 수준 상수에 있어서는 허용되는)operator[]선언
	char& operator[](std::size_t uiPos) const
	{
		return m_cpName[uiPos];
	}
};

//의미 두번째:논리적 상수성
class Clogical
{
private:
	const char* m_cpName;
	mutable std::size_t m_uiPos;		//mutable이 데이터 멤버들은 어떠한 경우에도 수정이 가능하다.
	mutable bool m_bLengthCheck;		//(심지어 상수 멤버 함수 안에서도 수정할 수 있습니다.

public:
	explicit Clogical(const char* _cpName) : m_cpName(_cpName),m_uiPos(), m_bLengthCheck(false)
	{

	}

	std::size_t length() const
	{
		if (!m_bLengthCheck)
		{
			m_uiPos = std::strlen(m_cpName);	//const 멤버 함수 내부에서 값변경
			m_bLengthCheck = true;
		}
		return m_uiPos;
	}
};

class CMultiplication
{
private:
	int m_iNum;
public:
	CMultiplication(int iNum) : m_iNum(iNum) 
	{

	}

	//operator* 리턴값을 const로 해준다.
	const CMultiplication& operator*(const CMultiplication Input)
	{
		m_iNum *= Input.getNum();
		return *this;
	}

	//기본 메멉변수 get
	int getNum(void) const
	{
		return m_iNum;
	}
};

int main(void)
{
	//STL 반복자에서 const 사용 방법
	std::vector<int> vInt;
	vInt.push_back(1);

	//상수 포인터, 비 상수 포인터
	const std::vector<int>::iterator iter = vInt.begin();
	*iter = 10;	//가능
	//++iter;	//error

	//비상수 포인터, 상수 데이터
	std::vector<int>::const_iterator cIter = vInt.begin();
	//*cIter = 10;	//error
	++cIter;		//가능

	//operator* 리턴값을 const로
	CMultiplication A(2);
	CMultiplication B(4);
	CMultiplication C(6);
	//(A*B)=C;	//error 상수(A*B)에다가 operator*를 했기 때문에

	//코드 판박이 괴물 제거 방법
	const COverLapCodeImprove cCodeMonster("Dron");
	std::cout << cCodeMonster[0] << std::endl;
	//cCodeMonster[0]='H';		//error

	COverLapCodeImprove CodeMonster("Mutal");
	std::cout << CodeMonster[0] << std::endl;
	CodeMonster[0] = 'H';		//값 변경 됨

	//멤버 함수가 상수 멤버라는 것의 의미
	//1. 물리적 상수성의 에러
	const CPhysical Physical("Physical");
	//const 객체의 const 멤버함수인데, 값이 변경된다.(물리적 상수성 const error)
	//const 멤버함수안에서 변경만 되지 않는다면 외부에서 변경을 해도 상관없는 모순이 생겨납니다.
	Physical[0] = 'H';
	std::cout << Physical[0] << std::endl;
	char* pc = &Physical[0];
	*pc = 'c';
	std::cout << Physical[0] << std::endl;


	//2. 논리적 상수성
	Clogical Logical("MNLogical");
	std::cout << "Logical Str Length" << Logical.length() << std::endl;

	system("pause");
	return 0;
}