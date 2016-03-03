#include "SpinLock.h"
#include <iostream>
#include "Timer.h"
#include "Global.h"
#include <thread>


SpinLock::SpinLock(){}

SpinLock::~SpinLock(){}

//begin spin lock
void SpinLock::acquireLock(){
	while (isLocked.test_and_set(std::memory_order_seq_cst));
	curLock = true;
}

//unlocks the spin lock from another thread
void SpinLock::unlock(){
	isLocked.clear(std::memory_order_seq_cst);
	curLock = false;
}

bool SpinLock::getIsLocked(){
	return curLock;
}