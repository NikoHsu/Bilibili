#include <stdio.h>
#include "DOUBLEDRAGON.h"

/******************Դ���� ��������******************/
void CreateMap();			//��ʼ����ͼ******
void Drawplayers();			//����*****
void Movement();			//�ƶ�*****
void Snakewin();
void Dragonwin();
void Collision();			//ײǽ******
void Action();              //���г���**********

int main()
{
	PlaySound(TEXT("D:\\dragonbgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);   //BGM
	Action();
	return 0;

}   //��������ˢ��ÿһ���������

void Action()
{
	initgraph(1000, 600);
	Cover();				//���ɷ��溯��
	snake.speed = 100, dragon.speed = 100;
	snake.grade = 0, dragon.grade = 0;
	setbkcolor(RGB(190, 150, 150));   //RBG set blackcolor
	cleardevice();              // ����
	Createplayers();             //��ʼ����
	while (1)
	{
		cleardevice();		//ˢ���ߵ�·��
		CreateMap();
		Explanation();
		Drawplayers();
		DrawBeads();
		Movement();
		if (Beads.symbol == 0)
		{
			CreateBeads();
		}
		Sleep((dragon.speed + snake.speed));			//���ֵ��Խ��ԽС,����Խ��Խ��
		Collision();
		Eatbeads();
	}

	_getch();   //�����Ժ���������ĳ���ַ�ʱ���Զ���ȡ������س�
	closegraph();
}
//����������ͷ��ʼ

void Drawplayers()
{
	int i, j;  //�β�
	for (i = 0; i < snake.lenth; i++)
	{
		setlinecolor(COLORREF RGB(250, 250, 250));  //color of snakeline
		setfillcolor(COLORREF RGB(250, 5, 170));   //color of snake
		fillrectangle(snake.xy[i].x, snake.xy[i].y, snake.xy[i].x + 10, snake.xy[i].y + 10);  //fill in the color of the snake
	}
	/******************���߷ָ�******************/
	for (j = 0; j < dragon.lenth; j++)
	{
		setlinecolor(COLORREF RGB(250, 250, 5));  //color of dragonline
		setfillcolor(COLORREF RGB(250, 5, 10));   //color of dragon
		fillrectangle(dragon.xy[j].x, dragon.xy[j].y, dragon.xy[j].x + 10, dragon.xy[j].y + 10);  //fill in the color of the dragon
	}
}
//OKOKOKOKOKOK  ���ߵĻ���(��Movement�������ʵ���ƶ�)

void Movement()
{
	int i, j, m, n;

	for (i = snake.lenth - 1; i > 0; i--)
	{
		snake.xy[i].x = snake.xy[i - 1].x;
		snake.xy[i].y = snake.xy[i - 1].y;
	}
	for (j = dragon.lenth - 1; j > 0; j--)
	{
		dragon.xy[j].x = dragon.xy[j - 1].x;
		dragon.xy[j].y = dragon.xy[j - 1].y;
	}
	//���˵�һ������,��һ�������������ǰһ�ڵ�����

	switch (snake.position)
	{
	case sup:
		snake.xy[0].y -= 10;
		break;
	case sdown:
		snake.xy[0].y += 10;
		break;
	case sright:
		snake.xy[0].x += 10;
		break;
	case sleft:
		snake.xy[0].x -= 10;
		break;
	case pause:
		_getch();
		break;
	}
	
	switch (dragon.position)
	{
	case sup:
		dragon.xy[0].y -= 10;
		break;
	case sdown:
		dragon.xy[0].y += 10;
		break;
	case sright:
		dragon.xy[0].x += 10;
		break;
	case sleft:
		dragon.xy[0].x -= 10;
		break;
	case pause:
		_getch();
		break;   //?��ͣ�����
	}
	//ͷxy[0]�˶�����,���ݷ����־���ƶ�

	while (_kbhit())     //kbhit()��鵱ǰ�Ƿ��м������룬�����򷵻�һ����0ֵ�����򷵻�0
	{
		KeyCommunity();  //���̽�������
	}

	for (m = 2; m < snake.lenth; m++)
	{
		if (snake.xy[0].x == snake.xy[m].x && snake.xy[0].y == snake.xy[m].y)
			Dragonwin();
		else if (snake.xy[0].x == dragon.xy[m].x && snake.xy[0].y == dragon.xy[m].y)
			snake.lenth--, snake.grade --,dragon.lenth++, dragon.grade++;
	}

	for (n = 2; n < dragon.lenth; n++)
	{
		if (dragon.xy[0].x == dragon.xy[n].x && dragon.xy[0].y == dragon.xy[n].y)
			Snakewin();
		else if (dragon.xy[0].x == snake.xy[n].x && dragon.xy[0].y == snake.xy[n].y)
			dragon.lenth--, dragon.grade --,snake.lenth++, snake.grade++;
	}
	//��������ͷ�����������ʱ,ײ���Լ�����Ϸ����������������ײ���Է���������ȡ���Ⱥ͵÷�

}
//���ߵ��˶�

void Gameover()
{
	cleardevice();
	char choose;
	settextstyle(50, 0, "�����п�");
	settextcolor(COLORREF RGB(230, 35, 40));
	char End[] = "������֣�";
	char reburn[] = "��y�����¿�ʼ��Ϸ";
	outtextxy(100, 125, End);
	outtextxy(100, 175, reburn);
	_getch();
	choose = _getch();
	switch (choose)
	{
	case 'y': Action();  //���³���ģ�黯���Ǻܺã������,�Ͻ����ޣ�
		break;
	}
	_getch();  //���������˳���Ϸ
	exit(0);
}

void CreateMap()
{
	char name[] = "˫��Ϸ��";
	settextstyle(40, 0, "�����п�");
	settextcolor(COLORREF RGB(230, 5, 10));
	outtextxy(250, 50, name);

	setlinecolor(COLORREF RGB(250, 0, 0));    //��ͼ������ɫ
	rectangle(40, 90, 610, 560);   //outȦ�����Ͻ�xy�����½�xy
	rectangle(50, 100, 600, 550);  //inȦ��ͬ  
}
//OKOKOKOKOKOK  �滭��ͼ����ͼ���ݺ�Collisionײǽ������ϣ�������鱦�������

void Snakewin()
{
	settextstyle(28, 0, "����");
	char end[] = "�ⳡ������,";
	char end0[] = "��ȡ����ʤ����";

	settextstyle(25, 0, "����");
	char tips[] = "�����������";
	outtextxy(250, 200, end);
	outtextxy(240, 225, end0);
	outtextxy(250, 300, tips);
	_getch();

	Gameover();
}

void Dragonwin()
{
	settextstyle(28, 0, "����");
	char end[] = "�ⳡ������,";
	char end0[] = "��ȡ����ʤ����";

	settextstyle(25, 0, "����");
	char tips[] = "�����������";
	outtextxy(250, 200, end);
	outtextxy(240, 225, end0);
	outtextxy(250, 300, tips);
	_getch();

	Gameover();
}

void Collision()
{
	if (snake.xy[0].x > 590 || snake.xy[0].x < 50 || snake.xy[0].y > 540 || snake.xy[0].y < 100)
	{
		Dragonwin();		
	}
	if (dragon.xy[0].x > 590 || dragon.xy[0].x < 50 || dragon.xy[0].y > 540 || dragon.xy[0].y < 100)
	{
		Snakewin();		//ײǽʱ,��Ϸ����
	}

}
//OKOKOKOKOKOK  �ж������Ƿ�ײǽ
