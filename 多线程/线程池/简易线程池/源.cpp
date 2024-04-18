#include"ThreadPool.hpp"
int main()
{
	TaskQueue taskqueue;
	auto task1 = []() {
		cout << "hello word" << endl;
		cout << this_thread::get_id << " :ehkllo" << endl; 
	};
	auto task2 = []() {
		cout << this_thread::get_id << " :helloe" << endl;
	};
	ThreadPool pool(50);
	pool.addTask(task1);
	pool.addTask(task1);
	pool.addTask(task2);
	pool.addTask(task2);
}
