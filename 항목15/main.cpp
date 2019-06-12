/*항목15 : 자원 관리 클래스에서 관리되는 자원은 외부에서 접근할 수 있도록 하자

요점정리
실제 자원을 직접 접근해야 하는 기존 API들도 많기 때문에 RAII 클래스를 만들 때는
그 클래스가 관리하는 자원을 얻을 수 있는 방법을 열어 주어야 합니다.

자원 접근은 명시적 변환 혹은 암시적 변환을 통해 가능합니다. 안정성만 따지면 명시적
변환이 대체적으로 더 낫지만, 고객 편의성을 놓고 보면 암시적 변환이 괞찮습니다.
*/

#include <iostream>


std::tr1::shared_ptr<Investment> pInv(createInvestment);	//항목 13에서 가져온 예제
int daysHeld(const Investment* pi);	//투자금이 유입된 이후로 경과한 날수
int days = daysHeld(pInv);	//에러!
/*
에러가 난 이유는 daysHeld함수는 Investment* 타입입의 실제 포인터를 원하는데,
tr1::shared_ptr<Investment> 타입의 객체를 넘기기 때문입니다.
*/

/* 요점은 RAII 클래스(지금은 tr1::shared_ptr)의 객체를 그 객체가 감싸고 있는
실제 자원(Investment*)으로 변환할 방법이 필요해진다.
두가지 방법이 존재, 명시적 변환, 암시적 변환
*/

/*명시적 변환하는 방법(get)
get함수를 사용하면 각 타입으로 만든 스마트 포인터 객체에 들어있는 실제 포인터(의 사본)를 얻어낼수 있다.
int days = daysHeld(pInv.get());	//이제 문제없습니다. pInv에 들어있는 실제 포인터를 daysHeld에 넘긴다.
*/

class Investment {		//여러 형태의 투자를 모델링한 투자 클래스들의 최상위 클래스
public:
	bool isTaxFree() const;
};

Investment* createInvestment();	//팩토리 함수

std::tr1::shared_ptr<Investment> pi1(createInvestment());	//tr1::shared_ptr이 자원관리를 맡도록 합니다.

bool taxable1 = !(pi1->isTaxFree());	//operator->를 써서 자원에 접근합니다.

std::auto_ptr<Investment> pi2(createInvestment());	//auto_ptr로 하여금 자원 관리를 맡도록 합니다.

bool taxable2 = !((*pi2).isTaxFree());	//operator*를 써서 자원에 접근합니다.

//////////////////////////////////////////////////////////////////////////////////////

FontHandle getFont();	//C API에서 가져온 매개변수가 있으면 복잡하기 때문에 생략

void releaseFont(FontHandle fh);	//역시 같은 C API에서 가져온 함수

class Font {						//RAII클래스
private:
	FontHandle f;					//실제 폰트 자원
public:
	explicit Font(FontHandle fh)	//자원을 흭득합니다. 여기서 값에 의한 전달이 수행되는것에 
									//주의하세요. 자원 해제를 C API로 하기 때문이빈다.
		: f(fh)
	{

	}
	~Font()
	{
		releaseFont(f);
	}
	FontHandle get() const	//명시적 변환 함수
	{
		return f;
	}
};

void changeFontSize(FontHandle f, int newSize);	//폰트 API의 일부
Font f(getFont());
int newFontSize;

changeFontSize(f.get(), newFontSize);	//Font에서 FontHandle로 명시적으로 바꾼후에 넘깁니다.


/*FontHandle로의 암시적 변환 함수
class Font
{
public:
	operator FontHandle() const	//암시적 변환 함수
	{
		return f;
	}
}
*/

Font f(getFont());
int newFontSize();
changeFontSize(f, newFontSize);	//Font에서 FontHandle로 암시적 변환을 수행합니다.


/*암시적 변환이 들어가면 실수를 저리를 여지가 많아진다.
Font f1(getFont());
FontHandle f2 = f1;	//원래의도는 Font객체를 복사하는 것이었는데, 엉뚱하게도 f1이 FontHandle로 바귀고 나서 복사되어 버렸다.
이렇게 되면 f2도 f1이 관리하는 자원을 사용할수 있게 되는데, f1이 소멸하게 되면 f2는 해제된 폰트에 매달려있는 꼴이된다.
*/

int main(void)
{
	
}