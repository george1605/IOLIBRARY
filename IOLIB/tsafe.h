#pragma once
#include <thread>
#include <atomic>
#include <mutex>
#include "core.h"

namespace io
{

	class os_thread // uses os functions rather than std::thread
	{
	private:
		int id;
	public:
		os_thread()
		{
#if defined(_WIN32)
#include <Windows.h>
#include <processthreadsapi.h>
			
#endif
#if defined(__linux__) || defined(_UNIX_)
			this->id = fork();
#endif
		}
	};

	class atomic : public std::atomic<int>
	{
	private:
	
	};

	class thread : public std::thread
	{
	private:

	public:
		void pause()
		{
			this->detach();
			io::simple_wait();
			this->join();
		}
	};

	class mutex : public std::mutex
	{
	public:
#ifdef _WIN32
#include <Windows.h>
#include <synchapi.h>
		HANDLE lock()
		{
			return CreateMutex(NULL, TRUE, );
		}


#endif
		mutex()
		{
			
		}
	};
}