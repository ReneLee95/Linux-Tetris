#include <iostream>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include "tetris.h"
#include "map.h"
#include "block.h"

#define up 29
#define upL 23
#define right 28
#define rightL 22
#define down 27
#define downL 1
#define left 21
#define leftL 0

using namespace std;

void gotoxy(int x,int y);
int strike(int shape,int rotation, int x,int y);
int newbie(int shape,int rot, int x ,int y);
int newbiedraw(int shape,int rot, int x ,int y);
int newdel(int shape,int rot, int x ,int y);
int mainmenu();
struct strikedata{
        int n;
        int m;
};

int checkspeed = 0;
int servoscore = 0;
int speed = 500;
int totalscore;
int modecount = 0;
int key;
int curnum;
int menuNum;
char name;
int rotation = 1;
int newblock= 300;
vector<strikedata> strikevec;
vector<strikedata>::iterator iter;

int mapset(int shape, int rot, int x,int y)
{
	gotoxy(0,0);
	for(int i =0; i<MAIN_X; i++)
	{
		for(int j =0; j<MAIN_Y; j++)
		{
			if(j == 0 || j == MAIN_Y-1 || i == MAIN_X-1)
			{
				gotoxy(j+y,i+x);
				mapcpy[i][j] = 1;
				map[i][j] = 1;
			}
		}
	}
}

int idraw(int shape,int rot,int x,int y)
{
	int cpyx;
	int cpyy;
	cpyx = x;
	cpyy = y;
	for(int i =0; i<4; i++)
	{
		for(int j = 0; j<4; j++)
		{
			if(block[shape][rot][i][j]==1)
			{
				if (mapcpy[j+y][i+x]!=1||mapcpy[j+y][i+x]!=3)
				{
				gotoxy(i+x,j+y);
				mapcpy[j+y][i+x] = 2;
				gotoxy(100,100);
				}
			}
		}
	}
	gotoxy(0,0);
        for(int i =0; i<MAIN_X; i++)
        {
                for(int j =0; j<MAIN_Y; j++)
                {
                        if(mapcpy[i][j]==1)
                        {
                                printf("%c[43m",27);
                                printf("■");
                                printf("%c[49m",27);
                        }
			else if(mapcpy[i][j] == 2)
			{
				printf("%c[42m",27);
				printf("■");
				printf("%c[49m",27);
			}
			else if(mapcpy[i][j] == 3)
			{
				printf("%c[45m",27);
				printf("■");
				printf("%c[49m",27);
			}
			else if(mapcpy[i][j] == 4)
			{
                                printf("■");
			}
                        else
			{
				printf(" ");
			}
                }
                printf("\n");
        }
	gotoxy(100,100);
}

int init(int shape,int rot, int x ,int y)
{
	for(int i =0; i<MAIN_X; i++)
	{
		for(int j =0; j<MAIN_Y; j++)
		{
			if(mapcpy[i][j] == 4)
			{
				mapcpy[i][j] = 0;
			}
		}
	}
}

int strike(int shape, int rot,int x,int y)
{
	strikedata strikedata;
	for(int i =0; i<4; i++)
	{
		for(int j =0; j<4; j++)
		{
			if(block[shape][rot][i][j] = 1)
			{
				strikedata.n = i+x;
				strikedata.m = i+y;
				strikevec.push_back(strikedata);
			}
		}
	}
	for(int i =0; i<4; i++)
	{
		mapcpy[strikevec[i].n][strikevec[i].m] = 1;
	}
	for(int i =0; i<MAIN_X; i++)
	{
		for(int j =0; j<MAIN_Y; j++)
		{
			if(j != 0 && j!= MAIN_Y-1 && i != MAIN_X-1 && mapcpy[i][j] == 1) return 10;
			else return -2;
		}
	}
}

int test()
{
	gotoxy(50,50);
	for(int i =0; i<MAIN_X; i++)
	{
		for(int j =0; j<MAIN_Y; j++)
		{
			printf("%d ",mapcpy[i][j]);
		}
		printf("\n");
	}
}
int triger()
{
        if(digitalRead(up)==0)
        {
                digitalWrite(upL,1);
		delay(100);
        	digitalWrite(upL,0);
                return 1;
        }
        else if(digitalRead(left)==0)
        {
                digitalWrite(leftL,1);
		delay(100);
		digitalWrite(leftL,0);
                return 5;
        }
        else if(digitalRead(right)==0)
        {
                digitalWrite(rightL,1);
		delay(100);
		digitalWrite(rightL,0);
                return 2;
        }
        else if(digitalRead(down)==0)
        {
                digitalWrite(downL,1);
		delay(100);
		digitalWrite(downL,0);
               return 3;
        }
}

