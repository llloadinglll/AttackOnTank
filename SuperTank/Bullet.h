#pragma once
class Bullet
{
public:
	Bullet::Bullet(
	double _x=0,
	double _y=0,
	int _speed=6,		//
	int _attack=30,		//
	int _id=0,
	int _wide=10,		//
	int _high=10,		//
	int _owner=0,
	int _face=0,
	int _explode=0,		//
	int _offset_w=0,	//
	int _offset_h=0,		//
	bool _dead=false,
	int _hp=30
	):
	x(_x),
	y(_y),
	speed(_speed),
	attack(_attack),
	id(_id),
	wide(_wide),
	high(_high),
	owner(_owner),
	face(_face),
	explode(_explode),
	offset_w(_offset_w),
	offset_h(_offset_h),
	dead(_dead),
	hp(_hp)
{
}

	~Bullet(void){}
	double x;
	double y;
	int speed;
	int attack;
	int id;
	int wide;
	int high;
	int owner;
	int face;
	int explode;
	int offset_w;
	int offset_h;
	int dead;
	int hp;
};

