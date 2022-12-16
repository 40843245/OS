#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <thread>
#include <mutex>
using namespace std;

#define RUNTIMES 50

std::mutex write_mtx;
std::mutex read_mutex;
std::mutex rw_mutex;

void writer(string s)
{
	static int currTime=0;
	do 
	{          
		system("timeout 2");
		currTime++;
		if(rw_mutex.try_lock()==false)
		{
		cout<<"The rw_mutex was NOT locked yet."<<endl;
	 	
	 	write_mtx.lock();
	 	/* writing is performed */	 	
	 	cout<<currTime<<"th:"<<s<<endl;
		write_mtx.unlock();
		}else
		{
			cout<<"The rw_mutex was ALREADY locked yet."<<endl;
		}
	}while (currTime<=RUNTIMES);
	write_mtx.unlock();
}
void reader(string s)
{
	static int read_count=0;
	static int currTime2=0;
		do 
		{ 
			system("timeout 2");
			cout<<"currTime2="<<currTime2<<endl;
			if(write_mtx.try_lock())
			{
				cout<<"The write_mtx was ALREADY locked yet."<<endl;	
			}else
			{
			cout<<"The write_mtx was NOT locked yet."<<endl;
			read_mutex.lock();         
			read_count++;           
			if (read_count == 1)
			{
				rw_mutex.lock();
			}  
			read_mutex.unlock();
			/* reading is performed */
			cout<<"Msg="<<s<<"Read_count="<<read_count<<endl;
			read_mutex.lock();          
			read_count--;           
			if(read_count == 0)
			{
				rw_mutex.unlock();
			} 
			read_mutex.unlock(); 
			}
			currTime2++;
		} while (currTime2<=RUNTIMES);
		
}
int main()
{
	string s1="Writer";
	string s2="Reader 1";
	string s3="Reader 2";
	
	write_mtx.unlock();
	read_mutex.unlock();
	rw_mutex.unlock();
	
	std::thread t1(writer,s1);	
	std::thread t2(reader,s2);
	std::thread t3(reader,s3);
	
	cout<<"The t1 was joined."<<endl;
	t1.join();
	cout<<"The t2 was joined."<<endl;
	t2.join();
	cout<<"The t3 was joined."<<endl;
	t3.join();
	
	return 0;
}
