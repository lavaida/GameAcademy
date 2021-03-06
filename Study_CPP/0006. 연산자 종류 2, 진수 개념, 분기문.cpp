/*



######################
   N 진수(진법 변환) - 정수 대상으로 수행함.
######################

case 1. 10 진수
- (0~ 9) 10개로 수를 표현함.
- 일반적으로 사용하는 숫자 개념.

case 2. 2 진수
- (0~ 1) 2개로 수를 표현함.
- 기계어가 2 진수를 사용한다.

case 3. 8 진수
- (0~ 7) 8개로 수를 표현함.
- 2진수로 변환 시 (000 ~ 111) 3자리로 표현된다.

- 정수 앞에 "0"을 붙여 8 진수를 명시함 !!!!


case 4. 16 진수
- (0~ 15) 16개로 수를 표현한다.
- A = 10, B = 11, C = 12, D = 13, E = 14, F = 15
- 2진수로 변환 시 (0000 ~ 1111) 4자리로 표현된다.

- 정수 앞에 "0x"를 붙여 16 진수를 명시함 !!!!

###################################################################################################

Question01. 10진수 8부터 20까지 2진수(8bits)와 16진수로 표현하기.
Question02. 10진수 5부터 18까지 8진수로 표현하기.
Question03. 각 2진수들은 10진수로 얼마인가?

0000 0001
0000 0010
0000 0100
0000 1000
0001 0000
0010 0000
0100 0000
1000 0000

Question04. 다음 signed의 4bits는 10진수로 얼마인가

1001
1010

Question05. 정수를 입력 받으면 부호를 바꿔서 출력하기. (단, -1 쓰면 X)


Question06. 3*8/ 4 식을 *와 /를 사용하지 않고 표현하자.

###################################################################################################

###############################
 축약 연산자(복합 대입 연산자) - 이항 연산자
###############################

+=, -=, *=, /=, %=, <<=, >>=

###################################################################################################

##############
 증감 연산자 - 단항 연산자
##############
- 값을 1 증가 or 1 감소 시킨다.

case 1. 전위 증감 연산자
- 증감 연산자가 피연산자 앞에 붙는다.
- 선 증감, 후 연산

int num1 = 5;
cout << num1 << endl;	// 5
cout << ++num1 << endl;	// 6 먼저 연산을 한 뒤에 코드라인을 벗어나서 증감을 한다.
cout << num1 << endl;	// 6

case 2. 후위 증감 연산자
- 증감 연산자가 피연산자 뒤에 붙는다.
- 선 연산, 후 증감(코드 라인을 벗어나야 증감이 적용된다.)

int num2 = 5;
cout << num2 << endl;	// 5
cout << num2++ << endl;	// 5 코드라인을 벗어나야 증감이 이루어진다.
cout << num2 << endl;	// 6


So, 차이점.
전위 증감 연산자는 피연산자 본인을 통해 연산을 진행한다.
- 후위 증감 연산자는 임시 객체를 만들어야하니까 오버헤드가 발생.
 증감이 연산에 영향을 미치지 않는다면, 전위 증감 연산자를 고려해볼 것 !!!!

후위 증감 연산자는 (임시 객체)를 생성 후 본인은 증감하지만, 임시 객체는 연산에 반영한다.
- 임시 객체를 생성하여 자신을 복사 한 후 본인은 증감을 한다.
 이후 연산에 사용되는 것은 임시 객체에 저장된 값을 사용한다.
 코드 라인을 벗어나면 임시 객체는 소멸된다.

###################################################################################################

############
   분기문
############

- 정해진 기준을 토대로 나눈다.
- 프로그램의 실행 흐름을 바꿀 때 사용한다.

#####################
case 1. if문 (조건문)
- 조건이 참일 경우 이후 문장을 수행한다.
- 조건에 거짓(0)이 아닌 모든 값은 참으로 여긴다 !!!!

ex.
if(조건) {
	조건이 참일 경우에 수행하는 코드 block.
}


 else문
- if가 거짓(0)일 경우 처리되는 코드 block을 지정할 수 있다. (예외 처리의 개념)
- 흑백 논리와 같음.(if 아니면 else)
- 혼자 존재할 수 없으며, else문 앞에는 if문이 존재한다.

###########################################################################
(그래서, if~ else 사이에 다른 코드를 작성할 수 없게 된다. 컴파일 오류 !!!!)
###########################################################################

ex. 
if(조건) {

} else {
	조건이 거짓(0)일 때 수행 되는 코드 block.
}


 else if문
- if문으로 여러 조건을 검사할 때 사용한다.
- 둘 이상의 겹치는 동일한 조건이 있을 경우, 가장 먼저 조건이 맞는 것만 수행한다.

if(조건) {

} else if(조건) {

} else {

}


################
case 2. switch문
- 정수를 조건으로 실행 흐름을 나누는 문법
(실수(소수점)는 조건이 될 수 없음.)

ex.

switch(조건: 변수 or 상수 - 정수에 해당) {
case 상수1:
	...
	break;
case 상수2:
	...
	break;

default:
	...
	break;
}

 break문
- (반복문, switch문 내부)에서만 사용이 가능한 명령어
- 해당 (반복문, switch문)을 탈출하기 위해 사용한다.
(그래서, switch문 내부에 break문이 없으면 break문을 만날 때까지 or switch문이 종료될 때까지 수행한다.)


 default문
- switch문에서 해당 조건에 맞는 분기가 없으면 호출되는 부분


###################################################################################################


과제 성적표에 등급 추가하기

A: [90 ~)
B: [80, 90)
C: [70, 80)
D: [60, 70)
E: [50, 60)
F: (0, 50]

*/