int newblockf()
{
	srand(time(NULL));
	int random = rand()%100;
	if(0<=random&&random<10) return 0;
	else if(10<=random&&random<20) return 1;
	else if(20<=random&&random<30) return 2;
	else if(30<=random&&random<40) return 3;
	else if(40<=random&&random<50) return 4;
	else if(50<=random&&random<60) return 5;
	else if(60<=random&&random<100) return 6;
	else return 100;
}

int gameover()
{
	char type;
	for(int i =0; i<MAIN_X; i++)
	{
		for(int j =0; j<MAIN_Y; j++)
		{
			if(i==0 && mapcpy[1][j]==3)
			{
				system("clear");
				gotoxy(30,30);
				printf("game over	totalscore : %d\n",totalscore + servoscore);
				std::cout<<"go out of this screan (menu : p)";
				std::cin>>type;
				if(type =='p')
				{
					mainmenu();
				}
				else return 0;
			}
		}
	}
}

int del(int shape, int rot,int x,int y)
{
	gotoxy(x,y);
	for(int i =0; i<4; i++)
	{
		for(int j =0; j<4; j++)
		{
                        if(block[shape][rot][i][j]==1)
                        {
				gotoxy(i+x,j+y);
				mapcpy[j+y][i+x] = 0;
                        }
		}
	}
	gotoxy(0,0);
	gotoxy(100,100);
}

int firstcheck(int shape, int rot, int x, int y)
{
	for(int i =0; i<4; i++)
	{
		for(int j =0; j<4; j++)
		{
			if(block[shape][rot][i][j]==1)
			{
				if(mapcpy[j+y][i+x]==1 || mapcpy[j+y][i+x]==3)
				{
					return 10;
				}
			}
		}
	}
}

int modeselect()
{
	system("clear");
	gotoxy(0,0);
	printf("%c[33m",27);
	printf("select mode\n");
	printf(" 1) easy \n");
	printf(" 2) expert \n");
	int select = 0;
	std::cin>>select;
	if(select == 1)
	{
		return 1;
	}
	else if(select == 2)
	{
		return 2;
	}
	else
	{
		printf("no search mode please choose mode");
		delay(1000);
		modeselect();
	}
}

int blocksave()
{
	for(int i =0; i<MAIN_X; i++)
	{
		for(int j =0; j<MAIN_Y; j++)
		{
			if(mapcpy[i][j] == 2)
			{
				mapcpy[i][j] = 3;
			}
		}
	}
}

int downblock(int num)
{
	for(int i =num; i>=0; i--)
	{
		for(int j =1; j<MAIN_Y-1; j++)
		{
			if(i==num)
			{
				mapcpy[i][j] = 0;
			}
			if(i!=num && mapcpy[i][j] ==3)
			{
				mapcpy[i+1][j] = 3;
				mapcpy[i][j] = 0;
			}
		}
	}
}

