#include <iostream>
using namespace std;

static class X
{
public:
	 bool isSet;
	 int BufferSize;
	 bool *waiting;
	 bool key;
	 bool lock;
	 int counterProgram;
public:
	void Init()
	{
		isSet=true;
		BufferSize=5;
		waiting=new bool [BufferSize];
		for(int ii=0;ii<BufferSize;ii++)
		{
			waiting[ii]=false;
		}
		key=false;
		lock=false;
		counterProgram=0;
	}
	void IncCounter()
	{
		counterProgram++;
	}
	void DisplayIsSet()
	{
		cout<<"X.isSet="<<isSet<<endl;
	}
	void DisplayMsgLn(string msg)
	{
		DisplayMsg(msg);
		cout<<endl;
	}
	void DisplayMsg(int counter)
	{
		cout<<counter;
	}
	void DisplayMsg(string msg)
	{
		cout<<msg;
	}
};

int main()
{
	X.IncCounter();
	X.DisplayMsg("This is my ");
	X.DisplayMsg(X.counterProgram);
	X.DisplayMsgLn("th program.");
	X.DisplayIsSet();
	if(X.isSet==false)
	{
		X.Init();
		X.DisplayMsgLn("After Initialization.");
		X.DisplayIsSet();
	}
	
	
	return 0;
}
