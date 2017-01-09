#pragma once
#include <SFML/System.hpp>
#include <thread>
#include <queue>

using namespace std;

class ThreadQueue
{
private:
	queue<function<void()>> m_tasks;
	bool finished;

	sf::Mutex m_queLock;
public:
	ThreadQueue() : finished(false) { };
	~ThreadQueue() {};

	void AddJob(function<void()> task)
	{
		m_queLock.lock();
		m_tasks.push(task);
		m_queLock.unlock();
	};

	bool IsFinished() const
	{
		return finished;
	}

	bool hasWork() const
	{
		return (m_tasks.size()>0);
	}

	void finish() {
		m_queLock.lock();
		finished = true;
		m_queLock.unlock();
	}

	void DoNextJob()
	{
		m_queLock.lock();

		if (m_tasks.size() == 0) {
			m_queLock.unlock();
			return;
		}

		function<void()> next = m_tasks.front();
		m_tasks.pop();
		//cout << m_tasks.size() << " tasks left in thread pool" << endl;
		m_queLock.unlock();
		next();
	}
};

class ThreadPool
{
private:
	vector<sf::Thread *> m_threads;
	ThreadQueue m_queue;

	static ThreadPool * m_instance;

	ThreadPool()
	{
		for (int i = 1; i < 2; i++)
		{
			m_threads.push_back(new sf::Thread(RunTask, &m_queue));
		}

		for (auto & thread : m_threads)
		{
			thread->launch();
		}
	};
public:
	static ThreadPool * GetInstance();

	~ThreadPool()
	{
		m_queue.finish();
		waitForCompletion();
		for (auto & thread : m_threads)
		{
			thread->wait();
		}
	};

	void AddJob(function<void()> task)
	{
		m_queue.AddJob(task);
	}

	void waitForCompletion() {
		while (m_queue.hasWork()) {}
	}

	static int RunTask(void *ptr)
	{
		ThreadQueue * queue = (ThreadQueue*)ptr;
		while (!queue->IsFinished() || queue->hasWork())
		{
			queue->DoNextJob();
		}

		return 0;
	}
};