#include "Player.h"
#include <iostream>
#include "global.h"
#include "Timer.h"
#include "Scheduler.h"


Player::Player(){

}

Player::~Player(){

}

void Player::update(){
	fbr::cout << "updating player" << fbr::endl;
}

void Player::addHp(int amount){
	hp += amount;
}

void Player::printHp(){
	fbr::cout << "player hp: " << hp <<  fbr::endl;
}

void Player::empty(){}

void Player::damage(int amount, bool isMagic){
	if (isMagic)
		hp -= amount * 2;
	else 
		hp -= amount;
}

void Player::move(int x, int y, int z){
	fbr::cout << "x:" << x << " y:" << y << " z:" << z << fbr::endl;
}

void Player::longTask(){
	Timer *t = new Timer();
	t->wait(2);
}

void Player::taskInput(){
	std::string s;
	fbr::cin(s, "Enter some text:");
	fbr::cout << s << fbr::endl;
	Scheduler::wakeUpMain();
}
