#ifndef CON_IOSTREAM_H
#define CON_IOSTREAM_H

#include <atomic>
#include <thread>
#include <string>
#include <iostream>
#include <mutex>

using std::string;

namespace fbr{
	static std::atomic_flag writeFlag = ATOMIC_FLAG_INIT;

	//concurrent standard output
	class Log
	{
	public:
		//standard log
		Log(){
			getLock();
		}

		//Warning logger, prints the function name too
		Log(const std::string &funcName){
			while (writeFlag.test_and_set(std::memory_order_seq_cst));
			std::cout << "Warning! " << funcName << ": " << std::endl;
		}

		//spinlock until lock is acquired
		static void getLock(){
			while (writeFlag.test_and_set(std::memory_order_seq_cst));
		}

		//print the next value
		template <class T>
		Log &operator<<(const T &v){
			std::cout << v;
			return *this;
		}

		// function that takes a custom stream, and returns it
		typedef Log& (*LogManipulator)(Log&);

		//take a function with the typedef signature
		Log& operator<<(LogManipulator manip){
			return manip(*this);
		}

		//release lock after printing has completed
		~Log(){
			//release lock
			writeFlag.clear(std::memory_order_seq_cst);
		}
	};

	//custom endl for character stream using inline function
	inline Log& endl(Log& log){
		std::cout << std::endl;
		return log;
	}

	//preprocessor directives for cout and cout_warn
	#define con_cout Log()
	#define con_cout_warn Log(__FUNCTION__)

	//mutex for taking input
	static std::mutex *readMutex = new std::mutex();
	//take input and t is set to input value
	template<class T>
	static void con_input(T& t){
		while (readMutex->try_lock());
		std::cin >> t;
		readMutex->unlock();
	}

	//print message using fbr::cout then call cin()
	template<class T, class MSG>
	static void con_input(T& t, MSG msg){
		con_cout << msg;
		con_input(t);
	}
}

#endif