int linecheck()
{
	int line;
	int saveline;
	for(int i =0; i<MAIN_X; i++)
	{
		line = 0;
		for(int j =0; j<MAIN_Y; j++)
		{
			if(mapcpy[i][j] ==3)
			{
				line++;
			}
			if(line == MAIN_Y-2)
			{
				saveline = i;
				totalscore +=100;
				downblock(saveline);
				return 10;
			}
		}
	}
}
int blockchecking(int shape, int rot, int x, int y)
{
	int cut = 0;
	for(int i =0; i<4; i++)
	{
		for(int j =0; j<4; j++)
		{
			if(block[shape][rot][i][j] == 1)
			{
				if(mapcpy[j+y+1][i+x] == 1||mapcpy[j+y+1][i+x]==3||mapcpy[j+y][i+x]==1)
				{
					cut+=10;
				}
			}
		}
	}
	if(cut >=10) return 10;
	else return 0;
	gotoxy(100,100);
}
int mirror(int shape,int rot, int x, int y)
{
	gotoxy(25,16);
	printf("next block\n");
	gotoxy(25,17);
	printf("@@@@@@@@@@@@\n");
	gotoxy(25,18);
	printf("@	   @\n");
	gotoxy(25,19);
	printf("@	   @\n");
	gotoxy(25,20);
	printf("@	   @\n");
	gotoxy(25,21);
	printf("@	   @\n");
	gotoxy(25,22);
	printf("@	   @\n");
	gotoxy(25,23);
	printf("@@@@@@@@@@@@\n");
	for(int i =0; i<4; i++)
	{
		for(int j =0; j<4; j++)
		{
			if(block[shape][rot][i][j] ==1)
			{
				gotoxy(30+j,18+i);
				printf("■");
			}
			else
			{
				gotoxy(30+j,18+i);
				printf(" ");
			}
			gotoxy(100,100);
		}
	}
}

int score()
{
	gotoxy(25,5);
	printf("☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n");
	gotoxy(25,6);
	printf("☆ ★★★   ★★★    ★★★     ★★★   ★★★ ☆\n");
	gotoxy(25,7);
	printf("☆ ★     ★     ★   ★    ★ ★   ★   ☆\n");
	gotoxy(25,8);
	printf("☆ ★★★   ★     ★   ★    ★★★   ★★★ ☆\n");
	gotoxy(25,9);
	printf("☆   ★   ★     ★   ★    ★ ★   ★   ☆\n");
	gotoxy(25,10);
	printf("☆ ★★★   ★★★    ★★★     ★ ★   ★★★ ☆\n");
	gotoxy(25,11);
	printf("☆                                ☆\n");
	gotoxy(25,12);
	printf("☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n");
	gotoxy(25,13);
	printf("total : %d  speedUp : %d\n",totalscore+servoscore,checkspeed);
	if(totalscore/1000 >=1)
	{
		speed-=100;
		totalscore = 0;
		servoscore +=1000;
		checkspeed++;
	}
}

int gamemode()
{
	system("clear");
	int num = 0;
	printf("easy : 1 expert : 2\n");
	printf("select : ");
	std::cin>>num;
	if(num == 1)
	{
		modecount = 1;
		return 1;
	}
	else if (num == 2){
		modecount = 2;
		 return 2;
	}
	else
	{
		gamemode();
	}
}

