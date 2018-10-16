#include <windows.h>
#include <iostream>
#include <conio.h>
#define hang 20
#define lie 110
#define speed 250
using namespace std;
void forward(int direct);
void printgoal();
void food();
struct snake
{
	int flag; //标志是什么部分
	int x,y; //坐标
    int n;
};
snake demsnake[100] = {0};
int xfood = 0,yfood = 0;
int ncount = 2;    
int direct = 2;
int nfood = 0;
void set_color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}
void gotoxy(int x,int y)
{
COORD c;
c.X=x;c.Y=y;
SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE),c);
}
void map()
{
	set_color(1);
	for (int i = 0; i < lie; i++)
		cout<<"*";
	cout<<endl;
	for (int i = 0; i < hang; i++)
	{
		gotoxy(0,i);
		cout<<"*";
		gotoxy(lie,i);
		cout<<"*";
	}
	gotoxy(0,hang);
		for (int i = 0; i < lie; i++)
		cout<<"*";
}
void delsnake()
{
	for (int i = 0; i < ncount; i++)
	{
		gotoxy(demsnake[i].x,demsnake[i].y);
		cout<<" ";
	}
}
void drawsnake()
{
	set_color(2);
	for (int i = 0; i < ncount; i++)
	{
		gotoxy(demsnake[i].x,demsnake[i].y);
		if(demsnake[i].flag == 1)
			cout<<"@";
		if(demsnake[i].flag == 0)
			cout<<"#";
	}
	gotoxy(lie,hang);
}
void addsnake()
{
	int newx=0,newy=0;
	if(demsnake[ncount-2].x == demsnake[ncount-1].x)
	{
		newy = demsnake[ncount-1].y ;
		newx = demsnake[ncount-1].x;
		if(newy - 1 == demsnake[ncount-2].y)
			newy++;
		else
			newy--;
	}
	if(demsnake[ncount-2].y == demsnake[ncount-1].y)
	{
		newy = demsnake[ncount-1].y ;
		newx = demsnake[ncount-1].x;
		if(newx - 1 == demsnake[ncount-2].x)
			newx++;
		else
			newx--;
	}
	demsnake[ncount].x = newx;
	demsnake[ncount].y = newy;
	demsnake[ncount].flag = 0;
	demsnake[ncount].n = ncount+1;
	ncount++;
}
void thread()
{
	while(true)
	{
		Sleep(1);
		//char ch = getch();
		switch (getch())
		{
		case 'w':
			direct = 8;
			break;
		case 's':
			direct = 2;
			break;
		case 'a':
			direct = 4;
				break;
		case 'd':
			direct = 6;
			break;
		default:
			break;
		}
	}
}
void forward(int direct)
{
	delsnake();
	int headx,heady;
	headx = demsnake[0].x ;
	heady = demsnake[0].y ;
	switch (direct )
	{
	case 2: heady++;break;
	case 8: heady--;break;
	case 4: headx--;break;
	case 6: headx++;break;
	}
	//从最后一个开始遍历到顺数第二个
	for (int i = ncount-1; i >0; i--)
	{
		demsnake[i] = demsnake[i-1];
	}

	//判断新位置是不是石头
	if (headx == lie || 0 == headx || heady==hang || heady ==0)
	{
		MessageBoxA(NULL, "Game over!", "", MB_OK);
		exit(0);
	 }

	//如果新位置是食物
	if(headx==xfood && heady == yfood)
	{
		//刷新食物
		food();
		addsnake();
		nfood++;
	}
		//设置蛇头新位置
	demsnake[0].x = headx;
	demsnake[0].y = heady;
	demsnake[1].flag = 0;
}
void mainthread()
{
	while(true)
	{
		//刷新蛇的信息
		Sleep(speed);
		forward(direct);
		drawsnake();
		printgoal();
	}
}
void food()//随机出现食物
{
	set_color(4);
	srand(rand());
	xfood = yfood= 0;
	while(xfood<=0 ||  xfood>=lie)
		xfood = (rand()%lie);
	while(yfood<=0 ||  yfood>=hang)
		yfood = (rand()%hang);
	gotoxy(xfood,yfood);
	cout<<"%";
}


void winSize(int lines_height, int cols_width)
{
	char cmd[100];
	if ((lines_height<1) || (lines_height>168) || (cols_width<13) || (cols_width>9001))
	{
		printf("\nWarnning from winSize(): 1<=lines_height<=168  13<=cols_width<=9001 \n");
		lines_height = 168;
		cols_width = 9001;
	}
	sprintf(cmd, "mode con cols=%d lines=%d", lines_height, cols_width);
	system(cmd);
}
 void printgoal()
 {
	 set_color(6);
	 gotoxy(0,hang+1);
	 cout<<"得分:"<<nfood;
	 gotoxy(0,hang+2);
	  cout<<"贪吃蛇";
	   gotoxy(0,hang+3);
	   cout<<"方向"<<direct;
	    gotoxy(0,hang+4);
	   cout<<"速度"<<speed;
	   	 gotoxy(0,hang+5);
		 cout<<"@为蛇头,#为蛇神,%为食物"<<speed;
 }
int main()
{
	demsnake[0].flag = 1;//蛇头
	demsnake[0].x = 3;
	demsnake[0].y = 4;
	demsnake[1].flag = 0;
	demsnake[1].x = 3;
	demsnake[1].y = 3;
    
	
	winSize(170, 200);
	map();
	food();
	CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)thread,NULL,NULL,NULL);
	mainthread();
	return 0;
}
