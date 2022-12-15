/*-------
INFO:

(1)ID:40843245
(2)Name:Huang Jay
(3)HW: OS-Banker's algorithm
(4)NOTE!!!
This is the first version
which is NOT optimized.
Thus,the code is too long.
i.e. sloc is too large.

-------*/

#include <iostream>
#include <algorithm> //For func next_permutation
#include <vector>
#include <cstring> 
#include <cmath> //For func tgamma
#include <cstdlib> //For func system

using namespace std;

//uncomment it for see the information about the Banker class
//#define DEBUG1
//#define DEBUG2

//Behave similar as extension 1D array.
class Matrix1D
{
public:
	int row;
	int *matrix1D;
public:
	Matrix1D(int row)
	{
		this->SetRow(row);
		this->matrix1D=this->Allocate1DMatrix(this->row);
	}
public:
	void Input1DMatrix(string name)
	{
		cout<<"You have to input data for the 1D matrix, name:"<<name<<endl;
		for(int i=0;i<this->row;i++)
		{
			cout<<name<<"["<<i<<"]:";
			cin>>this->matrix1D[i];
		}
	}
public:
	void SetRow(int row)
	{
		this->row=row;
	} 
public:	
	int *Allocate1DMatrix(int row,int defaultValue=0)
	{
		int *temp=new int [row];
		for(int i=0;i<row;i++)
		{
			temp[i]=defaultValue;
		}
		return temp;
	}
public:
	Matrix1D* Sub_1D_1D(Matrix1D* m1D2)
	{
		Matrix1D *m1=new Matrix1D(m1D2->row);
		for(int i=0;i<this->row;i++)
		{
			m1->matrix1D[i]=this->matrix1D[i]-m1D2->matrix1D[i];
		}
		return m1;
	} 
	Matrix1D* Add_1D_1D(Matrix1D* m1D2)
	{
		Matrix1D *m1=new Matrix1D(m1D2->row);
		for(int i=0;i<this->row;i++)
		{
			m1->matrix1D[i]=this->matrix1D[i]+m1D2->matrix1D[i];
		}
		return m1;
	}	
};

//Behave similar as extension 2D array.
class Matrix2D
{
public:
	int row;
	int col;
	int **matrix2D;
public:
	Matrix2D(int row,int col)
	{
		this->SetRowCol(row,col);
		this->matrix2D=this->Allocate2DMatrix(this->row,this->col);
	}
	Matrix2D(Matrix2D *m2D)
	{
		this->SetRowCol(m2D->row,m2D->col);
		this->matrix2D=this->Allocate2DMatrix(this->row,this->col);
	}
public:
	void Input2DMatrix(string name)
	{
		cout<<"You have to input data for the 2D matrix, name:"<<name<<endl;
		for(int i=0;i<this->row;i++)
		{
			for(int j=0;j<this->col;j++)
			{
				cout<<name<<"["<<i<<"]"<<"["<<j<<"]:";
				cin>>this->matrix2D[i][j];
			}
		}
	}
public:
	void SetRowCol(int row,int col)
	{
		this->row=row;
		this->col=col;
	}
public:
	int **Allocate2DMatrix(int row,int col,int defaultValue=0)
	{
		int **temp=new int *[row];
		for(int i=0;i<row;i++)
		{
			temp[i]=new int[col];
			for(int j=0;j<col;j++)
			{
				temp[i][j]=defaultValue;
			}
		} 
		return temp;
	} 
public:
	Matrix2D* Sub_2D_2D(Matrix2D* m2D2)
	{
		Matrix2D *m2=new Matrix2D(m2D2->row,m2D2->col);
		for(int i=0;i<this->row;i++)
		{
			for(int j=0;j<this->col;j++)
			{
				m2->matrix2D[i][j]=this->matrix2D[i][j]-m2D2->matrix2D[i][j];			
			}
		}
		return m2;
	}
	Matrix2D* Add_2D_2D(Matrix2D* m2D2)
	{
		Matrix2D *m2=new Matrix2D(m2D2->row,m2D2->col);
		for(int i=0;i<this->row;i++)
		{
			for(int j=0;j<this->col;j++)
			{
				m2->matrix2D[i][j]=this->matrix2D[i][j]+m2D2->matrix2D[i][j];			
			}
		}
		return m2;
	}
	
