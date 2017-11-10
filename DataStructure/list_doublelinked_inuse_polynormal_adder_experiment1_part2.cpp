#include<iostream>
#include<algorithm>
using namespace std;
#define INF 0x7fffffff
struct alist
{
	int data,wei;//wei*x^(data)
	alist *forward,*next;
	alist(int data,int wei):next(NULL),forward(NULL),data(data),wei(wei){}
	alist():next(NULL),forward(NULL),data(INF),wei(INF){}
};

alist *finddata(alist *root,int data,int base=-1)
{
	if(root->next==NULL) return root;
	alist *now=root;
	if(base==1)
	{
		//if(now->next->data > data) return now;
		while(now->next!=NULL&&now->next->data < data) {if(now->next==NULL) break;else now=now->next;}
		//if(now->next==NULL) return now;
		//else return now->forward;
		return now;
	}
	else
	{
		while(now->next!=NULL&&now->next->data > data) {if(now->next==NULL) break;else now=now->next;}
		return now;
	}
	return now;
}

void insertdata(alist *root,int data,int wei,int base=-1)
{
	alist *res=finddata(root,data,base);
	if(res->next==NULL||res->next->data!=data)
	{
		if(res->next==NULL)
		{
			alist *asd=new alist;
			asd->data=data,asd->wei=wei,asd->forward=res,asd->next=NULL;
			res->next=asd;
		}
		else 
		{
			alist *asd=new alist;
			asd->data=data,asd->wei=wei,asd->forward=res,asd->next=res->next;
			res->next->forward=asd,res->next=asd;
		}
	}
	else
	{
		res->next->wei+=wei;
	}
	return ;
}
void printres(alist *root)
{
	alist *now=root->next;
	while(now!=NULL)
	{
		if(now->wei!=0)  cout<<"[ "<<now->wei<<" "<<now->data<<" ]"<<"   ";
		now=now->next;
	}
	cout<<endl;
	return;
}
alist *root=new alist;
void exp2_add(int a[],int n)
{
	for(int i=0;i<n;i+=2)
	{
		insertdata(root,a[i+1],a[i]);
	}
}
int as[]={-1,17,2,20,5,9,-7,7,10,4,22,2,-15,0,16,5,0,-1};
int ar[]={2,19,7,7,3,17,4,4,15,10,-10,5,13,2,-7,0,8,-8};
int at[]={-1,17,2,23,22,2,6,8,-4,7,-18,0,1,5,21,4,0,-1};
int ax[]={23,4,-4,5,12,7,15,10,3,17};
int main()
{
	exp2_add(as,18);
	exp2_add(ar,18);
	exp2_add(at,18);
	exp2_add(ax,10);
	printres(root);
	system("pause");
	return 0;
}