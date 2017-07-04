#include<cstring>
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<map>
using namespace std;
typedef std::pair<int,int> pii;
typedef vector<int> vi;
#define StoragePath "D:\\Airplane Controller\\data\\pointsee.dat"
struct pointse
{
	double x,y,z;
	int stairnear;
	pointse(){}
	pointse(double x,double y,double z,int stairnear):x(x),y(y),z(z),stairnear(stairnear){}
	bool operator <(pointse p) const
	{
		return x!=p.x? x>p.x:(y!=p.y ? y>p.y:(z!=p.z ? z>p.z:1));
	}
};
struct stpoint
{
	pointse from,to;
	stpoint(){}
	stpoint(pointse from,pointse to) : from(from),to(to){}
};
double distancing(pointse p1,pointse p2)
{
	return (double)sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)+(p1.z-p2.z)*(p1.z-p2.z));
}
class buildin
{
public:
	int idcnt_point[20];
	int idcnt_stairs;
	int idcnt_specialpoint;
	double x0,y0,z0;
	double degree_r,degree_z;
	double compressdeg;
	pointse *head;
	bool hashead;
	void convert00(double degr,double degz,double comdeg,double newx0,double newy0,double newz0);
	bool addpoint(double x,double y,double z,int index,int layer);
	bool addstair(double x1,double y1,double z1,double x0,double y0,double z0,int idst);
	double bfs(double x0,double y0,double z0,double desx,double desy,double desz);
	pointse doubletopoint(double x,double y,double z);
	vi databack();
	map<pointse,int> mps;
	buildin(double xx,double yy,double zz,int index){
		pointse*header=new pointse(xx,yy,zz,index);
		head=header;
		degree_r=0;
		degree_z=0;
		compressdeg=0;
		x0=xx;
		y0=yy;
		z0=zz;
		hashead=true;
		mps.clear();
		mps[pointse(xx,yy,zz,0)]=1;
		memset(idcnt_point,0,sizeof idcnt_point);
		idcnt_stairs=0;
		idcnt_specialpoint=0;
		memset(maxizlayer,0,sizeof maxizlayer);
		memset(minizlayer,0x3f,sizeof minizlayer);
	}
	buildin()
	{
		head=NULL;
		degree_r=0;
		degree_z=0;
		compressdeg=0;
		x0=0;
		y0=0;
		z0=0;
		hashead=false;
		mps.clear();
		memset(idcnt_point,0,sizeof idcnt_point);
		idcnt_stairs=0;
		idcnt_specialpoint=0;
		memset(maxizlayer,0,sizeof maxizlayer);
		memset(minizlayer,0x3f,sizeof minizlayer);
	}
private:
	pointse plain[10000];
	stpoint stairs[100];
	pointse layers[20];
	double maxizlayer[11];
	double minizlayer[11];
	int vis[10000];
};
void buildin::convert00(double degr,double degz,double comdeg,double newx0,double newy0,double newz0)
{
	x0=newx0-x0;
	y0=newy0-y0;
	z0=newz0-z0;
	//Î´Íê
}
bool buildin::addpoint(double x,double y,double z,int index,int layer)
{
	if(layer==1&&!hashead)
	{
		head=new pointse(x,y,z,index);
		hashead=true;
	}
	int idcnt=layer*1000+idcnt_point[layer];
	if(idcnt_point[layer]==0)
	{
		layers[layer]=pointse(x,y,z,index);
	}
	plain[idcnt]=pointse(x,y,z,index);
	idcnt_point[layer]++;
	mps[pointse(x,y,z,index)]=idcnt;
	maxizlayer[layer]=max(maxizlayer[layer],z);
	minizlayer[layer]=min(minizlayer[layer],z);
	cout<<"Suc(1000):pointse Add Successfully!"<<endl;
	return true;
}
bool buildin::addstair(double x1,double y1,double z1,double x0,double y0,double z0,int idst)
{
	idcnt_stairs=idst;
	if(mps[pointse(x1,y1,z1,idst)]==0||mps[pointse(x0,y0,z0,idst)]==0)
	{
		cout<<"Error(1001):Add Stairs Failed:Please Check the Real Point Coordinate!"<<endl;
		return false;
	}
	else
	{
		stairs[idcnt_stairs]=stpoint(pointse(x0,y0,z0,mps[pointse(x0,y0,z0,idst)]),pointse(x1,y1,z1,mps[pointse(x1,y1,z1,idst)]));
		cout<<"Suc(1001):Stairs add successfully! id= "<<idcnt_stairs<<endl;
	}
	return true;
}
pointse buildin::doubletopoint(double x,double y,double z)
{
	int minn=0x3f3f3f3f,maxx=0;
	for(int i=1;i<=10;i++)
	{
		if(minizlayer[i]<=z)
		{
			minn=min(minn,i);
		}
		if(maxizlayer[i]>=z)
		{
			maxx=max(maxx,i);
		}
	}
	double dis=0x3f3f3f3f;
	pointse nearest;
	for(int i=minn;i<=maxx;i++)
	{
		for(int j=1;j<=idcnt_point[i];j++)
		{
			double dist=distancing(pointse(x,y,z,0),plain[j+i*1000]);
			if(dis>dist)
			{
				nearest=plain[j+1000*i];
				dis=dist;
			}
			else continue;
		}
	}
	if(dis>31.7)
	{
		cout<<"Warning(1002):The distancing between current point and the nearest point is above limit, please check it"<<endl;
	}
	return nearest;
}
double buildin::bfs(double x0,double y0,double z0,double desx,double desy,double desz)
{
	pointse from = doubletopoint(x0,y0,z0);
	pointse to = doubletopoint(desx,desy,desz);
	int fromid=mps[from];
	int toid=mps[to];
	queue<int> que;
	que.push(fromid);
	vis[fromid]=true;
	memset(vis,false,sizeof vis);
	while(!que.empty())
	{
		int cur=que.front();
		que.pop();
		if(cur==toid)
		{
			cout<<"Suc(1002):Find Destiny Successfully!"<<endl;
			return 1;
		}
		if(plain[cur].stairnear!=0)
		{
			pointse toto=stairs[plain[cur].stairnear].to;
			int nu=mps[toto];
			if(!vis[nu])
			{
				que.push(nu);
				vis[nu]=true;
			}
		}
		if(cur+1<idcnt_point[cur/1000]&&!vis[cur+1])
		{
			vis[cur+1]=true;
			que.push(cur+1);
		}
		if(!vis[cur-1])
		{
			que.push(cur-1);
			vis[cur-1]=true;
		}
	}
	return 0;
}
vi buildin::databack()
{

}
int main()
{
	int indexx;
	cout<<"Input O(0,0,0) index:"<<endl;
	cin>>indexx;
	buildin ccs(0.0,0.0,0.0,indexx);
	int n,num;
	double x,y,z;
	int index,layer;
	cout<<"Input the number of layers:"<<endl;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cout<<"Input the number of points in F"<<i<<endl;
		cin>>num;
		for(int j=1;j<=num;j++)
		{
			cout<<"Input the corrinate of points:x,y,z,index:"<<endl;
			cin>>x>>y>>z>>index;
			ccs.addpoint(x,y,z,index,i);
		}
	}
	int m,numm,idst;
	double x0,y0,z0,x1,y1,z1;
	cout<<"Input the number of stairs:"<<endl;
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		cout<<"Input the corrindates of twopoints:xyz0,xyz1,id of this stair:"<<endl;
		cin>>x0>>y0>>z0>>x1>>y1>>z1>>idst;
		ccs.addstair(x1,y1,z1,x0,y0,z0,idst);
	}
	cout<<"Input the origin and des of point:"<<endl;
	double xx,yy,zz,desx,desy,desz;
	while(cin>>xx>>yy>>zz>>desx>>desy>>desz)
	{
		bool res=(int)ccs.bfs(xx,yy,zz,desx,desy,desz);
		cout<<res<<endl;
	}
	return 0;
}