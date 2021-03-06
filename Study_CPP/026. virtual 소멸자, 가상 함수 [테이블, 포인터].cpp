/*

#####################################
   가상 소멸자(Virtual Destructor)
#####################################

객체 포인터를 통한 메모리 동적 할당에서 소멸자 호출 문제 해결 - 가상 소멸자
소멸자 앞에 virtual 키워드가 붙으면 가상 소멸자라 일컫는다.

class Obj;
class Player : public Obj;

Obj *pObj = new Player;

##########################################################
case 1. 상속관계가 이렇고, 일반적인 소멸자를 사용한다면...
##########################################################

- 포인터 변수의 클래스인 상위 클래스 Obj를 기준으로 함수 호출을 하므로,
하위 클래스인 Player 클래스의 소멸자를 호출하지 않는다.


생성자 호출 순서
- 메모리 할당 -> 상위 클래스 생성자 -> 하위 클래스 생성자

소멸자 호출 순서
- 하위 클래스 소멸자 -> 상위 클래스 소멸자 -> 메모리 반환

#########################################################
case 2. 상속관계가 이렇고, virtual 소멸자를 사용한다면...
#########################################################

가상 함수의 경우와 마찬가지로 "delete pObj;" 문장을 수행할 때.
- pObj가 실제 가리키는 대상인 하위 클래스인 Player 클래스의 소멸자가 먼저 호출 되고, 
- 상위 클래스인 Obj 클래스의 소멸자가 뒤이어 호출 된다.



##################################################################################################

##############################################
    가상 함수 테이블과 가상 함수 포인터?!
##############################################

- 객체 포인터 변수가 가리키는 실제 대상인 객체가 호출하는 함수들의 위치 정보(주소)를 담을 수 있는 포인터 배열입니다.

- 클래스 내에 가상 함수가 존재하면, 컴파일러는 실제로 호출되어야 할 함수의 위치 정보를 담을 수 있는
 "가상 함수 테이블"을 메모리 영역 중 Code 영역에 프로그램 시작 시, 자동적으로 만들어준다 !!!!

- 가상 함수의 개수만큼 가상 함수 테이블의 배열 길이가 증가함.


그래서, 실제 대상 객체의 가상 함수를 호출하기 위해,
 해당 클래스에는 "가상 함수 테이블"을 참조하는 "가상 함수 포인터"가 추가 된다.



######################################
     가상 함수 포인터 (void **)형
######################################

- 가상 함수가 존재하는 클래스에 컴파일러가 "가상 함수 테이블"과 함께 "가상 함수 포인터"를
클래스의 멤버로 프로그램 시작 시, 자동으로 추가한다.


- 가상 함수 포인터는 객체가 할당된 공간에 할당이 된다?!
(정적 객체면 Stack 메모리 영역에, 동적 객체면 Heap 메모리 영역에...)


################################################################################
디버깅을 통해, 가상 함수 포인터와 테이블이 메모리에 잡히는 것을 꼭 확인하기 !!!!
################################################################################

- 클래스의 시작 주소와 같음.
(처음 4 bytes가 가상 함수 포인터)

- 가상 함수 포인터가 가리키고 있는 것은 가상 함수 테이블의 위치 !!!!
- (void **)형이므로 배열(가상함수 테이블)의 주소를 저장하고 있음.


##################################################################################################

###############################
    Virtual Function의 단점
###############################

- 가상 함수 포인터(객체가 할당된 메모리 영역)와 가상 함수 테이블(Code 영역)에 관한 메모리 공간이 필요하다.
- 가상 함수 테이블을 거쳐 함수 호출이 되기 때문에, 프로그램 실행 속도라는 성능적인 측면에서 불리하다.

but, 장점이 많으니까...


##################################################################################################

#################################
   디버깅(Debuging) 하는 방법
#################################

1. F9 - 중단점 설정


2. F5 - 디버깅 모드 시작.
(화살표의 위치는 바로 다음에 수행할 문장.
물론, 화살표 위치는 마우스 드래그로 옮길 수도 있음 ㅋㅋㅋㅋ)

그리고, 디버깅 모드 중 F5를 누르면 다음 중단점까지 흐름을 바로 수행할 수 있음.

반복문 수행 도중 몇 번째 수행인지 확인할 때...
(중단점을 마우스 우클릭하면, 조건이라는 카테고리 있음.)


Runtime Error로 프로그램이 터졌을 떄, Call Stack View를 통해서 해당 위치를 확인하고,
다시 디버깅을 수행한 뒤, 변수의 값을 비교하면 된다 !!!!


3. F10 - 한 줄 실행(함수 내부로 들어가지 않음.)


4. F11 - 한 코드 실행(함수 내부로 들어가서 해당 함수 흐름까지 확인 가능.)
(Shift + F11 - 함수 내부를 빠져나옴.)


5. Shift + F5 : 디버깅 모드 종료.

- Watch View를 통해서 원하는 변수의 값을 확인할 수 있음.


##################################################################################################


*/

#include <iostream>

using std::cout;
using std::endl;
using std::cin;

//////////////////////////////////////////////////////////////////////////////////////
// 상위 클래스
// case 1. virtual 키워드를 사용하지 않은 소멸자의 경우.
class Obj
{
public:
	Obj()
	{
		cout << "Obj 생성자" << endl;
	}
	~Obj()
	{
		cout << "Obj 소멸자" << endl;

	}
};

// case 2. virtual 키워드를 사용한 Virtual Destructor의 경우.
class Obj2
{
public:
	Obj2()
	{
		cout << "Obj 생성자" << endl;
	}
	virtual ~Obj2()
	{
		cout << "Obj 소멸자(virtual)" << endl;

	}
};

