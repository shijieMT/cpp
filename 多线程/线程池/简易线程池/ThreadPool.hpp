#include"TaskQueue.hpp"

class ThreadPool {
public:
	ThreadPool()
	{
		ThreadPool(50);
	}
	ThreadPool(int maxCapacity)
	{
		{
			unique_lock<mutex>lock_threadpool(mtx_threadpool);
			shutdown = false;
		}
		cout << "׼��forѭ��" << endl;
		for (int i = 0; i < maxCapacity; i++)
		{
			cout << "����forѭ��" << endl;
			workers.push_back(thread(&ThreadPool::workFunc,this));
			cout << "workers.push_back(thread(&ThreadPool::workFunc,this));" << endl;
		}
	}

	~ThreadPool() {
		shutDown();
	}
	bool addTask(function<void(void)> task)
	{
		unique_lock<mutex> lock_taskqueue(mtx_taskqueue);
		bool result = taskqueue.addTask(forward<function<void(void)>>(task));
		if (result) {
			cv.notify_one();
		}
		return result;
	}

private:
	void workFunc()
	{
		cout << "����workFunc" << endl;
		while (1) 
		{
			if (taskqueue.isEmpty() && shutdown)break;
			cout << "����while" << endl;
			function<void(void)> task = []() {};
			//std::this_thread::sleep_for(std::chrono::milliseconds(1));
			{
				unique_lock<mutex> lock_taskqueue(mtx_taskqueue);
				cv.wait(lock_taskqueue, [this]() {
					return !taskqueue.isEmpty() || shutdown;
					});
				if(!taskqueue.isEmpty())
					task = taskqueue.getTask();
			}
			std::thread tmp(task);
			tmp.join();
		}
	}
	void shutDown()
	{
		{
			unique_lock<mutex>lock_threadpool(mtx_threadpool);
			shutdown = true;
		}
		cv.notify_all();// ����ʱȷ���������Ѿ��ͷ�
		for (auto& e : workers) {
			e.join();
		}
	}
private:
	condition_variable cv;
	mutex mtx_taskqueue;
	mutex mtx_threadpool;
	TaskQueue taskqueue;
	vector<thread> workers;
	bool shutdown;
};