#pragma once
#include <Windows.h>

#define DOWN 0
#define LEFT 1
#define UP 2
#define RIGHT 3

class BaseTank
{
public:
	BaseTank::BaseTank(
	int _owner=0,
	int _id=0,
	int _no=0,
	int _life=1,
	int _hp=100,
	int _maxhp=100,
	int _mp=1000,
	int _maxmp=1000,
	double _speed=3,
	bool _move_lock=false,
	int _attack=30,
	int _attack_frame=0,
	int _attack_cd=40,
	int _face=LEFT,
	double _x=30,
	double _y=250,
	int _armor=0,
	bool _gun_lock=false,
	int _gun_back=10,
	int _move_step=0,
	int _gun_face=LEFT,
	double _speedbate=1,
	bool _activate=false,
	bool _stop=true,
	int _frame=0,
	int _step=0,
	int _frameper=15,
	int _stepmax=3,
	int _ai_searchcd=40,
	int _ai_frame=0,
	int _ai_step=-1,
	int _ai_judgecd=150,
	int _face_cd=50,
	int _face_frame=0,
	int _attack_temp=0,
	int _speed_temp=0,
	int _exp=0,
	int _lv=1
	):id(_id),
	owner(_owner),
	no(_no),
	life(_life),
	hp(_hp),
	maxhp(_maxhp),
	mp(_mp),
	maxmp(_maxmp),
	speed(_speed),
	move_lock(_move_lock),
	attack(_attack),
	attack_frame(_attack_frame),
	attack_cd(_attack_cd),
	face(_face),
	x(_x),
	y(_y),
	armor(_armor),
	gun_lock(_gun_lock),
	gun_back(_gun_back),
	move_step(_move_step),
	gun_face(_gun_face),
	speedbate(_speedbate),
	activate(_activate),
	stop(_stop),
	frame(_frame),
	step(_step),
	frameper(_frameper),
	stepmax(_stepmax),
	ai_judgecd(_ai_judgecd),
	ai_searchcd(_ai_searchcd),
	ai_frame(_ai_frame),
	ai_step(_ai_step),
	face_cd(_face_cd),
	face_frame(_face_frame),
	attack_temp(_attack_temp),
	speed_temp(_speed_temp),
	exp(_exp),
	lv(_lv)
	{
	}

	~BaseTank(void);

	void Move(int);
	void Change(int);
	void Fire();
	void Death();
	void Draw(HDC &,HDC &,bool);

	int id;
	int no;				//
	int owner;
	int life;			
	int hp;
	int maxhp;			//
	int mp;				
	int maxmp;			//
	double speed;		//
	bool move_lock;		
	int attack;			//
	int attack_frame;
	int attack_cd;
	int face;			
	double x;				//
	double y;				//
	int armor;			//
	bool gun_lock;	
	int gun_back;
	int move_step;
	int gun_face;
	double speedbate;
	bool activate;
	bool stop;
	int frame;
	int step;
	int frameper;
	int stepmax;
	int ai_judgecd;
	int ai_searchcd;
	int ai_frame;
	int ai_step;
	int face_cd;
	int face_frame;
	int attack_temp;
	int speed_temp;
	int lv;
	int exp;
};