#include <iostream>

using namespace std;

int main(void) {
	
	/* ########################################################################################
	Question01. 10진수 8부터 20까지 2진수(8bits)와 16진수로 표현하기.

	case 1. 2진수      case 2. 16진수
	0000 1000 : 8			0x08
	0000 1001 : 9			0x09
	0000 1010 : 10			0x0a
	0000 1011 : 11			0x0b
	0000 1100 : 12			0x0c

	0000 1101 : 13			0x0d
	0000 1110 : 14			0x0e
	0000 1111 : 15			0x0f
	0001 0000 : 16			0x10
	0001 0001 : 17			0x11

	0001 0010 : 18			0x12
	0001 0011 : 19			0x13
	0001 0100 : 20			0x14

	*/

	/* ########################################################################################
	Question02. 10진수 5부터 18까지 8진수로 표현하기.
	
	case 1. 8진수
	005 : 5
	006 : 6
	007 : 7
	010 : 8
	011 : 9

	012 : 10
	013 : 11
	014 : 12
	015 : 13
	016 : 14

	017 : 15
	020 : 16
	021 : 17
	022 : 18
	
	*/

	/* ########################################################################################
	Question03. 각 2진수들은 10진수로 얼마인가?

	0000 0001 : 1
	0000 0010 : 2
	0000 0100 : 4
	0000 1000 : 8
	0001 0000 : 16
	0010 0000 : 32
	0100 0000 : 64
	1000 0000 : 128(부호 그런거 없으면 그냥 절대치로... 있다고 하면 0)

	*/

	/* ########################################################################################
	Question04. 다음 signed의 4bits는 10진수로 얼마인가
		   1의보수 +     1    =  2의 보수
	1001 : (0110)  +  (0001)  =  (0111)  -7

	1010 : (0101)  +  (0001)  =  (0110)  -6
	
	*/

	// ########################################################################################
	//Question05. 정수를 입력 받으면 부호를 바꿔서 출력하기. (단, -1 쓰면 X)

	//int num1 = 0;
	//cin >> num1;

	//cout << "변경 전 num1: " << num1 << endl;

	//// 반전 - XOR
	////num1 = num1 ^ 4294967295;

	//// 반전 - NOT 가능하네?!
	//num1 = ~num1;

	//// +1
	//num1 = num1 + 1;

	//cout << "변경 후 num1: " << num1 << endl;

	// cout << (~iA +1) <<endl;

	// ########################################################################################
	//Question06. 3*8/ 4 식을 *와 /를 사용하지 않고 표현하자.
	

	/*cout << (3 * 8) / 4 << endl;
	int num2 = 3;
	num2 = num2 << 3;
	num2 = num2 >> 2;
	cout << "num2: " << num2 << endl;*/

	// but, (3 << 3) >> 2 상수라서 안됨.

	cout << "##############################################################" << endl;
	cout << "### 복합 대입 연산자(축약 연산자)" << endl;

	int iPlayer_Hp = 100;
	int iMonster_Att = 10;

	iPlayer_Hp = iPlayer_Hp - iMonster_Att;
	cout << "iPlayer_Hp: " << iPlayer_Hp << endl;
	iPlayer_Hp -= iMonster_Att;
	cout << "iPlayer_Hp: " << iPlayer_Hp << endl;

	cout << "##############################################################" << endl;


	return 0;
}
