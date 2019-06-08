/*항목13 : 자원 관리에는 객체가 그만!
프로그래밍 분야에서 자원이란 사용을 일단 마치고 난 후에는 시스템에 돌려주어야 한다.
자원에는 여러가지가 있다. 대표적으로는 동적 할당한 메모리가 있고,
파일 서술자(file descriptor), 뮤텍스 잠금(mutex lock), 그래픽 유저 인터페이스에서
쓰이는 폰트(Font)와 브러시(brush)도 자원입니다.
*/

/*요점정리
자원 누출을 막기 위해, 생성자 안에서 자원을 흭득하고 소멸자에서 그것을 해제하는 RAII객체를 사용합시다.

일반적으로 널리 쓰이는 RAII 클래스는 tr1::shared_ptr 그리고 auto_ptr입니다.
이 둘 가운데 tr1::shared_ptr이 복사 시의 동작이 직관적이기 때문에 대개 더 좋습니다.
반면, auto_ptr은 복사되는 객체(원본 객체)를 null로 만들어 버립니다.
*/

#include <iostream>


/* 여러 형태의 투자를 모델링한
클래스 계통의 최상위 클래스
*/
class Investment
{
public:
	
	
};

Investment* createInvestment()
{
	/*Investment 클래스 계통에 속한
	클래스의 객체를 동적 할당하고
	그 포인터를 반환합니다.
	이 객체의 해제는 호출자 쪽에서 직접 해야합니다.
	*/
}

/*
멀쩡해 보이는 함수같지만 createInvestment 함수로부터 얻은 투자 객체의
삭제에 실패할수 있는 경우가 한두가지가 아닙니다.
...부분 어딘가에서 return문이 들어있거나 continue,goto문, 예외가 던져지면
delete문을 실행하여 자원을 반환할수 없는경우가 있습니다.

*/


/*createInvestment 함수로 얻어낸 자원이 항상 해제되도록 만들 방법은, 자원을 객체에 넣고 그 자원
해제를 소멸자가 맡도록 하며, 그 소멸자는 실행 제어가 f를 떠날때 호출되도록 만드는 것입니다.
C++가 자동으로 호출해 주는 소멸자에 의해 해당 자원을 저절로 해제할 수 있습니다.
*/
void f()
{
	//Investment* pInv = createInvestment();	//팩토리 함수를 호출합니다.
	//...									// pInv를 사용합니다.

	/*auto_ptr : 가리키고 있는 대상에 대해 소멸자가 자동으로 delete를 불러주도록 설계되어 있다.*/
	std::auto_ptr<Investment> pInv(createInvestment());	//팩토리 함수를 호출합니다.
	//...												// 예전처럼 pInv를 사용합니다.

	//delete pInv;							//객체를 해제합니다.
}

/* 자원 관리에 객체를 사용하는 방법의 중요한 두가지 특성
첫째: 자원을 흭득한 후에 자원 관리 객체에게 넘깁니다.
자원 흭득과 자원 관리 객체의 초기화가 바로 한 문장에서 이루어지는 것이 일상적이다.

둘째 자원 관리 객체는 자신의 소멸자를 사용해서 자원이 확실히 해제되도록 합니다.
소멸자는 어떤 객체가 소멸될 때(유효범위를 벗어나는 경우가 한가지 예) 자동적으로
호출되기 때문에, 실행 제어가 어떤 경위로 블록을 떠나는가에 상관없이 자원해제가 
제대로 이루어지게 되는것입니다.
*/

/*auto_ptr의 주의점
어떤 객체를 가리키는 auto_ptr의 개수가 둘 이상이면 절대로 안된다.
둘 이상이 하나의 객체를 가리키면 자원을 두번 삭제하는 현상이 발생한다.

auto_ptr의 특성
auto_ptr객체를 복사하면 원본 객체는 null로 만든다.
*/

/*
std::auto_ptr<Investment> pInv1(createInvestment());	//createment 함수에서 반환된 객체입니다.

std::auto_ptr<Investment> pInv2(pInv1);	//pInv2는 현재 그 객체를 가리키고 있는반면, 이제 pInv1은 null입니다.
pInv1 = pInv2;	//지금 pInv1은 그 객체를 가리키고 있으며, pInv2는 null입니다.
*/

/*
auto_ptr이 관리하는 객체는 두 개 이상의 auto_ptr 객체가 물고 있으면 안되는 요구사항과
동적으로 모든 자원에 대한 관리 객체로서 auto_ptr을 쓰는 것은 최선이 아닐듯하다.
예를들어 STL 컨테이너의 경우엔 원소들이 '정상적인'복사 동작을 가져야 하기 때문에
auto_ptr은 이런 복사를 하지 못한다.
그래서 대안으로 참조 카운팅 방식 스마트 포인터(reference-counting smart pointer: RCSP)가 괜찮다.

참조 카운팅 방식 스마트 포인터(reference-counting smart pointer: RCSP)
특정한 어떤 자원을 가리키는 외부 객체의 개수를 유지하고 있다가 그 개수가 0이 되면
해당 자원을 자동으로 삭제하는 스마트 포인터이다.
TR1에서 제공되는 tr1::sharted_ptr이 대표적인 RCSP입니다.

*/

void f()
{
	//...
	std::tr1::shared_ptr<Investment> pInv1(createInvestment());	//팩토리 함수를 호출합니다.
	//...														//예전처럼 pInv1를 사용합니다.
																//shared_ptr의 소멸자를 통해 pInv를 자동으로 삭제합니다.

	std::tr1::shared_ptr<Investment> pInv2(pInv1);				//pInv1 및 pInv2가 동시에 그 객체를 가리키고 있다.
	
	pInv1 = pInv2;												// 마찬가지로 변한 것은 없다.

	/*pInv1 및 pInv2는 소멸되며, 이들이 가리키고 있는 객체도 개수가 0이되어 자동으로 삭제됩니다.
	*/
}

/*
auto_ptr 및 tr1::shared_ptr은 소멸자 내부에서 delete 연산자를 사용합니다.
delete[] 연산자가 아닙니다.
동적으로 할당된 배열에 대해 auto_ptr이나 tr1::shared_ptr을 사용하면 난감해진다.

std::auto_ptr<std::string> aps(new std::string[10]);	//잘못된 delete가 사용됩니다.

std::tr1::shared_ptr<int> spi(new int[1024]);			//같은 문제가 발생합니다.
*/