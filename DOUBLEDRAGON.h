#ifndef __DOUBLEDRAGON_H__
#define __DOUBLEDRAGON_H__

#include<stdio.h>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <process.h>
#include<windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;


#define Max 99		//����max

#define	up 72      
#define	down 80
#define left 75
#define	right 77
#define	w 119    
#define	s 115
#define a 97
#define	d 100          //�궨���˶�ASCII��

/******************���½ṹ������******************/
typedef struct pointxy
{
	int x;
	int y;
}pointxy; //����������������pointxy

struct Player
{
	int lenth;			//����
	pointxy xy[Max];	//��󳤶�
	char position;		//��Ƿ���
	int speed;			//�ٶ�
	int grade;			//����
}snake,dragon;        //������


struct Beads
{
	pointxy Beadsxy;		//�鱦����
	int symbol;		//�鱦���ڱ�־
}Beads;//�鱦

enum positon { sright, sleft, sup, sdown, pause }; //�����ж�ö��

/******************���²��ֺ�������******************/

void Cover()
{
	setbkcolor(RGB(25, 20, 20));
	int i = 0;
	char name[] = "˫�� Ϸ��";
	char choice[2][30] = { "���������ʼ��Ϸ", "Bilibili@���ƹ�Niko" };


	Sleep(800);  //800ms������
	settextstyle(100, 0, "�����п�");
	settextcolor(COLORREF RGB(250, 5, 60));
	outtextxy(280, 125, name);    //����-˫��Ϸ��-�����
	settextcolor(COLORREF RGB(50, 150, 100));
	settextstyle(19, 0, "����");
	outtextxy(640, 250, choice[1]);    //����-���ƹ�Niko-ԭ��ɫ
	setlinecolor(COLORREF RGB(255, 0, 50));
	rectangle(70, 90, 900, 500);   //�߿�
	settextstyle(25, 0, "����");
	do {
		settextcolor(COLORREF RGB(144, 236, 194));
		outtextxy(380, 325, choice[0]);
		Sleep(800);
		settextcolor(COLORREF RGB(i, 0, 0));
		outtextxy(380, 325, choice[0]);
		Sleep(800);
		i += 30;
	} while (!_kbhit());       //���������ʼ��Ϸ-ֻ�а����Ż�����ѭ��
	_getch();

}
//OKOKOKOKOKOK  ��ʾ���漰��������

void KeyCommunity()
{
	char key = _getch();

	switch (key)
	{
	case up:
		//ʵ���ߵ��ƶ��߼��ж�,�������෴�ķ����ƶ�
		if (snake.position != sdown)
			snake.position = sup;
		break;
	case down:
		if (snake.position != sup)
			snake.position = sdown;
		break;
	case left:
		if (snake.position != sright)
			snake.position = sleft;
		break;
	case right:
		if (snake.position != sleft)
			snake.position = sright;
		break;

	case w:
		//ʵ�������ƶ��߼��ж�,�������෴�ķ����ƶ�
		if (dragon.position != sdown)
			dragon.position = sup;
		break;
	case s:
		if (dragon.position != sup)
			dragon.position = sdown;
		break;
	case a:
		if (dragon.position != sright)
			dragon.position = sleft;
		break;
	case d:
		if (dragon.position != sleft)
			dragon.position = sright;
		break;

	case 'p':
		snake.position = pause;
		dragon.position = pause;
		break;
	}
}
//OKOKOKOKOKOK  ���߰�����������

void Createplayers()
{
	dragon.xy[2].x = 50;
	dragon.xy[2].y = 100;

	dragon.xy[1].x = 60;
	dragon.xy[1].y = 100;

	dragon.xy[0].x = 70;
	dragon.xy[0].y = 100;    //dragon��ʼλ�����Ͻ�

	dragon.lenth = 3;
	dragon.position = sright;

	snake.xy[2].x = 590;
	snake.xy[2].y = 540;

	snake.xy[1].x = 580;
	snake.xy[1].y = 540;

	snake.xy[0].x = 570;
	snake.xy[0].y = 540;    //�߳�ʼ�����½�

	snake.lenth = 3;
	snake.position = sleft;


	Beads.symbol = 0;

}
//��ʼ��������

