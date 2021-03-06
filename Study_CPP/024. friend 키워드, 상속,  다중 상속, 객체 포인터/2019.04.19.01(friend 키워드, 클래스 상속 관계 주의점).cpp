/*

2019.04.19.01 금

######################
	friend 키워드
######################

- "클래스의 private 멤버"에 대한 접근 권한을 다른 클레스에게 주도록하는 선언하는 키워드.
(정보 은닉화(Information Hiding)를 위반하는 문법이기 때문에 가급적, 사용을 제한한다.)


#####################################################
friend 키워드로 선언을 누구한테 하는 지가 중요하네...
#####################################################

- 클래스 내부에 다른 클래스를 friend 선언을 한다면,
그 다른 클래스에서 해당 클래스의 private 멤버에 접근이 가능하다고 !!!!

ex. Boy 클래스에다가 Girl 클래스를 friend 선언을 하면,
Girl 클래스에서 Boy 클래스의 private 멤버에 접근이 가능하다.


- 선언 위치는 아무 곳이나 상관없음.
(Access Modifier에 연관되어 있는 대상이 아님.)


############################################################################################################################

##############################
	  상속(Inheritance)
##############################

- 실세계에서의 상속은 부모가 가진 것을 자식에게 물려주는 행위를 말한다.
- 프로그래밍에서 상속의 의미는 기존 정의된 클래스의 멤버를 다른 클래스에게 물려주는 것을 의미함.

###############################################################################
	물려 주는 클래스 : 부모 클래스, base 클래스, 수퍼 클래스, 상위 클래스
	물려 받는 클래스 : 자식 클래스, derived 클래스, 서브 클래스, 하위 클래스
###############################################################################


############################################################################################################################

########################################
   클래스 상속의 Access Modifier 변화
########################################

					 하위 클래스에서
상위 클래스의      |    public 상속   |    protected 상속   |    private 상속
 public      멤버  |     public       |     protected       |     private(얘네는 접근이 가능함.)
				   |                  |                     |
 protected   멤버  |    protected     |     protected       |     private
				   |                  |                     |
 private     멤버  |   (접근불가)     |    (접근 불가)      |    (접근 불가)


- 상위 클래스의 모든 데이터는 하위 클래스에 상속이 된다 !!!!
but, Access Modifier에 따라 하위 클래스에서 접근을 못할 뿐 !!!!

A. "public 상속"은 부모의 private 멤버를 제외한 모든 멤버들의 접근 권한을 그대로 물려준다.

B. "Protected 상속"은 상위 클래스의 public 과 protected 멤버들을 protected 권한으로 물려준다.

#########################################################################################
C. private 상속은 상위 클래스의 모든 멤버를 private 권한으로 물려준다.

- 상위 클래스의 private 멤버는 하위 클래스에서 절대로 직접 접근이 불가능함.
(Member Initailizer를 통해 상위 클래스의 생성자를 호출하여 초기화를 수행해야 한다 !!!!)
#########################################################################################


############################################################################################################################

######################################################
   상속 관계인 클래스의 생성자 및 소멸자 호출 순서
######################################################

########################
case 1. 생성자 호출 순서
########################

- 메모리 할당 -> 상위 클래스 생성자 호출 -> 하위 클래스 생성자 호출

########################
case 2. 소멸자 호출 순서
########################

- 하위 클래스 소멸자 호출 -> 상위 클래스 소멸자 호출 -> 메모리 반환

############################################################################################################################


*/


#include "stdafx.h"
#include "2019.04.19.01 friend.h"

///////////////
// 상속 예제 //
////////////////////////////////////////////////////////////////////////////////////////////////
// 상위 클래스.h

class Person {

public:
	Person(char *name, int age, int money)
		: age(age), money(money)
	{
		strcpy_s(this->name, 16, name);
	}

public:
	void ShowName();
	void ShowAge();

protected:
	int money;

private:
	char name[16];
	int age;
};
////////////////////////////////////////////////////////////////////////////////////////////////
// 하위 클래스.cpp

void Person::ShowName(void) {
	cout << "name: " << name << endl;
}