int rightcheck(int shape, int rot, int x, int y)
{
	int count = 0;
	for(int i =0; i<4; i++)
	{
		for(int j =0; j<4; j++)
		{
			if(block[shape][rot][i][j]==1 && mapcpy[y+j][x]==1||mapcpy[y+j][x]==3)
			{
				count++;
			}
		}
	}
	if(count >=1) return 10;
}
int gamestart()
{
	int blockcount = 0;
	totalscore = 0;
	system("clear");
	gotoxy(0,0);
	system("clear");
	maps(1);
	int shape = 0;
	int count = 0;
	int center = 2;
	int countcpy = 0;
	int centercpy = 0;
	int rotationcpy = 0;
	int copyshape = 0;
	shape = newblockf();
	copyshape = newblockf();
	centercpy = center;
	countcpy = count;
	rotation = 0;
	rotationcpy = rotation;
	mapset(shape,rotation,center,count);
	gotoxy(0,0);
	while(1)
	{
	mapset(shape,rotation,center,count);
	gotoxy(100,100);
	if(center == MAIN_Y-1 || center == 0 || count==MAIN_X-1)
	{
		count = 0;
		center = 4;
		rotation = 0;
		shape = newblockf();
		mapset(shape,rotation,count,center);
	}
	int n = triger();
	switch(n){
		case 5:
			init(shape,rotation,center,count);
			center--;
			if(mapcpy[count][center]==1 || mapcpy[count][center] == 3)
			{
				del(shape,rotation,centercpy,countcpy);
				center++;
				center = centercpy;
				idraw(shape,rotation,center,count);
			}
			else
			{
				gotoxy(centercpy,countcpy);
				del(shape, rotation,centercpy,countcpy);
				gotoxy(count,center);
				idraw(shape, rotation,center,count);
				centercpy = center;
				countcpy = count;
			}
			break;
		case 1:
				init(shape,rotation,center,count);
				rotation++;
				rotation = rotation % 4;
				if(firstcheck(shape,rotation,centercpy,countcpy) == 10)
				{
					if(rotation!=0)
					{
						rotation --;
						rotation = rotation % 4;
					}
					else
					{
						rotation = 0;
					}
					break;
				}
				else
				{
				gotoxy(centercpy,countcpy);
				del(shape, rotationcpy,centercpy,countcpy);
				idraw(shape, rotation,center,count);
				centercpy = center;
				countcpy = count;
				rotationcpy = rotation;
				}
			break;
		case 3:
			init(shape,rotation,center,count);
			count++;
			if(map[count][center] == 1 || map[count][center] == 3)
			{
				del(shape,rotation,centercpy,countcpy);
				count--;
				idraw(shape,rotation,center,count);
				countcpy = count;
			}
			else
			{
				gotoxy(centercpy,countcpy);
				del(shape, rotation,centercpy,countcpy);
				idraw(shape, rotation,center,count);
				centercpy = center;
				countcpy = count;
			}
			break;
		case 2:
			init(shape,rotation,center,count);
			center++;
			if(blockchecking(shape,rotation,center,countcpy)==10)
			{
				del(shape,rotation,centercpy,countcpy);
				center--;
				idraw(shape,rotation,center,countcpy);
				centercpy = center;
			}
			else
			{
				gotoxy(centercpy,countcpy);
				del(shape, rotation,centercpy,countcpy);
				idraw(shape, rotation,center,count);
				centercpy = center;
				countcpy = count;
			}
			break;
			default:
				break;
			}
				count++;
				if(rightcheck(shape,rotation,centercpy,countcpy)==10)
				{
					center--;
					center = centercpy;
				}
				if(blockchecking(shape,rotation,centercpy,countcpy) == 10)
				{
					idraw(shape,rotation,centercpy,countcpy);
					blocksave();
					center = 4;
					centercpy = center;
					count = 0;
					countcpy = count;
        				shape = copyshape;
					copyshape = newblockf();
					gameover();
				}
				else
				{
				linecheck();
				score();
				if(modecount==1)
				{
					newbie(shape,rotation,center,count);
					mirror(copyshape,1,center,count);
				}
				del(shape,rotation,centercpy,countcpy);
                                idraw(shape,rotation,center,count);
		//		test();
				gotoxy(100,100);
				delay(speed);
				gotoxy(100,100);
   	                	centercpy = center;
                        	countcpy = count;
				gotoxy(centercpy,countcpy);
				}
		}
}

int newbiedraw(int shape,int rot,int x,int y)
{
        int cpyx;
        int cpyy;
        cpyx = x;
        cpyy = y;
        for(int i =0; i<4; i++)
        {
                for(int j = 0; j<4; j++)
                {
                        if(block[shape][rot][i][j]==1)
                       {
                                if (mapcpy[j+y][i+x]!=1||mapcpy[j+y][i+x]!=3)
                                {
                                gotoxy(i+x,j+y);
                                mapcpy[j+y][i+x] = 4;
                                gotoxy(100,100);
                                }
                        }
                }
	}
        gotoxy(100,100);
}

int newdel(int shape, int rot,int x,int y)
{
        gotoxy(x,y);
        for(int i =0; i<4; i++)
        {
                for(int j =0; j<4; j++)
                {
                        if(block[shape][rot][i][j]==1)
                        {
                                gotoxy(i+x,j+y);
                                mapcpy[j+y][i+x] = 0;
                        }
                }
        }
        gotoxy(0,0);
        gotoxy(100,100);
}

int newbie(int shape, int rot, int x, int y)
{
	int cpx = x;
	int cpy = y;
	int oriy = y;
	int cpshape = shape;
	int cprot = rot;
	gotoxy(x,y);
	while(1)
	{
		gotoxy(cpx,cpy);
		if(blockchecking(shape,rot,cpx,cpy)==10) break;
		else
		{
		for(int i =0; i<4; i++)
		{
			for(int j = 0; j<4; j++)
			{
				if(block[shape][rot][i][j] == 1)
				{
					gotoxy(i+cpx,j+cpy);
					mapcpy[j+cpy][i+cpx] = 0;
				}
			}
		}
		gotoxy(100,100);
		cpy++;
		for(int i =0; i<4; i++)
		{
			for(int j =0; j<4; j++)
			{
				if(block[shape][rot][i][j] == 1)
				{
					if(mapcpy[j+y][i+x]!=1 || mapcpy[j+y][i+x]!=3)
					{
						gotoxy(i+cpx,j+cpy);
						mapcpy[j+cpy][i+cpx] = 4;
						gotoxy(100,100);
					}
				}
			}
		}
		gotoxy(100,100);
		}
	}
}

