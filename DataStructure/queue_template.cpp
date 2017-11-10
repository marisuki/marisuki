#include<iostream>
#include<assert.h>
using namespace std;
template<class e> struct cell
{

	e data;
	cell *next,*forw;
	cell():data(0),next(NULL),forw(NULL){}
	cell(e data):data(data),next(NULL),forw(NULL){}
};

template<class e> 
class queues
{
public:
	cell<e> *root;
	e pop()
	{
		if(size==0) {cout<<"empty"<<endl;assert(0);return (e)0;}
		front->forw->next=NULL;
		size--;
		cell<e> *tmp=front;
		front=front->next;
		return tmp->data;
	}
	e fronts()
	{
		if(size==0) {cout<<"empty"<<endl;assert(0);return (e)0;}
		else return front->data;
	}
	void push(e data)
	{
		cell<e> *p=new cell<e>(data);
		if(size==0)
		{
			front=p;
			root->next=p;
			p->forw=root;
		}
		else
		{
			front->next=p;
			p->forw=front;
		}
		size++;
	}
	int size;
	queues()
	{
		root=new cell<e>();
		front=NULL;
		size=0;
	}
private:
	cell<e> *front;
};
queues<int> st;
int main()
{
	st.push(23);
	cout<<st.pop()<<endl;
	//cout<<st.pop()<<endl;
	st.push(123);
	cout<<st.fronts()<<endl;
	cout<<st.pop()<<endl;
	cout<<st.pop()<<endl;
	system("pause");
	return 0;
} 