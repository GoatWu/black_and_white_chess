// chess_game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>

int w_num=2,b_num=2;
struct node
{
	int x,y;
	int chess;
}nd[8][8];

void init()
{
	initgraph(1280, 960, SHOWCONSOLE);
	setbkcolor(RGB(150,150,150));
	cleardevice();
	setlinecolor(BLACK);
	setlinestyle(0,4);
	int i,j;
	for(i=0;i<=7;i++)
	{
		line(100,100+100*i,800,100+100*i);
		line(100+100*i,100,100+100*i,800);
	}
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			nd[i][j].x=100+i*100;
			nd[i][j].y=100+j*100;
		}
	}
	setfillcolor(BLACK);
	fillcircle(400,400,30);
	fillcircle(500,500,30);
	nd[3][3].chess=1;
	nd[4][4].chess=1;
	setfillcolor(WHITE);
	fillcircle(400,500,30);
	fillcircle(500,400,30);
	nd[3][4].chess=-1;
	nd[4][3].chess=-1;

	settextstyle(30, 15, _T("Courier"));
	settextcolor(BLACK);
	outtextxy(900, 100, "black num: ");
	outtextxy(900, 200, "white num: ");
}

void show_score(int b,int w)
{
	char s1[3],s2[3];
	sprintf(s1,"%d",b);
	sprintf(s2,"%d",w);

	clearcircle(1100,100,50);
	outtextxy(1100, 100, s1);
	clearcircle(1100,200,50);
	outtextxy(1100, 200, s2);
}

void end_game()
{
	settextstyle(160, 80, _T("Courier"));
	settextcolor(RED);
	if(b_num>w_num) outtextxy(140, 200, "balck win!");
	else if(w_num>b_num) outtextxy(140, 200, "white win!");
	else outtextxy(140, 200, "break even!");
}

void set_color(int col,int a,int b)
{
	int x=(a-100)/100;
	int y=(b-100)/100;
	if(col==1)
	{
		setfillcolor(BLACK);
		fillcircle(a,b,30);
	}
	else if(col==-1)
	{
		setfillcolor(WHITE);
		fillcircle(a,b,30);
	}
	nd[x][y].chess=col;
}

int judge_point(int x,int y,int &a,int &b)
{
	double minn=1e9;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			double dis=sqrt((x-nd[i][j].x)*(x-nd[i][j].x)+(y-nd[i][j].y)*(y-nd[i][j].y));
			if(dis<minn)
			{
				a=nd[i][j].x;
				b=nd[i][j].y;
				minn=dis;
			}
		}
	}
	if(minn>30) return 0;
	return 1;
}

int judge_u(int flag,int x,int y)
{
	if(y==0||nd[x][y-1].chess==0||nd[x][y-1].chess==flag)
	{
		return 0;
	}
	int num=0;
	for(int i=y-1;i>=0;i--)
	{
		if(nd[x][i].chess==0) return 0;
		if(nd[x][i].chess==flag) return num;
		num++;
	}
	return 0;
}
int judge_d(int flag,int x,int y)
{
	if(y==7||nd[x][y+1].chess==0||nd[x][y+1].chess==flag)
	{
		return 0;
	}
	int num=0;
	for(int i=y+1;i<8;i++)
	{
		if(nd[x][i].chess==0) return 0;
		if(nd[x][i].chess==flag) return num;
		num++;
	}
	return 0;
}
int judge_l(int flag,int x,int y)
{
	if(x==0||nd[x-1][y].chess==0||nd[x-1][y].chess==flag)
	{
		return 0;
	}
	int num=0;
	for(int i=x-1;i>=0;i--)
	{
		if(nd[i][y].chess==0) return 0;
		if(nd[i][y].chess==flag) return num;
		num++;
	}
	return 0;
}
int judge_r(int flag,int x,int y)
{
	if(x==7||nd[x+1][y].chess==0||nd[x+1][y].chess==flag)
	{
		return 0;
	}
	int num=0;
	for(int i=x+1;i<8;i++)
	{
		if(nd[i][y].chess==0) return 0;
		if(nd[i][y].chess==flag) return num;
		num++;
	}
	return 0;
}

