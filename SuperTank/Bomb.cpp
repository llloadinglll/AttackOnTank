#include "stdafx.h"
#include "Bomb.h"


Bomb::Bomb(int _id, int _x, int _y,int _owner,int _size,int _bombX,int _step,int _temp,bool _end):
	id(_id),x(_x),y(_y),owner(_owner),size(_size),bombX(_bombX),step(_step),temp(_temp),end(_end){}






Bomb::~Bomb(void)
{
}

void Bomb::DrawBomb(HDC & hdc1,HDC & hdc2){
		if (end==false)
		{
			
			size=temp+16;
			int offset=size/2;
			TransparentBlt(hdc1,x-offset,y-offset,size,size,hdc2,bombX,0,size,size,RGB(255,255,255));
			if ((++step)%3==0)//ÿ3֡�������Ժ��л���һ��ͼ
			{
				temp+=16;
				bombX+=temp;

			}

			if (step==id*3)//һ����ʾid*3֡����
			{
				end=true;
				temp=0;
				bombX=0;
			}
		}
}



