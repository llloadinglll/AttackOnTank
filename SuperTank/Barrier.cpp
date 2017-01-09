#include "stdafx.h"
#include "Barrier.h"
#include "SuperTank.h"

Barrier::~Barrier(void)
{
}

void Barrier::DrawBarrier(HDC & hdc1,HDC &hdc2){
	
		//TransparentBlt(hdc1,x,y,64,64,hdc2,xs,ys,64,64,RGB(255,255,255));
		switch (id)
		{
		case GRASS:			
			if (state==SHAKE_STATE)
			{
				
					TransparentBlt(hdc1,x,y,64,64,hdc2,(shake_step/10)%3*64,64,64,64,RGB(255,255,255));//目的使每10贞换一幅图，没三幅图循环一次
					if ((++shake_step)==30)
					{
						
						shake_step=0;
						state=NORMAL_STATE;
					}
				
			}else if(state==SHOOT_STATE)
			{
				
					TransparentBlt(hdc1,x,y,64,64,hdc2,(shoot_step/10)%3*64,2*64,64,64,RGB(255,255,255));//目的使每10贞换一幅图，没三幅图循环一次
					if ((++shoot_step)==30)
					{
					
						shoot_step=0;
						state=NORMAL_STATE;
					}
				
			}else
			{
				if (life<=0)
				{
					id=BARRIER_NONE;
				}else if (life<=400)
				{
					TransparentBlt(hdc1,x,y,64,64,hdc2,64,0,64,64,RGB(255,255,255));
					state=DAMAGE_STATE;
				}else if(life<=1000)
				{
					TransparentBlt(hdc1,x,y,64,64,hdc2,0,0,64,64,RGB(255,255,255));
				}
			}
			break;
		case TREE:
			if (state==SHOOT_STATE)
			{
				
					TransparentBlt(hdc1,x,y,64,64,hdc2,(shoot_step/10)%3*64,4*64,64,64,RGB(255,255,255));//目的使每10贞换一幅图，没三幅图循环一次
					if ((++shoot_step)==30)
					{
						
						shoot_step=0;
						state=NORMAL_STATE;
					}
				
			}else
			{
				if (life<=0)
				{
					id=BARRIER_NONE;
				}else if (life<=100)
				{
					TransparentBlt(hdc1,x,y,64,64,hdc2,64,3*64,64,64,RGB(255,255,255));
					state=DAMAGE_STATE;
				}else if(life<=200)
				{
					TransparentBlt(hdc1,x,y,64,64,hdc2,0,3*64,64,64,RGB(255,255,255));
				}
			}
				break;
		case WATER_ONE:
			TransparentBlt(hdc1,x,y,64,64,hdc2,0,5*64,64,64,RGB(255,255,255));
			break;
		case WATER_TWO:
			TransparentBlt(hdc1,x,y,64,64,hdc2,64,5*64,64,64,RGB(255,255,255));
			break;
		case WATER_THREE:
			TransparentBlt(hdc1,x,y,64,64,hdc2,0,6*64,64,64,RGB(255,255,255));
			break;
		case WATER_FOUR:
			TransparentBlt(hdc1,x,y,64,64,hdc2,64,6*64,64,64,RGB(255,255,255));
			break;
		case WATER_FIVE:
			TransparentBlt(hdc1,x,y,64,64,hdc2,2*64,6*64,64,64,RGB(255,255,255));
			break;
		case WATER_SIX:
			TransparentBlt(hdc1,x,y,64,64,hdc2,3*64,6*64,64,64,RGB(255,255,255));
			break;
		case WALL:
			if (life<=0)
			{
				id=BARRIER_NONE;
			}else if (life<=75)
			{
				TransparentBlt(hdc1,x,y,64,64,hdc2,3*64,7*64,64,64,RGB(255,255,255));
			}else if(life<=150)
			{
				TransparentBlt(hdc1,x,y,64,64,hdc2,2*64,7*64,64,64,RGB(255,255,255));
			}
			else if(life<=250)
			{
				TransparentBlt(hdc1,x,y,64,64,hdc2,64,7*64,64,64,RGB(255,255,255));
			}
			else if(life<=350)
			{
				TransparentBlt(hdc1,x,y,64,64,hdc2,0,7*64,64,64,RGB(255,255,255));
			}
			break;
		case STONE:
			if (life<=0)
			{
				id=BARRIER_NONE;
			}else if (life<=150)
			{
				TransparentBlt(hdc1,x,y,64,64,hdc2,3*64,8*64,64,64,RGB(255,255,255));
			}else if(life<=300)
			{
				TransparentBlt(hdc1,x,y,64,64,hdc2,2*64,8*64,64,64,RGB(255,255,255));
			}
			else if(life<=450)
			{
				TransparentBlt(hdc1,x,y,64,64,hdc2,64,8*64,64,64,RGB(255,255,255));
			}
			else if(life<=600)
			{
				TransparentBlt(hdc1,x,y,64,64,hdc2,0,8*64,64,64,RGB(255,255,255));
			}
			break;
		case BUCKET:
			if (life<=0)
			{
				id=BARRIER_NONE;
				OpenExplode(12, x + 32, y + 32 -96, OBJECT_BOMB, BUCKET);
			}else{
				TransparentBlt(hdc1,x,y,64,64,hdc2,0,9*64,64,64,RGB(255,255,255));
			}
			
			break;
		case IRON:
			if (life<=0)
			{
				id=BARRIER_NONE;
			}else{
				TransparentBlt(hdc1,x,y,64,64,hdc2,64,9*64,64,64,RGB(255,255,255));
			}
			
			break;
		case PITON:
			TransparentBlt(hdc1,x,y,64,64,hdc2,2*64,9*64,64,64,RGB(255,255,255));
			if (cd>0)cd--;
			break;
		case BASTION:
			if (life<=0)
			{
				//预留
			}else if (life<=125)
			{
				TransparentBlt(hdc1,x,y,64,64,hdc2,192,0,64,64,RGB(255,255,255));
			}else if(life<=250)
			{
				TransparentBlt(hdc1,x,y,64,64,hdc2,128,0,64,64,RGB(255,255,255));
			}
			else if(life<=375)
			{
				TransparentBlt(hdc1,x,y,64,64,hdc2,64,0,64,64,RGB(255,255,255));
			}
			else if(life<=500)
			{
				TransparentBlt(hdc1,x,y,64,64,hdc2,0,0,64,64,RGB(255,255,255));
			}
			break;
		default:
			break;

			}
	}

