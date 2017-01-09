#include "ThreadPool.h"

ThreadPool * ThreadPool::m_instance = nullptr;
ThreadPool * ThreadPool::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new ThreadPool;
	}

	return m_instance;
}
