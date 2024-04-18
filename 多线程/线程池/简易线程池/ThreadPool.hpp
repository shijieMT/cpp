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
		cout << "准备for循环" << endl;
		for (int i = 0; i < maxCapacity; i++)
		{
			cout << "进入for循环" << endl;
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
		cout << "进入workFunc" << endl;
		while (1) 
		{
			if (taskqueue.isEmpty() && shutdown)break;
			cout << "进入while" << endl;
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
		cv.notify_all();// 析构时确保所有锁已经释放
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