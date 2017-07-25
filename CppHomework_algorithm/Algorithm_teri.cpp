#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<time.h>
#include<math.h>
#include<random>
#define ll long long

const static int types[7][50][50]=
{
	// 棒型方块
			{ 
				{ 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 }, 
				{ 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 },
				{ 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 } 
			},
			// s型方块
			{ 
				{ 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
				{ 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
				{ 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 } 
			},
			// z型方块
			{ 
				{ 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
				{ 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
				{ 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 } },
			// 右l型方块
			{
				{ 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 }, 
				{ 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
				{ 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
			// 田型方块
			{ 
				{ 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
				{ 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
			// 左l型方块
			{
				{ 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
				{ 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
			// t型方块
			{ 
				{ 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
				{ 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
				{ 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0 } 
			} 
};
class terist
{
public:
	terist();
	void init();
	void resetgraph();
	std::string refreshgraph();//"GG":Failed,"Next":OK,Next
	bool CollectionDetectior(int x,int y, int kind,int  shape);
	void rotate();
	void left();
	void right();
	void down();
	void clearLines();
	void addnewitems(int x,int y,int kind,int shape);
private:
	ll score;
	int nextt;
	int nextb;
	int x,y;
	int rotatestate;//shape=4
	int teritype;//kinds=7
	bool pause;
	int maps[25][15];
};

terist::terist()
{
	resetgraph();
	pause=false;
	score=0;
}

void terist::resetgraph()
{
	for(int i=0;i<23;i++)
	{
		for(int j=0;j<13;j++)
		{
			maps[i][j]=0;
		}
	}
	// draw walls
	for (int i = 0; i < 12; i++) {//right-1
		maps[21][i] = 2;
	}
	for (int j = 0; j < 22; j++) {//lower-1
		maps[j][11] = 2;
		maps[j][0] = 2;
	}
	return;
}

std::string terist::refreshgraph()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> d(0,6),shape(0,3);
	teritype = d(gen);
	rotatestate = shape(gen);
	x=4;
	y=0;
	if(CollectionDetectior(x,y,teritype,rotatestate))
	{
		//std::cout<<"GG"<<std::endl;
		return "GG";
		resetgraph();
		score=0;
	}
	else
	{
		return "Next";
	}
}

bool terist::CollectionDetectior(int x,int y, int kind,int rotateshape)
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if((types[kind][rotateshape][i*4+j]==1 && maps[y+i][x+j+1]==1)||(types[kind][rotateshape][i*4+j]==1 && maps[y+i][x+j+1]==2))
			{
				return true;
			}
		}
	}
	return false;
}

void terist::rotate()
{
	int tmp=rotatestate;
	rotatestate = (rotatestate+1)%4;
	if(pause||CollectionDetectior(x,y,teritype,rotatestate))
	{
		rotatestate = tmp; 
	}
	return;
}

void terist::left()
{
	if(!(pause || CollectionDetectior(x-1,y,teritype,rotatestate)))
	{
		x-=1;
	}
	return;
}

void terist::right()
{
	if(!(pause || CollectionDetectior(x+1,y,teritype,rotatestate)))
	{
		x++;
	}
	return;
}

void terist::down()
{
	if(!(pause || CollectionDetectior(x,y+1,teritype,rotatestate)))
	{
		y++;
	}
	return;
}

void terist::clearLines()
{
	int del=0,from=0;
	for(int i=0;i<22;i++)
	{
		from=0;
		for(int j=0;j<12;j++)
		{
			if(maps[i][j]==1)
			{
				from+=1;
				if(from==10)
				{
					del+=1;
					for(int t=i;t>0;t--)
					{
						for(int k=1;k<11;k++)
						{
							maps[t][k]=maps[t-1][k];
						}
					}
				}
			}
		}
	}
	score+=(int)(del*del*10);
	return;
}

void terist::addnewitems(int x,int y,int kind,int shape)
{
	for(int i=0,from=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(maps[y+i][x+1+j]==0)
			{
				maps[y+i][x+1+j] = types[kind][shape][from];
			}
		}
		from+=1;
	}
	return;
}
