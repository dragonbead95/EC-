/*항목14 : 자원 관리 클래스의 복사 동작에 대해 진지하게 고찰하자

요점정리
1.RAII 객체의 복사는 그 객체가 관리하는 자원의 복사 문제를 안고 가기 때문에, 그 자원을
어떻게 복사하느냐에 따라 RAII 객체의 복사 동작이 결정됩니다.

2.RAII 클래스에 구현하는 일반적인 복사 동작은 복사를 금지하거나 참조 카운팅을 해주는 선으로 마무리
하는것입니다. 하지만 이 외의 방법들도 가능하니 참고해 둡시다.
*/
#include <mutex>
#include <iostream>

using std::mutex;

void lock(mutex* pm);	//pm이 가리키는 뮤텍스에 잠금을 겁니다.
void unlock(mutex* pm);	// pm이 가리키는 해당 뮤텍스의 잠금을 풉니다.

class Lock
{
public:
	explicit Lock(mutex* pm) : mutexPtr(pm)
	{
		lock(mutexPtr);	//자원을 흭득합니다.
	}
	~Lock()				//자원을 해제합니다.
	{
		unlock(mutexPtr);
	}
private:
	mutex* mutexPtr;

};

int main(void)
{
	mutex m;	//여러분이 쓰고 싶은 뮤텍스를 정의합니다.
	{			//임계영역을 정하기 위해 블록을 만듭니다.
		Lock m1(&m);	//뮤텍스에 잠금을 겁니다.
		//,..			//임계영역에서 할 연사을 수행합니다.
	}			//블록의 끝입니다. 뮤텍스에 걸렸던 잠금이 자동으로 풀립니다.

	{
		Lock ml1(&m);	//m에 잠금을 겁니다.
		Lock ml2(ml1);	//ml1을 ml2로 복사합니다. 어떻게 되어야 맞을까요?
	}
	/*RAII객체가 복사될때 어떤 동작을 이루어야 할까?*/
	/*1. 복사를 금지한다.
	복사를 금지하는 방법
	class Lock:private Uncopyable{	//복사를 금지합니다. 항목6을 보시기 바랍니다.
	public:
		...
	}
	*/
	/*2. 관리하고 있는 자원에 대해 참조 카운팅을 수행합니다.
	자원을 사용하고 있는 마지막 객체가 소멸될 때까지 그 자원을 저 세상으로 안보내는게
	바람직할 경우도 종종 있습니다. 이럴 경우에는, 해당 자원을 참조하는 객체의 개수에 대한 카운트를 증가시키는
	식으로 RAII 객체의 복사 동작을 만들어야 합니다. 이런 방식은 tr1::shared_ptr이 사용하고 있다.
	
	tr1::shared_ptr이 삭제자(deletr)를 지정을 허용한다.
	삭제자란 tr1::shared_ptr이 유지하는 참조카운트가 0이 되었을때 호출되는 함수 혹은
	함수객체를 일컫는다.(auto_ptr은 삭제자 지정이 불가능하다.)
	

	class Lock
	{
	public:
		explicit Lock(mutex* pm)	//shared_ptr을 초기화하는데, 기리킬 포이넡로
			: mutexPtr(pm, unlock)	//mutext객체의 포인터를 사용하고 삭제자로 unlock 함수를 사용합니다.
		{
			lock(mutextPtr.get());	//get의 이야기는 항목15에서..
		}
	private:
		std::tr1::shared_ptr<mutex> mutextPtr;
	};
	mutextPtr의 소멸자는 뮤텍스의 참조 카운트가 0이 될때 tr1::shtread_ptr의 삭제자(unlock)를 자동으로 호출할 것이다.
	*/

	/*3. 관리하고 있는 자원을 진짜로 복사합니다.
	자원까지 복사하기 위해서는 깊은복사(depp copy)를 수행해야 한다.
	깊은 복사를 하게되면 포인터 및 그 포인터가 가리키는 새로운 힙 메모리를 갖게 된다.
	*/
	/*4. 관리하고 있는 자원의 소유권을 옮깁니다.
	어떤 특정한 자원에 대해 그 자원을 실제로 참조하는 RAII객체는 닥 하나만 존재하도록 만들고 싶어서,
	그 RAII객체가 복사 될때 그 자원의 소유권을 사본 쪽으로 아예 옮겨야 할 경우도 있다.
	이런 경우의 스타일 복사는 auto_ptr의 복사 동작이다.
	*/
}