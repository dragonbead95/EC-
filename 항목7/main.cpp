/*항목 07. 기본 클래스와 가상함수*/

/*class Child : public std::string 같은
virtual이 없는 string 클래스를 상속받으면
소멸시 소중한 자원, 자료구조 오염, 무한 짜증의 디버깅 발생이 될 수 있다.
*/

/* class A
class B : public A
B kobj;	//부모 클래스 소멸자에 virtual가 없어도 부모 자식 소멸자 전부 실행된다.
A* pkBase = new B;	//부모 클래스에 소멸자가 없으면, 자식 클래스에 소멸자가 실행되지 않음.
delete pkBase;
*/

#include <iostream>

class NoneVtbl
{
public:
	NoneVtbl() : m_iData(0)
	{

	}
	~NoneVtbl()
	{

	}
private:
	int m_iData;
};

class ExistVtbl
{//가상함수를 1개라도 가진 클래스는 가상 소멸자를 가져야한다.
public:
	ExistVtbl() : m_iData(0)
	{
		std::cout << "ExistVtbl 생성자 실행" << std::endl;
	}
	virtual ~ExistVtbl()
	{
		std::cout << "ExistVtbl 소멸자 실행" << std::endl;
	}
private:
	int m_iData;
};

class ExistVtblChild : public ExistVtbl
{
public:
	ExistVtblChild()
	{
		std::cout << "ExistVtblChild 생성자 실행" << std::endl;
	}
	~ExistVtblChild()
	{
		std::cout << "ExistCtblChild 소멸자 실행" << std::endl;
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
class VBase
{//추상 클래슬 만들려 하나, 마땅히 필요한 순수 가상함수가 없을때
public:
	VBase() {};
	virtual ~VBase() = 0;	//소멸자를 순수 가상함수로 설정함
};

VBase::~VBase()
{
	std::cout << "VBase 소멸자 실행" << std::endl;
}

class NWChild : public VBase
{
public:
	NWChild() {};
	~NWChild() {};
};

int main(void)
{
	//프로그램 실행환경에 따라 vptr의 크기는 변경 될수가 있다.
	//32bit-4byte
	//64bit-8byte
	std::cout << sizeof(NoneVtbl) << std::endl;		//int 1개 크기
	std::cout << sizeof(ExistVtbl) << std::endl;	//int 1개크기 + vptr 크기

	/*
		virtual 키워드가 추가되면 class은 vtbl(가상함수 테이블)이란
		별도의 추가적인 자료구조를 갖게 된다.

		vtbl이란?
		실행주엥 주어진 객체의 어떤 가상함수를 호출해야 하는지 결정하는데 쓰이는 정보다.
		
		대개는 포인터로 구현되어 있기 때문에 sizeof를 통해 체크해 보면
		포인터의 값만큼 size가 증가된것을 알수가 있다.(위 예제)

		객체의 어떤 가상함수가 호출되려하면 호출되는 실제함수는
		그 객체의 vptr이 가르키는 vtbl에 따라 결정된다.
	*/

	{//class의 내부에 vptr이 존재하기 때문에 이처럼 메모리 복사를 하게 되면
		//vptr의 정보가 깨질수 밖에 없다.(memcpy도 마찬가지)
		//객체를 메모리 복사하는 바보같은짓은 하지 말자
		//memset 메모리 초기화 keyword
		ExistVtbl* kTemp = new ExistVtblChild;
		::memset(&kTemp, 0, sizeof(kTemp));	//미친짓 vtbl이 날아간다.
		delete kTemp;

	}

	std::cout << std::endl << std::endl;
	NWChild Child;	//VBase::~VBase(){} 주석달면 error남
}