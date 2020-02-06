#include <iostream>
#include <stdio.h>
#include <wiringPi.h>

#define up 29
#define upL 23
#define right 28
#define rightL 22
#define down 27
#define downL 1
#define left 21
#define leftL 0

void sensor()
{
	wiringPiSetup();

	pinMode(up,INPUT);
	pinMode(upL,OUTPUT);
	pinMode(left,INPUT);
	pinMode(leftL,OUTPUT);
	pinMode(down,INPUT);
	pinMode(downL,OUTPUT);
	pinMode(right,INPUT);
	pinMode(rightL,OUTPUT);

	int curnumU =0;
	int curnumD =0;
	int curnumL =0;
	int curnumR =0;
//void up{
	if(digitalRead(up)==0)
	{
		digitalWrite(upL,1);
		curnumU = 5;
	}
	else
	{
		digitalWrite(upL,0);
		curnumU = 0;
	}

//void left{
        if(digitalRead(left)==0)
	{
		digitalWrite(leftL,1);
		curnumL = 3;
	}
        else
	{
		digitalWrite(leftL,0);
		curnumL = 0;
	}

//void right{
        if(digitalRead(right)==0)
	{
		digitalWrite(rightL,1);
		curnumR = 1;
	}
        else
	{
		digitalWrite(rightL,0);
		curnumR = 0;
	}

//void down{
        if(digitalRead(down)==0)
	{
		digitalWrite(downL,1);
		curnumD = 2;
        else
	{
		digitalWrite(downL,0);
		curnumD = 0;
	}
}
