#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
void Lock(int n,char c)
{
  mtx.lock();
  for (int i=0; i<n; ++i) { std::cout << c; }
  std::cout << '\n';
  mtx.unlock();
}
int main()
{
 	std::thread th1 (Lock,50,'*');
  	std::thread th2 (Lock,50,'$');

  	th1.join();
  	th2.join();
	return 0;
}
