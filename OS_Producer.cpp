#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define BUFFER_SIZE 3

int main()
{
	int counter=0;
	int in=0;
	int next_produced=0;
	int *buffer=new int [BUFFER_SIZE];
	
	srand(time(NULL));
	
	while(true)
	{
		while(counter==BUFFER_SIZE)
		{
			cout<<"NOTHING"<<endl;
		}
		next_produced=rand()%1024;
		buffer[in]=next_produced;
		in=(in+1)%BUFFER_SIZE;
		counter++;
		system("pause");
	}
	return 0;
}