void Person::ShowAge(void) {
	cout << "age: " << age << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 하위 클래스.h

class Student : public Person { // 하위 클래스에서 상위 클래스를 상속하는 문법에는 ":" 콜론을 붙인다 !!!!
								// Access Modifier에 따라서 상속 받는 멤버에 대한 접근 권한이 결정된다 !!!!
public:
	Student(char *name, int age, int money, char *jobName)
		: Person(name, age, money)
	{
		strcpy_s(this->jobName, 16, jobName);
	}

public:
	void ShowJobName(void);
	void Func(void);

private:
	char jobName[16];
};
////////////////////////////////////////////////////////////////////////////////////////////////
// 하위 클래스.cpp

void Student::ShowJobName(void) {

	cout << "jobName: " << jobName << endl;
}

void Student::Func(void) {
	// Person 클래스의 name, age 멤버는 private이었으므로 접근이 불가능하다 !!!!
	// but, 상위 클래스의 "protected 멤버"였다면 하위 클래스에도 직접 접근이 가능함.
	cout << "Person 클래스의 protected 멤버, money: "<< money << endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////


int main(void)
{
	cout << "####################################################################" << endl;
	cout << "### friend 키워드와 클래스, 클래스의 멤버 함수, 전역 함수" << endl << endl;

	Boy1 boy1;
	Girl girl;

	cout << "case 1. friend 키워드와 클래스" << endl;
	girl.ShowBoy1Money(boy1); // Boy1 클래스에 "friend class Girl;" 선언이 되어있기 때문에,
	cout << endl;			  // Girl 클래스 내부의 모든 부분에서 Boy1 클래스의 "private" 멤버에 접근이 가능 !!!!
	
	Boy2 boy2;
	cout << "case 2. friend 키워드와 클래스의 멤버 함수" << endl;
	boy2.ShowGirlMoney(girl); // Girl 클래스에 "friend void Boy2::ShowGirlMoney(Girl girl);" 선언이 되어있기 때문에,
	cout << endl;			  // Boy2 클래스의 해당 멤버 함수에서는 Girl 클래스의 "Private" 멤버에 접근 가능 !!!!
	
	boy2.Func(girl); // Boy2 클래스의 일반 멤버 함수로, Girl 클래스에서 friend 선언 받은 ShowGirlMoney 멤버함수를 호출함.
	cout << endl;

	cout << "case 3. friend 키워드와 전역 함수" << endl;
	ShowGirlMoney(girl); // Girl 클래스에 전역 함수에 대한 "friend void ShowGirlMoney(Girl girl);" 선언이 되어있다.
						 // 전역 함수 "void ShowGirlMoney(Girl girl)"에서는 Girl 클래스의 "private" 멤버에 접근 가능 !!!!


	cout << "####################################################################" << endl;
	cout << "### 상속(inheritance)" << endl << endl;

	Student std1("Avril", 10, 32, "Programmer"); // Person 클래스를 상속했으므로, 해당 클래스의 멤버도 Access Modifier에 따라 접근이 가능하다.

	cout << "Student 객체로 (public) 멤버 함수를 호출 합니다." << endl;

	std1.ShowName(); // 상위 클래스인 Person 클래스의 private 멤버 변수에 접근할 수 없으므로,
	std1.ShowAge(); // 상위 클래스인 Person 클래스의 public, protected 멤버 함수를 통해 접근해야 한다 !!!!

	std1.Func(); // 상위 클래스인 Person 클래스의 protected 멤버 변수에 직접 접근.
				 // "public 상속"이기 때문에, 상속 받을 때 protected 그대로 받아와서,
				 // 하위 클래스에서도 직접 접근이 가능함.
				 // 물론, 상위 클래스의 "private 멤버"는 상속을 받아오지만, 접근이 불가능하다 !!!!

	std1.ShowJobName(); // Student 클래스 객체 자신의 private 멤버에 직접 접근.
						// (애초에 자신의 멤버니까 당연한 말)

	cout << "####################################################################" << endl;


	return 0;
}