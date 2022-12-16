#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define BUFFER_SIZE 3

int main()
{
	int counter=BUFFER_SIZE;
	int out=0;
	int next_cosumed=0;
	int *buffer=new int [BUFFER_SIZE];
	
	srand(time(NULL));
	
	while(true)
	{
		while(counter==0)
		{
			cout<<"NOTHING"<<endl;
		}
		next_cosumed=buffer[out];
		out=(out+1)%BUFFER_SIZE;
		counter--;
		system("pause");
	}
	return 0;
}