int judge_ul(int flag,int x,int y)
{
	if(x==0||y==0||nd[x-1][y-1].chess==0||nd[x-1][y-1].chess==flag)
	{
		return 0;
	}
	int num=0;
	for(int i=x-1,j=y-1;i>=0,j>=0;i--,j--)
	{
		if(nd[i][j].chess==0) return 0;
		if(nd[i][j].chess==flag) return num;
		num++;
	}
	return 0;
}
int judge_ur(int flag,int x,int y)
{
	if(x==7||y==0||nd[x+1][y-1].chess==0||nd[x+1][y-1].chess==flag)
	{
		return 0;
	}
	int num=0;
	for(int i=x+1,j=y-1;i<8,j>=0;i++,j--)
	{
		if(nd[i][j].chess==0) return 0;
		if(nd[i][j].chess==flag) return num;
		num++;
	}
	return 0;
}
int judge_dr(int flag,int x,int y)
{
	if(x==7||y==7||nd[x+1][y+1].chess==0||nd[x+1][y+1].chess==flag)
	{
		return 0;
	}
	int num=0;
	for(int i=x+1,j=y+1;i<8,j<8;i++,j++)
	{
		if(nd[i][j].chess==0) return 0;
		if(nd[i][j].chess==flag) return num;
		num++;
	}
	return 0;
}
int judge_dl(int flag,int x,int y)
{
	if(x==0||y==7||nd[x-1][y+1].chess==0||nd[x-1][y+1].chess==flag)
	{
		return 0;
	}
	int num=0;
	for(int i=x-1,j=y+1;i>=0,j<8;i--,j++)
	{
		if(nd[i][j].chess==0) return 0;
		if(nd[i][j].chess==flag) return num;
		num++;
	}
	return 0;
}

int judge(int flag,int x,int y,int a,int b)
{
	if(nd[x][y].chess) return 0;
	int k=judge_u(flag,x,y);
	int tmp=0,i,j;
	if(k)
	{
		if(flag==1) b_num+=k,w_num-=k;
		else b_num-=k,w_num+=k;
		tmp=1;
		for(i=b-100;k>0;i-=100,k-=1)
		{
			set_color(flag,a,i);
		}
	}
	k=judge_d(flag,x,y);
	if(k)
	{
		if(flag==1) b_num+=k,w_num-=k;
		else b_num-=k,w_num+=k;
		tmp=1;
		for(i=b+100;k>0;i+=100,k-=1)
		{
			set_color(flag,a,i);
		}
	}
	k=judge_l(flag,x,y);
	if(k)
	{
		if(flag==1) b_num+=k,w_num-=k;
		else b_num-=k,w_num+=k;
		tmp=1;
		for(i=a-100;k>0;i-=100,k-=1)
		{
			set_color(flag,i,b);
		}
	}
	k=judge_r(flag,x,y);
	if(k)
	{
		if(flag==1) b_num+=k,w_num-=k;
		else b_num-=k,w_num+=k;
		tmp=1;
		for(i=a+100;k>0;i+=100,k-=1)
		{
			set_color(flag,i,b);
		}
	}
	k=judge_ul(flag,x,y);
	if(k)
	{
		if(flag==1) b_num+=k,w_num-=k;
		else b_num-=k,w_num+=k;
		tmp=1;
		for(i=b-100,j=a-100;k>0;i-=100,j-=100,k-=1)
		{
			if(i==0||j==0) break;
			set_color(flag,j,i);
		}
	}
	k=judge_ur(flag,x,y);
	if(k)
	{
		if(flag==1) b_num+=k,w_num-=k;
		else b_num-=k,w_num+=k;
		tmp=1;
		for(i=b-100,j=a+100;k>0;i-=100,j+=100,k-=1)
		{
			if(i==0) break;
			set_color(flag,j,i);
		}
	}
	k=judge_dr(flag,x,y);
	if(k)
	{
		if(flag==1) b_num+=k,w_num-=k;
		else b_num-=k,w_num+=k;
		tmp=1;
		for(i=b+100,j=a+100;k>0;i+=100,j+=100,k-=1)
		{
			set_color(flag,j,i);
		}
	}
	k=judge_dl(flag,x,y);
	if(k)
	{
		if(flag==1) b_num+=k,w_num-=k;
		else b_num-=k,w_num+=k;
		tmp=1;
		for(i=b+100,j=a-100;k>0;i+=100,j-=100,k-=1)
		{
			set_color(flag,j,i);
		}
	}
	return tmp;
}


int main()
{
	init();
	int flag=1,i;

	while(flag)
	{
		show_score(b_num,w_num);
		if(b_num+w_num==64||b_num==0||w_num==0) break;
		MOUSEMSG m;
		m=GetMouseMsg();
		if(m.uMsg==WM_LBUTTONDOWN)
		{
			int a=0,b=0;
			if(judge_point(m.x,m.y,a,b))
			{
				int x=(a-100)/100;
				int y=(b-100)/100;
				if(judge(flag,x,y,a,b))
				{
					set_color(flag,a,b);
					if(flag==1) b_num+=1;
					else w_num+=1;
					flag*=-1;
				}
			}
		}
	}

	end_game();
	while(233){}
	closegraph();
	return 0;
}

