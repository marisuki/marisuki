#include<iostream>
#include<algorithm>
using namespace std;
template<a>
struct alist
{
	int data;
	alist *next,*forward;
	alist(int data):next(NULL),forward(NULL),data(data){}
	alist():next(NULL),forward(NULL),data(0){}
};

alist *finddata(alist *root,int data,int base=1)
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


void insertdata(alist *root,int data,int base)
{
	alist *res=finddata(root,data,base);
	if(res->next==NULL)
	{
		alist *asd=new alist;
		asd->data=data,asd->forward=res,asd->next=NULL;
		res->next=asd;
	}
	else 
	{
		alist *asd=new alist;
		asd->data=data,asd->forward=res,asd->next=res->next;
		res->next->forward=asd,res->next=asd;
	}
	return ;
}

void findele(alist *root,int data,int base=1)
{
	alist *res=finddata(root,data,base);
	//cout<<res->data<<endl;
	if(res->data!=data&&res->next->data!=data)
	{
		cout<<"NO ELE FOUND"<<endl;
	}
	else
	{
		cout<<res<<' '<<data<<endl;
	}
}

void deleele(alist *root, int data,int base)
{
	alist *res=finddata(root,data,base);
	//if(base==1)
	{
		if(res->next==NULL||res->next->data!=data)
		{
			cout<<"NO ELE FOUND, DELETE FAILED"<<endl;
		}
		else
		{
			alist *after=res->next->next;
			delete(res->next);
			res->next=after,after->forward=res;
			alist *now=root->next;
			cout<<"DELETE SUCCEED, AFTER DELETED:"<<endl;
			while(now!=NULL)
			{
				cout<<now->data<<endl;
				now=now->next;
			}
		}
	}
}
void printele(alist *root)
{
	alist *now=root->next;
	while(now!=NULL)
	{
		cout<<now->data<<endl;
		now=now->next;
	}
}
int staticlength(alist *root)
{
	alist *now=root->next;
	int cnt=0;
	while(now!=NULL)
	{
		cnt++;
		now=now->next;
	}
	return cnt;
}
void exper1_func(int a[],int n,int base=1)
{
	alist *root=new alist;
	root->data=0,root->forward=root,root->next=NULL;
	for(int i=0;i<n;i++)
	{
		insertdata(root,a[i],base);
	}
	printele(root);
	cout<<"length= "<<staticlength(root)<<endl;
	findele(root,11,base);
	insertdata(root,14,base);
	printele(root);
	cout<<"length= "<<staticlength(root)<<endl;
	deleele(root,10,base);
	findele(root,10,base);
	return;
}

int sa[]={10,9,5,6,33,13,31,34,31,3843,23,-3,8};

int main()
{
	exper1_func(sa,13);
	system("pause");
	return 0;
}