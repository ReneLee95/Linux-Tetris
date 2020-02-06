#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define MAIN_X 20
#define MAIN_Y 10
#define EMPTY 0
#define CEILLING -1
#define WALL 1
#define INACTIVE_BLOCK 2
#define ACTIVE_BLOCK -2
#define MAIN_X_ADJ 3
#define MAIN_Y_ADJ 1

int map[MAIN_X][MAIN_Y] = {0, };
int mapcpy[MAIN_X][MAIN_Y] = {0, };

void gotoxy(int x,int y) {
	printf("\033[%d;%df",y,x);
	fflush(stdout);
}

int maps(int n)
{
	for(int i =0; i<MAIN_X; i++)
	{
		for(int j =0; j<MAIN_Y; j++)
		{
			if(i==MAIN_X-1||j==0||j==MAIN_Y-1)
			{
				map[i][j]=1;
				mapcpy[i][j] = 1;
			}
			else
			{
				map[i][j] =0;
				mapcpy[i][j]=0;
			}
		}
	}
	if(n == 1)
	{
		for(int i =0; i<MAIN_X; i++)
		{
			for(int j =0; j<MAIN_Y; j++)
			{
				if(map[i][j]==1)
				{
					printf("%c[43m",27);
					printf("■");
					printf("%c[49m",27);
				}
				else printf(" ");
			}
			printf("\n");
		}
	}
        else
        {
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
                                else printf(" ");
                        }
                        printf("\n");
                }
        }
}