//////////////////////////////////////////////////////////////////////////////////////
// 하위 클래스
// case 1. virtual 키워드를 사용하지 않은 소멸자의 경우.
class Player : public Obj
{
public:
	Player()
	{
		cout << "Player 생성자" << endl;

	}
	~Player() // Obj 클래스의 포인터 변수로 Player 객체를 가리킨 뒤, 메모리 해제하면...
	{		  // 상위 클래스인 Obj 클래스의 소멸자는 호출이 되지만, 
			  // 하위 클래스인 Player 클래스의 소멸자는 호출 되지 않는다.
		cout << "Player 소멸자" << endl;
	}
};

// case 2. virtual 키워드를 사용한 Virtual Destructor의 경우.
class Player2 : public Obj2
{
public:
	Player2()
	{
		cout << "Player 생성자" << endl;

	}
	virtual ~Player2() // 이번에는 소멸자에 virtual 키워드를 사용한 케이스입니다.
	{				   // Obj2 클래스의 포인터 변수로 Player2 객체를 가리킨 뒤, 메모리 해제하면...
					   // 이번에는 하위 클래스인 Player2 클래스의 소멸자가 호출이 되고 난 뒤.
					   // 상위 클래스인 Obj2 클래스의 소멸자가 호출이 됩니다 !!!!
		cout << "Player 소멸자(virtual)" << endl;

	}
};
//////////////////////////////////////////////////////////////////////////////////////

class Object11 // 가상 함수가 없는 클래스
{
public:
	Object11() {}
	~Object11() {}
};

class Object22 // 가상 함수가 있는 클래스
{
public:
	Object22() {}
	virtual ~Object22() {}

public:
	virtual void Render(void)
	{
		cout << "Object22::Render()" << endl;
	}
};

class Player22 : public Object22 // 상위 클래스의 가상 함수를 Overriding한 하위 클래스
{
public:
	virtual void Render(void)
	{
		cout << "Player22::Render()" << endl;
	}
};

class SubPlayer22 : public Player22 // 상위 클래스의 가상 함수를 Overriding한 하위 클래스
{
public:
	virtual void Render(void)
	{
		cout << "SubPlayer22::Render()" << endl;
	}
};

//////////////////////////////////////////////////////////////////////////////////////


int main(void)
{
	cout << "########################################################################" << endl;
	cout << "### virtual 키워드와 클래스의 소멸자" << endl << endl;

	cout << "### 상위 클래스의 포인터 변수로 하위 클래스 가리킬 때 ###" << endl << endl;
	cout << "case 1. 일반적인 소멸자의 경우" << endl;
	// 객체 포인터를 통한 메모리 동적 할당에서 소멸자 호출 문제
	// delete 대상이 Obj 타입 객체 포인터이다.
	// Obj 타입 기준으로 소멸자가 호출, 즉 부모 소멸자만 호출하고 끝이난다.

	Obj *pObj = new Player;
	delete pObj; // 상위 클래스의 소멸자만 호출했음.
	cout << endl;// 하위 클래스의 소멸자도 호출해야 함 !!!!
				 // 그래서, virtual destructor 사용 !!!!
	
	cout << "case 2. Virtual Destructor를 사용한 경우" << endl;
	Obj2 *pObj2 = new Player2;
	delete pObj2; // 상위 클래스인 Obj2 클래스의 소멸자가 virtual로 선언되어 있다.
	cout << endl; // 그래서, Obj2 클래스의 포인터 변수로 Player2 객체를 가리켰을 때,
				  // 객체 소멸 시, 하위 클래스의 소멸자 - 상위 클래스 소멸자 순으로 호출이 된다 !!!!

	cout << "########################################################################" << endl;
	cout << "### 가상 함수 포인터 확인" << endl << endl;

	cout << "가상함수가 없는 클래스 Object: " << sizeof(Object11) << endl;
	// 멤버가 없는 클래스일 경우, 주소가 겹칠 수도 있기 때문에 최소 1 bytes를 가진다.
	// 메모리에 추가적으로 할당이 일어날 경우, 시작 주소가 공유될 수 있기 때문에 문제가 발생 !!!!
	
	cout << "가상함수가 있는 클래스 Object2: " << sizeof(Object22) << endl;
	// 가상 함수(virtual 소멸자)가 존재하기 때문에, 컴파일러가 클래스의 멤버로 "가상 함수 포인터"를 넣어줌.
	// 그래서, 다른 멤버 변수가 없고 가상 함수 포인터만 있으므로 4 bytes


	// 가상 함수 테이블을 확인하기 위해 !!!!!
	// 디버깅 모드에서 객체를 찍어서 확인할 수 있음.
	
	// 수정수정수정수정수정
	
	cout << "########################################################################" << endl;
	cout << "### 가상 함수 포인터의 동작 확인" << endl << endl;

	Object22 *pObj3 = new Player22;
	Object22 *pObj4 = new SubPlayer22;

	// pObj3의 가상 함수 포인터는 Player의 Render 함수의 주소를 갖는다.
	// pObj4의 가상 함수 포인터는 SubPlayer의 Render 함수의 주소를 갖는다.

	pObj3->Render(); // Player22의 Render() 함수
	pObj4->Render(); // SUbPlayer22의 Render() 함수

	// 중단점 걸고, 디버깅 모드로 들어가서 pObj3, pObj4를 Watch View에 입력한 뒤,
	// __vfptr의 주소를 보면 된다.
	// &(pObj3->__vfptr), &(pObj3->__vfptr) = 각 객체의 시작 주소.

	delete pObj3;
	delete pObj4;

	cout << "########################################################################" << endl;

	return 0;
}