#include "stdafx.h"
#include "Player.h"

Player::Player(char * name, int maxHp, int attackDamage)
{
	cout << "Player 생성자(매개변수)" << endl;
	system("pause");
	Init();

	strcpy_s(className, NAME_LEN, name);

	this->maxHp = maxHp;
	hp = maxHp;

	this->attackDamage = attackDamage;
}

Player::Player()
{
	cout << "Player 생성자" << endl;
}

Player::~Player()
{
	cout << "Player 소멸자" << endl;
	system("pause");
}

void Player::Init(void)
{
	level = 1;
	exp = 0;
	maxExp = 100;
	gold = 0;
}

void Player::Progress(void)
{
}

void Player::Release(void)
{
}

void Player::showStatus(void)
{
	cout << "레  벨: " << level << endl;
	cout << "클래스: " << className << endl;
	cout << "체  력: " << hp << " / " << maxHp << endl;
	cout << "공격력: " << attackDamage << endl;
	cout << "경험치: " << exp << " / " << maxExp << endl;
	cout << "골  드: " << gold << endl;
	cout << "###############################" << endl;
}

void Player::getDamaged(int att)
{
	hp -= att;
}

void Player::resetHp(void)
{
	hp = maxHp;
}

void Player::getReward(int exp, int gold)
{
	this->exp += exp;
	if (this->exp >= maxExp)
	{
		this->exp -= maxExp;

		level++;

		if (!strcmp(className, "전사"))
		{
			maxHp += 30;
			attackDamage += 10;
		}
		else if (!strcmp(className, "마법사"))
		{
			maxHp += 10;
			attackDamage += 20;
		}
		else if (!strcmp(className, "도적"))
		{
			maxHp += 20;
			attackDamage += 15;
		}

		hp = maxHp;
	}

	this->gold += gold;

}

int Player::getAttackDamage(void)
{
	return attackDamage;
}

int Player::getExp(void)
{
	return exp;
}

void Player::setExp(int exp)
{
	this->exp = exp;
}

int Player::getGold(void)
{
	return gold;
}

void Player::setGold(int gold)
{
	this->gold = gold;
}

int Player::getHp(void)
{
	return hp;
}

void Player::setHp(int hp)
{
	this->hp = hp;
}