int loading(int x,int y)
{
	printf("%c[32m",27);
	printf("			===========================================\n");
	printf("			   @     @@@     @      @    @         @@@\n");
	printf("			   @    @   @   @ @          @         @ @\n");
	printf("			   @    @   @  @   @    @  @@@    @@@  @@@\n");
	printf("			   @    @   @ @@@@@@@   @  @ @    @ @    @\n");
	printf("			   @@@@  @@@ @       @  @  @@@    @ @  @@@\n");
	printf("			===========================================\n");
	delay(300);
	gamemode();
	gotoxy(x,y);
}

int rank()
{
/*	FILE *fp;
	int n;
	char buf[2000];
	if(fp = fopen("rank.txt","r"))==NULL)
	{
		perror("rank.txt file no search");
		exit(1);
	}
	while((n=fread(buf,sizeof(char) *2,1,fp))>0)
	{
		fwrite(buf,sizeof(char),n,fp);
	}

	fclose(fp);*/
}

int mainmenu()
{
	data datas;
	char back;
	vector<data> vector;
        system("clear");
        printf("%c[32m",27);
        printf("                ===================== \n");
        printf("\n");
        printf("                 @@@ @@@ @@@ @@@ @ @@@\n");
        printf("                  @  @    @  @ @   @  \n");
        printf("                  @  @@@  @  @@@ @ @@@\n");
        printf("                  @  @    @  @ @ @   @\n");
        printf("                  @  @@@  @  @ @ @ @@@\n");
        printf("\n");
        printf("                =====================\n");
        printf("\n");
        printf("%c[33m",27);
        printf("                  1) Start Game \n");
        printf("                  2) Total Score \n");
        printf("                  3) Creater information\n");
        printf("                  4) Exit \n");
        printf("%c[32m",27);
        printf("                =====================\n");
        printf("%c[33m",27);
        printf("                select menu : ");
        printf("%c[39m",27);
        std::cin>>menuNum;
        switch(menuNum)
        {
                case 1:
                        system("clear");
                        std::cout<<"typing user name :";
                        std::cin>>datas.name;
                        datas.score = 0;
                        datas.level = 1;
			vector.push_back(datas);
		 	system("clear");
			loading(0,0);
                        gamestart();
                        break;
                case 2:
                        system("clear");
//                        rank();
			printf("mainmenu key : p\n");
			printf(" : ");
			std::cin>>back;
			if(back=='p')
			{
				system("clear");
				return mainmenu();
			}
			else
			{
				system("clear");
				printf("error , exit\n");
				exit(0);
			}
                        break;
                case 3:
                        system("clear");
                        printf("                Creater : LEE SANG HOON \n");
                        printf("                Seoil university Computer Application Junior\n");
			printf("		Age : 26\n");
			printf("		2020 / 1 / 13\n");
			printf("		Version : 0.1\n");
                        printf("mainmenu key : p\n");
                        printf(" : ");
                        std::cin>>back;
                        if(back=='p')
                        {
				system("clear");
                                return mainmenu();
                        }
                        else
                        {
                                system("clear");
                                printf("error , exit\n");
                                exit(0);
                        }

                        break;
                case 4:
                        system("clear");
			exit(0);
                        break;
                default:
                        mainmenu();
 	       }

}

int main()
{
	wiringPiSetup();
	data datas;

   	pinMode(up,INPUT);
	pinMode(upL,OUTPUT);
    	pinMode(left,INPUT);
    	pinMode(leftL,OUTPUT);
    	pinMode(down,INPUT);
    	pinMode(downL,OUTPUT);
    	pinMode(right,INPUT);
    	pinMode(rightL,OUTPUT);

	mainmenu();
}