	Matrix2D* Sub_2D_1D(Matrix1D* m1D2,int idx)
	{
		Matrix2D *m2=new Matrix2D(this->row,this->col);
		for(int i=0;i<this->row;i++)
		{
			for(int j=0;j<this->col;j++)
			{
				if(i==idx)
				{
					m2->matrix2D[i][j]=this->matrix2D[i][j]-m1D2->matrix1D[i];			
				}else
				{
					m2->matrix2D[i][j]=this->matrix2D[i][j];
				}
			}
		}
		return m2;
	}
	
	Matrix2D* Add_2D_1D(Matrix1D* m1D2,int idx)
	{
		Matrix2D *m2=new Matrix2D(this->row,this->col);
		for(int i=0;i<this->row;i++)
		{
			for(int j=0;j<this->col;j++)
			{
				if(i==idx)
				{
					m2->matrix2D[i][j]=this->matrix2D[i][j]+m1D2->matrix1D[i];			
				}else
				{
					m2->matrix2D[i][j]=this->matrix2D[i][j];
				}
			}
		}
		return m2;
	}
};

//Utility func
Matrix1D* Add_1D_2D(Matrix1D *m1D1,Matrix2D *m2D2,int idx)
{
		Matrix1D *m1=new Matrix1D(m1D1->row);
		for(int i=0;i<m1D1->row;i++)
		{
			m1->matrix1D[i]=m1D1->matrix1D[i]+m2D2->matrix2D[idx][i];
		}
		return m1;
}

//Class for request of resources
class RequestPair
{
public:
	int no;
	int availIdx;
	Matrix1D *request;
public:
	RequestPair(int no,Matrix1D *req)
	{
		this->no=no;
		this->request=req;
	}
};

//Driver class
class Banker
{
public:
	int numOfProcess;
	int numOfResource;
	Matrix2D *allocation;
	Matrix2D *maxAllocation;
	Matrix2D *need; 
	Matrix1D *available;
	Matrix1D *work;
	Matrix1D *finish;
	Matrix1D *req;
	Matrix1D *availProcess;
	Matrix1D *mapTable;
	
	RequestPair *reqPair;
	
