/*
  README:
  
  Administrator:RUIKANG
  number:1160300514
  Tel:86-18745142051
  
  User Help: press DOWN key to enter advance mode, else in the primary mode.
  
  Copyright 
  All rights reserved
  2017-7 RuiKang
  
  Catalog:
  begin
  
  Class bal(ball)
  Class rec(square)
  Class bgm(background settings)
  void setup()
  void draw(){flag=0,1,2,3; set bgm}
  void mousepressed()
  void mousereleased()
  void keypressed(){key=space(initilaize),down(enter advance mode)
  
  end
*/
import java.lang.*;
class bal//class ball
{
  int col;
  int rad;
  bal(int r)
  {
    col=(int)random(#000000, #FFFFFF);
    rad=r;
  }
  bal(int r,int colo)
  {
    rad=r;
    col=colo;
  }
  void play(int x,int y)
  {
    fill(col);
    ellipse(x, y, rad, rad);
  }
}
class rec//class square
{
  int col;
  int l,r;
  rec(int ll, int rr)
  {
    l=ll;
    r=rr;
    col=(int)random(#000000, #FFFFFF);
  }
  rec(int ll,int rr,int colo)
  {
    l=ll;
    r=rr;
    col=colo;
  }
  void play(int x,int y)
  {
    fill(col);
    rect(x,y,l,r);
  }
}
class bgm
{
  bal []ball = new bal[50];
  rec []reca = new rec[50];
  int flag=0;
  bgm(int[] coll,int[] colr,int[] li,int[] ri,int[] r,int n)
  {
    for(int i=0; i<n; i++)
    {
      ball[i] = new bal(r[i], colr[i]);
      reca[i] = new rec(li[i], ri[i], coll[i]);
    }
    flag=1;
  }
  bgm(int[] coll,int[] colr,int r,int l,int n)
  {
    for(int i=0;i<n;i++)
    {
      ball[i]=new bal(r, colr[i]);
      reca[i]=new rec(l,l, coll[i]);
    }
    flag=1;
  }
  bgm(int[] colr, int r, int n)
  {
    for(int i=0; i<n; i++)
    {
      ball[i]= new bal(r, colr[i]);
    }
    flag=2;
  }
  void play(int[] rcentrex, int[] rcentrey, int[] ecentrex, int[] ecentrey, int n)
  {
    if(flag==1)
    {
      for(int i=0; i<n; i++)
      {
        ball[i].play(ecentrex[i], ecentrey[i]);
        reca[i].play(rcentrex[i], rcentrey[i]);
      }
    }
    else
    {
      assert(true);
      return;
    }
    return ;
  }
  void play(int[] rcentrex, int[] rcentrey, int n)
  {
    for(int i=0; i<n; i++)
    {
      ball[i].play(rcentrex[i], rcentrey[i]);
    }
    return ;
  }
}
int [][] col = new int[20][20];//color of each object
int [][] occupy = new int[20][20];//occupy=1:ellipse,occupy=2:rect,occupy=0:null
int vectx,vecty;
int colOfObject;
int flag = 0;//flag=0:initial state,flag=1:press an object:ellipse,flag=2:rectpressed,flag=3:initial advanced state,flag=4:Not used;
bgm bmm;
int state = 0;
int []constructor1 = new int[50];
int []constructor2 = new int[50];
void setup()
{
  size(600,600);
  background(255);
}
void draw()
{
  rectMode(CENTER);
  ellipseMode(CENTER);
  smooth();
  background(255);
  
  if(flag==0)
  {
    for(int i=0; i<15; i++)
    {
      for(int j=0; j<14; j++)
      {
        col[i][j] = 0;
        occupy[i][j] = 0;
      }
    }
    for(int j=0; j<15; j++)
    {
      col[j][14] = 255-10*j;
      occupy[j][14] = 1;
    }
    for(int i=0; i<15; i++)
    {
      constructor2[i] = 255-10*i;
    }
    bmm=new bgm(constructor2,20,15);
    for (int i=0; i<15; i++)
    {
      constructor1[i] = 580;
      constructor2[i] = 20+40*i;
    }
    bmm.play(constructor2,constructor1,15);
  }
  else if (flag==1)
  {
    int rx = mouseX-vectx;
    int ry = mouseY-vecty;
    fill (colOfObject);
    ellipse (rx, ry, 20, 20);
  }
  else if (flag==2)
  {
    int rx = mouseX-vectx;
    int ry = mouseY-vecty;
    fill (colOfObject);
    rect (rx, ry+40, 20, 20);
  }
  else if (flag==3)
  {
    
  }
  for (int i=0; i<15; i++)
  {
    for (int j=0; j<15; j++)
    {
      fill (col[i][j]);
      if (occupy[i][j]==1)
      {
        ellipse (i*40+20, j*40+20, 20, 20);
      } 
      else if (occupy[i][j]==2)
      {
        rect (i*40+20, j*40+20, 20, 20);
      }
    }
  }
  for (int i=0; i<15; i++)
  {
    stroke(0);
    line(i*40, 0, i*40, 600);
    line(0, i*40, 600, i*40);
  }
}
void mousePressed ()
{
  int tmpx = mouseX;
  int tmpy = mouseY;
  int num = tmpx/40;
  int pos = tmpy/40;
  if (state==0)
  {
    if (occupy[num][pos]==0)
    {
      return;
    }
  }
  if (state==1)
  {
    if (occupy[num][pos]==0)
    {
      return;
    }
  }
  colOfObject = col[num][pos];
  if (pos==0)
  {
    flag = 2;
    vectx = tmpx-(num*40+20);
    vecty = tmpy-(pos*40-20);
  }
  else
  {
    flag = 1;
    vectx = tmpx-(num*40+20);
    vecty = tmpy-(pos*40+20);
  }
  return;
}
void mouseReleased ()
{
  int numx = mouseX/40;
  int numy = mouseY/40;
  //if (flag!=1&&flag!=4) return;
  if ((numy==0&&state==1) || numy==14)
  {
    flag = 4;
    colOfObject = 0;
    return ;
  }
  else
  {
    if(colOfObject!=0)
    {
      col[numx][numy] = colOfObject;
      occupy[numx][numy] = flag;
    }
    flag = 4;
    colOfObject = 0;
    return;
  }
}
void keyPressed ()
{
  //if(key==CODED)
    if (keyCode==32)
    {
      for(int i=0; i<15; i++)
      {
        for(int j=0; j<14; j++)
        {
          col[i][j] = 0;
          occupy[i][j] = 0;
        }
      }
      for (int j=0; j<15; j++)
      {
        col[j][14] = 255-10*j;
        occupy[j][14] = 1;
      }
    }
    else if (keyCode==DOWN)
    {
      state = 1;
      flag = 3;
      for (int i=0; i<15; i++)
      {
        for (int j=0; j<14; j++)
        {
          col[i][j] = 0;
          occupy[i][j] = 0;
        }
      }
      for (int j=0;j<15;j++)
      {
        occupy[j][14] = 1;
        occupy[j][0] = 2;
      }
      for (int i=0;i<15;i++)
      {
        constructor1[i] = (int)random(#000000, #FFFFFF);
        constructor2[i] = (int)random(#000000, #FFFFFF);
        bmm = new bgm(constructor1, constructor2, 20, 20, 15);
        col[i][0] = constructor1[i];
        col[i][14] = constructor2[i];
      }
    }
}