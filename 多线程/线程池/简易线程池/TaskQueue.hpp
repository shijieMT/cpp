#include<functional>
#include<iostream>
#include<vector>
#include<thread>
#include<queue>
#include<memory>
#include<mutex>
#include<future>
#include<chrono>
using namespace std;

class TaskQueue {
public:
	bool addTask(function<void(void)>&& task)
	{
		taskqueue.push(task);
		return true;
	}
	function<void(void)> getTask()
	{
		auto task  = taskqueue.front();
		taskqueue.pop();
		return task;
	}
	bool isEmpty()
	{
		return taskqueue.empty();
	}
private:
	queue<function<void(void)>>taskqueue;
};
