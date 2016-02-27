#include <iostream>
#include "Task.h"
#include "Player.h"
#include "Scheduler.h"
#include "Global.h"

using namespace std;

int main(){
	Player *p = new Player();
	std::function<void()> startfn = std::bind(&Player::printHp,p);
	Task *startingTask = new Task(startfn);

	Scheduler *scheduler = new Scheduler(3,2, *startingTask);
	if (scheduler->getIsConstructed() == false){
		return 0;
	}

	scheduler->waitAllFibersFree();

	function<void()> fn = std::bind(&Player::update, p);
	Task *task1 = new Task(fn);
	scheduler->runTask(*task1);

	scheduler->close();
	system("pause");

	//wait until schduler ends (should use condiction variable here i think)
	while (scheduler->getEndProcess() == false){
		std::this_thread::yield();
	}

	delete scheduler;
	std::cout << "Scheduler deleted" << std::endl;
	Timer *timer = new Timer();
	timer->wait(1);
	delete timer;
}