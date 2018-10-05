#include <windows.h>
#include <iostream>
#include <conio.h>
#define hang 20
#define lie 110
#define speed 50
using namespace std;
void forward(int direct);
void printgoal();
void food();
struct snake
{
	int flag; //��־��ʲô����
	int x,y; //����
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
	//�����һ����ʼ������˳���ڶ���
	for (int i = ncount-1; i >0; i--)
	{
		demsnake[i] = demsnake[i-1];
	}
	//�����λ����ʳ��
	if(headx==xfood && heady == yfood)
	{
		//ˢ��ʳ��
		food();
		addsnake();
		nfood++;
	}
		//������ͷ��λ��
	demsnake[0].x = headx;
	demsnake[0].y = heady;
	demsnake[1].flag = 0;
}
void mainthread()
{
	while(true)
	{
		//ˢ���ߵ���Ϣ
		Sleep(speed);
		forward(direct);
		drawsnake();
		printgoal();
	}
}
void food()//�������ʳ��
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
 void hide()
{
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO cci;
		GetConsoleCursorInfo(hOut, &cci);
		cci.bVisible = FALSE;
		SetConsoleCursorInfo(hOut, &cci);
}
 void printgoal()
 {
	 set_color(6);
	 gotoxy(0,hang+1);
	 cout<<"�÷�:"<<nfood;
	 gotoxy(0,hang+2);
	  cout<<"̰����";
	   gotoxy(0,hang+3);
	   cout<<"����"<<direct;
	    gotoxy(0,hang+4);
	   cout<<"�ٶ�"<<speed;
	   	 gotoxy(0,hang+5);
		 cout<<"@Ϊ��ͷ,#Ϊ����,%Ϊʳ��"<<speed;
 }
int main()
{
	demsnake[0].flag = 1;//��ͷ
	demsnake[0].x = 3;
	demsnake[0].y = 4;
	demsnake[1].flag = 0;
	demsnake[1].x = 3;
	demsnake[1].y = 3;
    map();
	food();
	hide();
	CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)thread,NULL,NULL,NULL);
	mainthread();
	return 0;
}