#pragma once
#include <Windows.h>

#define DOWN 0
#define LEFT 1
#define UP 2
#define RIGHT 3
class Object
{
public:
	Object(bool _activate=false,
		int _x=0,
		int _y=0,
		int _id=0,
		bool _dynamic=false
	):
	activate(_activate),
	x(_x),
	y(_y),
	id(_id),
	dynamic(_dynamic)
	{}

	~Object(void){}

	bool activate;
	int x,y;
	bool dynamic;
	int id;
};

