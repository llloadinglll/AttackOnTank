#pragma once
#include <Windows.h>
#define  PI 3.14159265
class Missile
{
public:
	Missile(
		int _x,
		int _y,
		int _target_x,
		int _target_y
		):
		x(_x), y(_y), target_x(_target_x), target_y(_target_y)
	{}

	~Missile(void){}

	int x, y, direction,target_x,target_y;

};

