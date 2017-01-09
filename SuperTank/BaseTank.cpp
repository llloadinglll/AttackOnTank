#include "stdafx.h"
#include "BaseTank.h"
#include "SuperTank.h"


BaseTank::~BaseTank(void)
{
}


void BaseTank::Change(int _face)
{
	face=_face;
	if(gun_lock==false)gun_face=face;
	if (++move_step>2) move_step=0;
}

void BaseTank::Fire()
{
}

void BaseTank::Death()
{
}

void BaseTank::Draw(HDC &DC1,HDC &DC2,bool fire)
{
	/*
	int gun_x;
	int gun_y;
	int fire_x;
	int fire_y;
	int _gun_step;
	_gun_step=gun_step/20;
	switch(gun_face)
	{
	case DOWN:
		gun_x=x;
		gun_y=y-_gun_step*(bullet_power/10);
		fire_x=gun_x;
		fire_y=gun_y+48;
		break;
	case LEFT:
		gun_x=x+_gun_step*(bullet_power/10);
		gun_y=y;
		fire_x=gun_x-48;
		fire_y=gun_y;
		break;
	case UP:
		gun_x=x;
		gun_y=y+_gun_step*(bullet_power/10);
		fire_x=gun_x;
		fire_y=gun_y-48;
		break;
	case RIGHT:
		gun_x=x-_gun_step*(bullet_power/10);
		gun_y=y;
		fire_x=gun_x+48;
		fire_y=gun_y;
	}
	if(fire==false)
	{
	//Ì¹¿Ëµ×ÅÌ
	BitBlt(DC1,x,y,64,64,DC2,face*64,id*1280+move_step*128+64,SRCPAINT);
	BitBlt(DC1,x,y,64,64,DC2,face*64,id*1280+move_step*128,SRCAND);
	//Ì¹¿ËÅÚÌ¨
	BitBlt(DC1,gun_x,gun_y,64,64,DC2,gun_face*64,id*1280+(5-_gun_step)*128+128*3+64,SRCPAINT);
	BitBlt(DC1,gun_x,gun_y,64,64,DC2,gun_face*64,id*1280+(5-_gun_step)*128+128*3,SRCAND);
	}
	else
	{
		//Ì¹¿Ë»ğ»¨
		if(fire_step>0)
		{
			--fire_step;
			BitBlt(DC1,fire_x,fire_y,64,64,DC2,gun_face*64,id*1280+9*128+64,SRCPAINT);
			BitBlt(DC1,fire_x,fire_y,64,64,DC2,gun_face*64,id*1280+9*128,SRCAND);
		}
		if(gun_step>0)
		{
			gun_step-=fire_speed;
			if(gun_step<0)gun_step=0;
		}
	}*/
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      