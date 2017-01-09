#pragma once
#include <Windows.h>
#include "SuperTank.h"

class Thing
{
public:
	Thing(
		int _id,
		int _x,
		int _y,
		int _time,
		int _last
		) :
		id(_id), x(_x), y(_y), time(_time), last(_last){}

	~Thing(void){}

	int id;
	int x;
	int y;
	int time;   //���ߴ���ʱ��
	int last;  //����Ч������ʱ��
};