void Explanation()
{
	char snake_grade[] = "�ߵõ�������";
	char dragon_grade[] = "���õ�������";
	char grade1[100];  char grade2[100];
	char exp[7][25] = { "�淨˵��:", "1.�ֱ���wasd����������", "���ı䷽��", "2.��p����ͣ,������������","3.���߻�ײ���о�ϲ","4.����ʱ�����ƣ������","Խ��Խ�죬ף�����" };
	settextstyle(22, 0, "����");
	setlinecolor(COLORREF RGB(150, 3, 125));
	rectangle(620, 90, 900, 560);
	settextcolor(COLORREF RGB(255, 215, 15));  //���ɫ

	sprintf(grade1, "%d", snake.grade);
	sprintf(grade2, "%d", dragon.grade);

	outtextxy(630, 100, snake_grade);
	outtextxy(750, 100, grade1);    //��ʾ�ߵĵ÷�
	outtextxy(630, 120, dragon_grade);
	outtextxy(750, 120, grade2);   //��ʾ���ĵ÷�
	outtextxy(630, 300, exp[0]);
	outtextxy(630, 325, exp[1]);
	outtextxy(630, 350, exp[2]);
	outtextxy(630, 375, exp[3]);
	outtextxy(630, 400, exp[4]);
	outtextxy(630, 425, exp[5]);
	outtextxy(630, 450, exp[6]);
}
//�Ҳ���Ϣ��,�ֻ���˸��

void CreateBeads()
{
	int i, j, x, y;
	srand((unsigned int)time(NULL));  //�������ֵ
	x = rand() % 54 + 6;	//��ʼ���鱦����,ҪΪ10�ı���,�����޷�����
	y = rand() % 45 + 10;
	Beads.Beadsxy.x = x * 10;
	Beads.Beadsxy.y = y * 10;
	Beads.symbol = 1;

	for (i = 0; i < snake.lenth; i++)
	{
		if (Beads.Beadsxy.x == snake.xy[i].x && Beads.Beadsxy.y == snake.xy[i].y)
		{
			x = rand() % 40 + 10;
			y = rand() % 50 + 10;
			Beads.Beadsxy.x = x * 10;
			Beads.Beadsxy.y = y * 10;
		}
	}
	for (j = 0; j < dragon.lenth; j++)
	{
		if ((Beads.Beadsxy.x == dragon.xy[j].x && Beads.Beadsxy.y == dragon.xy[j].y))
		{
			x = rand() % 40 + 10;
			y = rand() % 50 + 10;
			Beads.Beadsxy.x = x * 10;
			Beads.Beadsxy.y = y * 10;
		}
	}
	//�鱦�����������ص�������о���������һ���鱦
}
//��ʼ���������鱦

void DrawBeads()
{
	setfillcolor(COLORREF RGB(255, 192, 203));
	solidrectangle(Beads.Beadsxy.x, Beads.Beadsxy.y, Beads.Beadsxy.x + 10, Beads.Beadsxy.y + 10);
}
//OKOKOKOKOKOK  �����鱦

void Eatbeads()
{
	if (snake.xy[0].x == Beads.Beadsxy.x && snake.xy[0].y == Beads.Beadsxy.y)
	{
		snake.lenth++;
		snake.grade++;
		Beads.symbol = 0;
		snake.speed -= 3;
	}
	if (dragon.xy[0].x == Beads.Beadsxy.x && dragon.xy[0].y == Beads.Beadsxy.y)
	{
		dragon.lenth++;
		dragon.grade++;
		Beads.symbol = 0;
		dragon.speed -= 3;
	}

}
//������

#endif 