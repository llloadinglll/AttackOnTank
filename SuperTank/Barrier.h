#pragma once
#include <Windows.h>
//草和树所处的状态
#define NORMAL_STATE 0
#define SHAKE_STATE 1
#define SHOOT_STATE 2
#define DAMAGE_STATE 3
//地图块
#define BARRIER_NONE 0
#define GRASS 1
#define TREE 2
#define WATER 3
#define WATER_ONE 31
#define WATER_TWO 32
#define WATER_THREE 33
#define WATER_FOUR 34
#define WATER_FIVE 35
#define WATER_SIX 36
#define WALL 4
#define STONE 5
#define BUCKET 6
#define IRON  7
#define PITON 8
#define BASTION 9
class Barrier
{
public:

	Barrier(
		int _id=0,
		int _x=0,
		int _y=0,
		int _life=10000,
		int _state=NORMAL_STATE,
		int _shake_step=0,
		int _shoot_step=0,
		int _cd=0,
		bool _activate=false
	):
	id(_id),x(_x),y(_y),life(_life),state(_state),shake_step(_shake_step),shoot_step(_shoot_step),cd(_cd),old_id(_id),activate(_activate){}



	~Barrier(void);

	int id;
	int x;
	int y;
	int life;
	int state;
	int shake_step;
	int shoot_step;
	int cd;
	int old_id;
	bool activate;
	void DrawBarrier(HDC &,HDC &);

};