	vector< vector<int> > allSol;
	vector< int > tempVector;
	int currIdx;
	int currCnt;
	int currFinishCnt;
	int currMapIdx;
	int isEnd;
public:
	Banker()
	{
		
	}
public:
	void Input()
	{
		cout<<"Enter number of Process"<<endl;
		cin>>this->numOfProcess;
		
		cout<<"Enter number of Resource"<<endl;
		cin>>this->numOfResource;
			
		this->allocation=new Matrix2D(this->numOfProcess,this->numOfResource); 
		this->maxAllocation=new Matrix2D(this->numOfProcess,this->numOfResource); 
		this->need=new Matrix2D(this->numOfProcess,this->numOfResource); 
		
		this->available=new Matrix1D(this->numOfResource);
		this->work=new Matrix1D(this->numOfResource);
		this->finish=new Matrix1D(this->numOfProcess);		
		this->availProcess=new Matrix1D(this->numOfProcess);
		
		this->mapTable=new Matrix1D(this->numOfProcess);
		this->InitMapTable();
		
		this->allocation->Input2DMatrix("allocation");
		this->maxAllocation->Input2DMatrix("maxAllocation");	
		this->available->Input1DMatrix("available");
		
	}
public:
	void InitMapTable()
	{
		for(int i=0;i<this->mapTable->row;i++)
		{
			this->mapTable->matrix1D[i]=i;
		}
	}
public:
	void InitAll()
	{
		this->need=this->maxAllocation->Sub_2D_2D(this->allocation); 
		this->work=this->available;	
	}
public:
	int TryRequest(int reqFlag)
	{
		this->InitAll();
		this->work=this->available;
		
		int idx=0;
		do
		{
			cout<<"Request:";
			cin>>idx;
			cout<<endl;
		}
		while(idx<0 || idx>=this->numOfProcess);
		
		this->req=new Matrix1D(this->numOfResource);
		this->req->Input1DMatrix("request");
		#ifdef DEBUG1
		this->Display1DMatrix(this->req,"request","request");
		this->DisplayInfo();
		#endif
		this->reqPair=new RequestPair(idx,this->req);
		this->reqPair->no=idx;
		this->reqPair->availIdx=this->reqPair->no;
		
		return this->ResourceRequest(reqFlag);
	}
public:
	int SafeAlgorithm(int printFlag=1)
	{
		this->InitAll();
		int safeState=this->CheckSafe();
		if(safeState==1)
		{
			cout<<"Safe"<<endl;
			if(printFlag==1)
			{
				cout<<"The processes are shown as follow respectively."<<endl;
				this->Display1DMatrix(this->availProcess,"availProcess","availableProcess");
			}
		}else
		{
			cout<<"Un-safe"<<endl;
		}
		return safeState;
	}
	int CheckSafe()
	{
		int isAvailable=0;
		this->currIdx=0;
		this->isEnd=0;
		this->currCnt=0;
		this->currFinishCnt=0;
		this->currMapIdx=0;
		
		this->finish=new Matrix1D(this->numOfProcess);		
		this->work=this->available;
		while(true)
		{
			this->currMapIdx=this->mapTable->matrix1D[this->currIdx];
			isAvailable=this->IsAvailableProcess(this->currMapIdx);
			if(isAvailable!=0)
			{
				this->work=Add_1D_2D(this->work,this->allocation,this->currMapIdx);
				this->finish->matrix1D[this->currMapIdx]=1;
				this->availProcess->matrix1D[this->currFinishCnt]=this->currMapIdx;
				this->currFinishCnt+=1;
				this->currCnt=0;
				this->currIdx=(this->currIdx+1)%this->numOfProcess;
				continue;
			}
			if(this->currFinishCnt>=this->numOfProcess)
			{
				this->isEnd=1;
				break;
			}
			if(this->currCnt>=this->numOfProcess)
			{
				this->isEnd=-1;
				break;
			}
			this->currIdx=(this->currIdx+1)%this->numOfProcess;
			this->currCnt+=1;
		}
		return this->isEnd;
	}
public:
	int ResourceRequest(int reqFlag)
	{
		int reqState=this->RequestPairLTMatrix2D(this->reqPair,this->need);
		int availableState=0;
		int nextSafeState=0;
		
		if(reqFlag==0)
		{
			cout<<"Error!!!"<<endl;
			cout<<"Failed to handle the request"<<endl;
			cout<<"since it is NOT in safe state before request."<<endl;
			return -2;
		}
		if(reqState==0)
		{
			availableState=this->Matrix1DLTMatrix1D(this->reqPair->request,this->work);
			if(availableState==0)	
			{			
				this->PretendAllocate();
				nextSafeState=this->CheckSafe();
				if(nextSafeState==1)
				{
					cout<<"The request is allocated successfully."<<endl;
					cout<<"The processes are shown as follow respectively."<<endl;
					Display1DMatrix(this->availProcess,"availProcess","availableProcess");
					return 1;
				}
				else
				{
					cout<<"WARNING!!!"<<endl;
					cout<<"The request is rejected now. The request must have to wait for enough resource"<<endl;
					cout<<"since the deadlock will occurs after the allocation of the request."<<endl;
					return 0;
				}			
			}
		}
		cout<<"ERROR!!!"<<endl;
		cout<<"Failed to handle the request."<<endl;
		cout<<"reqState="<<reqState<<",nextSafeState="<<nextSafeState<<",availableState="<<availableState<<endl;
		return -1;
	}
public:
	void PretendAllocate()
	{
		this->available=this->available->Sub_1D_1D(this->reqPair->request);
		this->allocation=this->allocation->Add_2D_1D(this->reqPair->request,this->reqPair->availIdx);
		this->need=this->need->Sub_2D_1D(this->reqPair->request,this->reqPair->availIdx);
		this->work=this->available;
	}
public:
	int IsAvailableProcess(int idx)
	{
		int hasDone=(this->finish->matrix1D[idx]==0);
		#ifdef DEBUG2
		this->DisplayInfo();
		#endif
		int isNeedLTWork=(this->Matrix2DLTMatrix1D(this->need,this->work,idx)==0);
		return (((hasDone&& isNeedLTWork)!=0)?1:0);
	}
public:
	int Matrix1DLTMatrix1D(Matrix1D *m1D1,Matrix1D *m1D2)
	{
		if(m1D1->row!=m1D2->row)
		{
			cout<<"ERROR!!! The size of two one-dimension vector must be same!!!"<<endl;
			return -1;
		}
		for(int i=0;i<m1D1->row;i++)
		{
			int lv=m1D1->matrix1D[i];
			int rv=m1D2->matrix1D[i];
			if(lv>rv)
			{
				return -2;
			}
		}
		return 0;
	}
public:
	int RequestPairLTMatrix2D(RequestPair *request,Matrix2D *need)
	{
		if(request->request->row!=need->col)
		{
			cout<<"ERROR!!! The row of request is NOT same as the col of need!!!"<<endl;
			return -1;
		}
		for(int i=0;i<request->request->row;i++)
		{
			int lv=request->request->matrix1D[i];
			int rv=need->matrix2D[request->no][i];
			if(lv>rv)
			{
				cout<<"ERROR!!! The request must be less than need."<<endl;
				cout<<"Since the request is larger than need, the request is rejected, and the exception was thrown."<<endl;
				return -2;
			}
		}
		return 0;
	}
public:
	int Matrix2DLTMatrix1D(Matrix2D *need,Matrix1D *work,int idx)
	{
		if(need->col!=work->row)
		{
			cout<<"ERROR!!! The col of need is NOT same as the row of work!!!"<<endl;
			return -1;
		}
		for(int i=0;i<work->row;i++)
		{
			int lv=need->matrix2D[idx][i];
			int rv=work->matrix1D[i];
			if(lv>rv)
			{
				return -2;
			}
		}
		return 0;
	}
public:
	void DisplayInfo()
	{
		this->DisplayExtraComment();
		this->DisplayExtraLine();
		cout<<"numOfProcess="<<this->numOfProcess<<",numOfResource="<<this->numOfResource<<endl;
		this->DisplayExtraLine();
		this->Display2DMatrix(this->allocation,"allocation","allocation");
		this->Display2DMatrix(this->maxAllocation,"maxAllocation","maxAllocation");
		this->Display2DMatrix(this->need,"need","need");
		this->DisplayExtraLine();
		this->Display1DMatrix(this->available,"available","available");
		this->Display1DMatrix(this->work,"work","work");
		this->Display1DMatrix(this->finish,"finish","finish");
		this->DisplayExtraLine();
		this->DisplayExtraComment();
	}
public:
	void DisplayExtraLine()
	{
		cout<<"----------------------------------------"<<endl;
	}
	void DisplayExtraComment()
	{
		cout<<"/*------------------------------------*/"<<endl;
	}
public:
	void Display2DMatrix(Matrix2D *m2D1,string msg,string name)
	{
		this->Display2DMatrix(m2D1->matrix2D,m2D1->row,m2D1->col,msg,name);
	} 
	void Display2DMatrix(int **matrix,int row,int col,string msg,string name)
	{
		cout<<"name:"<<name<<endl;
		for(int i=0;i<row;i++)
		{
			for(int j=0;j<col;j++)
			{
				cout<<msg<<"["<<i<<"]"<<"["<<j<<"]"<<"="<<matrix[i][j]<<endl; 
			}
		}
	}
	void Display1DMatrix(Matrix1D *m1D1,string msg,string name)
	{
		this->Display1DMatrix(m1D1->matrix1D,m1D1->row,msg,name);
	} 
	void Display1DMatrix(int *matrix,int row,string msg,string name)
	{
		cout<<"name:"<<name<<endl;
		for(int i=0;i<row;i++)
		{
			cout<<msg<<"["<<i<<"]"<<"="<<matrix[i]<<endl; 
		}
	}  
public:
	void PermutationAll()
	{
		int ith=1;
		cout<<"All Possible Permutation:"<<endl;
		
		int numOfPosSol=tgamma(this->numOfProcess+1);
		this->allSol.resize(numOfPosSol);
		for(int i=0;i<this->allSol.size();i++)
		{
			this->allSol[i].resize(this->numOfProcess);
			this->allSol[i].clear();
		}
		this->tempVector.resize(this->numOfProcess);
		do
		{
			cout<<"The "<<ith<<"th possible solutions."<<endl;
 	   		this->SafeAlgorithm(0);
 	   		
 	   		tempVector=this->Matrix1DToVector(this->availProcess);
 	   		int containSameVector=this->CheckRepeatResult(ith);
 	   		if(containSameVector==0)
 	   		{
 	   			this->allSol[ith]=this->tempVector;
 	   			for(int i=0;i<this->allSol[ith].size();i++)
 	   			{
 	   				cout<<"P"<<this->allSol[ith][i];
 	   				if(i!=this->allSol[ith].size()-1)
 	   				{
 	   					cout<<"->";
					}
				}
				cout<<endl;
			}
 	   		system("pause");
 	   		ith+=1;
  		} while (next_permutation(this->mapTable->matrix1D,this->mapTable->matrix1D+this->mapTable->row));
	}
public:
	vector<int> Matrix1DToVector(Matrix1D *m1D1)
	{
		vector <int> t;
		t.resize(m1D1->row);
		t.clear();
		for(int i=0;i<m1D1->row;i++)
		{
			t.push_back(m1D1->matrix1D[i]);
		}
		return t;
	}
public:
	//Check the vector tempVector is one element of another vector allSol
	//If another vector does NOT contain the vector, return 0.
	//Otherwise, return 1.
	int CheckRepeatResult(int n)
	{
		if(n==1)
		{
			return 0;
		}
		for(int i=1;i<n;i++)
		{
			if(this->tempVector==this->allSol[i])
			{
				return 1;
			}
		}
		return 0;
	}
};

//Class for declaration many different Banker class.
class Group
{
public:
	Banker curr;
	Banker next;
public:
	Group()
	{
		int safeState=0;
		int reqState=0;
		this->curr=Banker();
		this->next=Banker();
		this->curr.Input();
		this->curr.InitAll();
		this->next=this->curr;	
		
		//HW1
		cout<<"A1!!!"<<endl;
		cout<<"A1!!!"<<endl;
		safeState=this->curr.SafeAlgorithm();
		
		//backup the next state to curr state
		//since the curr state was modified 
		//in method call SafeAlgorithm.
		this->curr=this->next;
		
		//HW2
		cout<<"A2!!!"<<endl;
		cout<<"A2!!!"<<endl;
		reqState=this->next.TryRequest((safeState==1)?1:0);
		//reqState==0 iff the request was met then the deadlock will occur.
		if(reqState==0)
		{
			//backup to original state.
			this->next=this->curr;
		}
		
		//HW3
		cout<<"A3!!!"<<endl;
		cout<<"A3!!!"<<endl;
		this->curr.PermutationAll();
	}
};

int main()
{
	Group *bank=new Group();
	return 0;
}
