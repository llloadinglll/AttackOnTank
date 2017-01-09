// SupperTankWar.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "SuperTank.h"
//障碍物类
#include "Barrier.h"
#include <wingdi.h>
#pragma comment (lib,"msimg32.lib")
#include <cmath>
#include <MMSystem.h>
#pragma  comment (lib,"winmm.lib")
#include <Digitalv.h>
#include <Vfw.h>
#pragma comment(lib,"vfw32.lib")

#include "mmsystem.h"//导入声音头文件
#pragma comment(lib,"winmm.lib")//导入声音头文件库

//是否播放音效
bool sound=TRUE;
//鼠标当前地图块属性
int mouse_id=WALL;
int mouse_x;
int mouse_y;
//矩形块碰撞检测减小量
const int offset=5;
int game_no=0;
const int game_max=4;


//判断障碍物是否生产道具
void JudgeThingE(BaseTank*);
void JudgeThingB(Barrier*);

//兼容内存设备
HDC bufferDC;
HDC bufferDC2;
HDC winDC;
HDC backgroundDC;
HDC player_tankDC;
HDC enemy_tankDC;
HDC bulletDC;
HDC barrierDC;
HDC bombDC;
HDC armorDC;
HDC attrDC;
HDC attringDC;
HDC adding_attrDC;
HDC level_upDC;
HDC missileDC;
HDC recoveryDC;
HDC bastionDC;
HDC buttonDC;
HDC topDC;
HDC skillDC;
HDC gamewinallDC;

//NEW
HDC player_state_mapDC;
HDC thingDC;
HDC startDC;
HDC selectDC;
HDC gamewinDC;
HDC gameoverDC;
HDC playerdeadDC;
HDC	introduceDC;
// HDC blankDC;
HDC sandDC;
HDC lvDC;

HBRUSH hBruRed;
HBRUSH hBruBlue;
HBRUSH hBruYellow;
HBRUSH hBruWhite;

HBRUSH hBru_Laser;
HPEN hPen_Border;

HPEN hPen_laser;
HPEN hPen_black;
HBRUSH  hBru_Black;
HBRUSH	hBru_hp;
HBRUSH  hBru_charge;


//兼容位图
HBITMAP bufferBMP;
HBITMAP backgroundBMP;
HBITMAP player_tankBMP;
HBITMAP bulletBMP;
HBITMAP barrierBMP;
HBITMAP bombBMP;
HBITMAP enemy_tankBMP;
HBITMAP blank;
HBITMAP sand;
HBITMAP armorBMP;
HBITMAP missileBMP;
HBITMAP recoveryBMP;
HBITMAP bastionBMP;
HBITMAP personBMP;
HBITMAP startBMP;
HBITMAP selectBMP;
HBITMAP gameoverBMP;
HBITMAP gamewinBMP;
HBITMAP playerdeadBMP;
HBITMAP introduceBMP;
HBITMAP creditsBMP;
HBITMAP gamewinallBMP;
//new
HBITMAP bufferBMP2;
HBITMAP player_state_map;
HBITMAP thing_map;


HBITMAP attrbmp;

HBITMAP adding_attrbmp;
HBITMAP level_upbmp;

HBITMAP topbmp;
HBITMAP buttonbmp;

HBITMAP skillbmp;
HBITMAP lvbmp;

//游戏窗口句柄
HWND hWnd;
//游戏定时器
UINT game_timer;
//游戏状态
int game_state;
//BOSS模式
bool boss_mode=false;
//玩家坦克
BaseTank* player_tank;
const int mp_decrease_cd=150;
int mp_decrease_frame=0;
//玩家子弹
list<Bullet*> bullet;
//火花容器z
list<Bomb*> bomb;
//敌人容器
list<BaseTank*> enemy_tank;
//物体容器
list<Barrier*> object;
//道具容器
list<Thing*> thing;

//坐标偏移量（用于计算屏幕显示坐标）
double offset_x=0;
const int offset_y=-96;
//地图块数宽和高
const int block_wide=GAME_TOTW/64;
const int block_high=(GAME_H+offset_y*2)/64;
const int rows = 9;
const int cols = 40;

//几幅地图
vector<int> barrier_map;
const int map_max=1;
int map_bg[block_wide*block_high]={0};
int barrier_layout[block_high*block_wide] = {
 };

//沙子冰块河流等的地形地图，共game_max关
int mapIndex[block_wide*block_high]={};
int map_all[game_max][block_wide*block_high]={
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 5, 3, 3, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 8, 4, 4, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
	
	3, 3, 3, 5, 3, 3, 3, 5, 3, 3, 3, 5, 3, 3, 10, 14, 14, 14, 11, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 3, 5, 3, 3, 3, 5, 3, 3, 10, 14, 14, 14, 14, 7, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 3, 1, 3, 5, 3, 1, 1, 1, 1, 1, 1, 14, 14, 14, 14, 11, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 3, 1, 3, 5, 3, 1, 3, 5, 3, 3, 10, 14, 14, 14, 14, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 3, 1, 3, 5, 3, 1, 3, 10, 13, 13, 14, 14, 14, 14, 11, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 3, 1, 3, 5, 3, 1, 3, 10, 12, 12, 14, 14, 14, 14, 11, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 3, 1, 3, 5, 3, 1, 3, 5, 3, 3, 10, 14, 14, 14, 11, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 3, 1, 1, 1, 1, 1, 3, 5, 3, 3, 8, 14, 14, 14, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 3, 3, 3, 5, 3, 3, 3, 5, 3, 3, 3, 10, 14, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,

	3, 3, 0, 0, 3, 3, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 3, 0, 0, 3, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 3, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 3, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 3, 0, 0, 3, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 3, 0, 0, 3, 3, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3

};

//障碍物敌人地图，共game_max关
int barrier_all[game_max][block_high*block_wide] = {
	2, 0, 0, 0, 0, 0, 2, 0, 90, 2, 0, 0, 1, 1, 0, 0, 4, 8, 8, 0, 90, 4, 0, 0, 0, 0, 0, 1, 1, 0, 0, 2, 5, 0, 92, 5, 0, 2, 2, 2, 0, 0, 0, 2, 1, 1, 0, 0, 0, 1, 0, 0, 2, 0, 1, 6, 4, 8, 8, 0, 0, 0, 4, 0, 0, 90, 0, 0, 4, 0, 0, 4, 0, 0, 0, 0, 91, 2, 9, 2, 1, 2, 0, 0, 1, 1, 0, 2, 1, 1, 0, 5, 0, 0, 4, 4, 4, 4, 4, 1, 2, 1, 0, 4, 1, 1, 0, 4, 0, 0, 0, 5, 5, 0, 5, 0, 7, 0, 0, 2, 0, 0, 2, 0, 2, 5, 0, 0, 0, 0, 2, 0, 0, 6, 4, 0, 90, 0, 4, 0, 0, 0, 0, 2, 0, 2, 4, 0, 90, 2, 0, 0, 90, 0, 5, 0, 0, 5, 2, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 2, 1, 6, 4, 0, 91, 0, 4, 0, 0, 2, 0, 33, 31, 34, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 2, 90, 0, 0, 1, 1, 4, 0, 90, 0, 4, 0, 0, 1, 0, 32, 2, 32, 0, 0, 0, 5, 0, 5, 0, 0, 0, 8, 8, 8, 8, 8, 5, 1, 0, 0, 1, 1, 2, 0, 0, 0, 0, 2, 0, 0, 4, 4, 4, 4, 4, 2, 2, 33, 31, 35, 6, 36, 31, 34, 0, 4, 0, 0, 0, 0, 1, 1, 0, 1, 0, 8, 2, 0, 0, 0, 1, 1, 0, 5, 0, 0, 1, 0, 0, 0, 0, 6, 4, 8, 8, 0, 0, 32, 2, 6, 4, 6, 2, 32, 0, 2, 0, 0, 0, 0, 0, 0, 91, 0, 1, 8, 0, 0, 0, 2, 0, 90, 0, 0, 0, 2, 1, 0, 0, 1, 1, 0, 4, 8, 8, 0, 1, 32, 6, 4, 92, 4, 6, 32, 5, 0, 0, 0, 0, 1, 90, 0, 1, 0, 92, 8, 
	
	0, 4, 0, 0, 4, 0, 0, 0, 5, 8, 0, 0, 0, 0, 0, 0, 0, 6, 0, 7, 5, 0, 2, 4, 0, 2, 0, 91, 2, 0, 4, 0, 1, 0, 4, 0, 7, 7, 7, 7, 0, 0, 0, 90, 0, 0, 92, 0, 4, 0, 5, 0, 7, 6, 0, 0, 0, 5, 0, 0, 5, 0, 0, 0, 1, 0, 4, 4, 0, 2, 4, 0, 2, 1, 1, 1, 0, 94, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 91, 0, 0, 0, 0, 0, 0, 5, 91, 0, 0, 0, 8, 5, 2, 4, 4, 91, 2, 0, 1, 0, 0, 1, 4, 0, 0, 32, 0, 0, 2, 2, 0, 0, 8, 0, 0, 0, 6, 0, 4, 0, 6, 0, 0, 5, 0, 0, 92, 0, 0, 0, 8, 8, 0, 2, 1, 1, 0, 4, 33, 31, 31, 1, 0, 92, 4, 32, 7, 93, 0, 0, 0, 0, 8, 0, 7, 0, 5, 0, 0, 0, 4, 0, 0, 0, 0, 0, 91, 0, 0, 7, 7, 2, 2, 0, 0, 2, 0, 1, 32, 0, 0, 0, 4, 0, 4, 32, 7, 0, 0, 9, 0, 0, 8, 0, 6, 0, 8, 0, 7, 0, 8, 0, 0, 0, 0, 0, 5, 5, 6, 5, 0, 0, 0, 4, 4, 4, 90, 1, 32, 91, 1, 2, 0, 92, 0, 36, 34, 93, 0, 0, 5, 0, 8, 0, 5, 0, 0, 0, 0, 0, 8, 91, 7, 0, 0, 0, 5, 5, 0, 5, 5, 2, 1, 1, 1, 31, 31, 31, 35, 2, 0, 0, 1, 0, 2, 0, 32, 0, 2, 2, 0, 4, 0, 0, 0, 0, 90, 0, 0, 0, 5, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 93, 2, 1, 4, 0, 2, 0, 4, 0, 4, 4, 0, 0, 2, 0, 1, 94, 0, 0, 4, 0, 5, 0, 0, 4, 4, 0, 4, 0, 6, 0, 0, 5, 0, 0, 90, 0, 5, 5, 7, 7, 0, 0, 4, 1, 0, 91, 0, 2, 0, 1, 1, 4, 4, 0, 7, 7, 7, 7,

	0, 0, 0, 7, 6, 0, 8, 0, 0, 0, 0, 7, 0, 92, 4, 0, 2, 92, 0, 0, 90, 0, 0, 6, 0, 0, 0, 0, 6, 0, 7, 1, 1, 90, 5, 0, 94, 5, 5, 0,
	0, 0, 0, 7, 0, 90, 0, 0, 0, 0, 6, 7, 92, 94, 5, 0, 5, 92, 4, 0, 90, 91, 0, 0, 5, 0, 6, 0, 0, 0, 4, 1, 1, 90, 5, 2, 0, 4, 5, 0,
	0, 0, 0, 0, 0, 90, 0, 7, 5, 5, 0, 5, 0, 0, 7, 8, 7, 0, 4, 0, 90, 91, 0, 6, 5, 0, 0, 0, 6, 0, 4, 1, 1, 91, 5, 93, 5, 0, 5, 0,
	0, 0, 0, 0, 0, 0, 0, 7, 5, 91, 0, 5, 2, 7, 7, 8, 7, 7, 4, 0, 0, 92, 0, 0, 5, 0, 6, 0, 0, 0, 4, 1, 1, 92, 5, 0, 5, 0, 5, 4,
	0, 0, 0, 7, 0, 0, 0, 8, 8, 4, 0, 2, 0, 8, 8, 8, 8, 8, 6, 5, 93, 0, 0, 6, 5, 0, 0, 0, 6, 0, 4, 1, 1, 93, 5, 6, 5, 0, 5, 9,
	0, 0, 0, 7, 0, 0, 0, 7, 5, 91, 0, 5, 2, 7, 7, 8, 7, 7, 4, 0, 0, 92, 0, 0, 5, 0, 6, 0, 0, 0, 4, 1, 1, 92, 5, 0, 5, 0, 5, 4,
	0, 0, 0, 7, 0, 90, 0, 7, 5, 5, 0, 5, 0, 0, 7, 8, 7, 0, 4, 0, 90, 91, 0, 6, 0, 0, 0, 0, 6, 0, 4, 1, 1, 91, 2, 0, 5, 0, 6, 0,
	0, 0, 0, 7, 0, 90, 0, 0, 0, 0, 6, 7, 92, 94, 5, 0, 5, 92, 4, 0, 90, 91, 0, 0, 2, 0, 6, 0, 0, 0, 4, 1, 1, 90, 2, 0, 5, 4, 6, 0,
	0, 0, 0, 7, 6, 0, 8, 0, 0, 0, 0, 7, 0, 92, 4, 0, 2, 92, 0, 0, 90, 0, 0, 6, 5, 0, 0, 0, 6, 0, 7, 1, 1, 90, 5, 5, 94, 94, 4, 0,

	0, 1, 0, 0, 1, 92, 92, 1, 1, 1, 1, 1, 1, 2, 1, 0, 7, 0, 4, 0, 90, 0, 0, 0, 4, 0, 0, 94, 4, 0, 4, 7, 2, 1, 94, 1, 94, 4, 4, 4, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 2, 0, 1, 7, 0, 0, 0, 4, 91, 0, 4, 7, 0, 4, 0, 0, 91, 0, 7, 5, 0, 1, 94, 1, 4, 9, 4, 0, 1, 1, 33, 31, 31, 34, 1, 1, 1, 1, 1, 1, 94, 2, 0, 7, 0, 91, 0, 92, 0, 0, 0, 7, 0, 94, 0, 4, 0, 0, 7, 4, 5, 2, 1, 94, 4, 4, 4, 0, 0, 1, 32, 94, 94, 32, 1, 1, 1, 1, 1, 1, 2, 0, 1, 7, 7, 7, 7, 7, 7, 7, 0, 7, 7, 7, 7, 7, 0, 7, 7, 6, 5, 4, 1, 1, 2, 94, 1, 0, 0, 1, 32, 94, 94, 32, 1, 1, 1, 1, 1, 1, 2, 0, 0, 8, 8, 8, 6, 6, 0, 0, 2, 7, 0, 0, 8, 0, 0, 0, 5, 4, 6, 5, 0, 2, 94, 1, 94, 1, 1, 0, 36, 31, 31, 35, 1, 1, 1, 1, 1, 1, 2, 1, 0, 7, 7, 7, 2, 2, 7, 7, 7, 7, 0, 92, 0, 0, 0, 4, 4, 8, 4, 6, 4, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 94, 2, 1, 7, 6, 2, 0, 0, 0, 7, 0, 0, 8, 0, 4, 5, 4, 5, 5, 4, 5, 4, 5, 2, 1, 2, 2, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 2, 0, 0, 7, 2, 92, 0, 90, 92, 7, 0, 93, 4, 5, 5, 0, 6, 4, 8, 0, 0, 1, 1, 0, 2, 6, 6, 0, 1, 0, 1, 1, 92, 92, 1, 1, 1, 1, 1, 1, 2, 0, 1, 7, 94, 0, 93, 93, 94, 7, 0, 0, 92, 0, 8, 0, 4, 0, 0, 0, 2, 93, 0, 94, 2, 6,
};

bool LevelUping=false;
int AddAttring;
int adding=0;
int uping=0;
int shaking=0;
//升级所需经验数组
int lvexp[11]={0,800,1200,1600,2000,2500,3000,3500,4000,5000,1000000};


//敌人坦克信息表
//maxhp,speed,attack,attack_cd,armor,exp
int tank_attr[5][6]={
	120,2,10,100,0,80,
	180,3,15,50,1,100,
	240,2,20,70,2,120,
	350,4,25,80,3,150,
	500,1,30,100,4,200,
};

//子弹属性表
//speed attack wide high hp offsetw offseth
int bullet_attr[11][7]={
	8,10,12+offset*2,15+offset*2,20,20,8,
	10,15,12+offset*2,15+offset*2,30,20,8,
	8,20,12+offset*2,18+offset*2,40,20,8,
	12,25,14+offset*2,20+offset*2,50,20,8,
	5,45,14+offset*2,22+offset*2,100,20,8,

	8,10,12+offset*2,15+offset*2,20,20,8,
	10,15,12+offset*2,15+offset*2,30,20,8,
	8,20,12+offset*2,18+offset*2,40,20,8,
	12,25,14+offset*2,20+offset*2,50,20,8,
	5,45,14+offset*2,22+offset*2,100,20,8,

	6,30,16+offset*2,22+offset*2,80,20,8,
};


//障碍物信息表,id和life
int barrier_info[37][2]={BARRIER_NONE,10000,
	GRASS,1000,TREE,200,WATER,10000,
	WALL,350,STONE,600,BUCKET,40,IRON,10000,PITON,10000,BASTION,500};
//游戏介绍是否显示
bool keydown_f1=false;
bool keydown_f2=false;
bool keydown_f3=false;
bool keydown_f4=false;
bool keydown_f5=false;
int credits=0;
bool introduce_ing=false;
bool credits_ing=false;
//蓄力中
int charge=-1;
int chargemax=60;
//质子撞击炮 ;
int proton_collider=0;
//fps
int time_now,time_pre,fps,frame;
//关卡
int wintime;
const int wintimemax=200;
int stage;
//基地
int base_time;
const int base_timemax=100;
//玩家生命数
int player_death=0;//0表示没死，有数值表示距重生的帧数
//玩家属性上限
const int max_life=100;
const int max_speed=12;
const int max_fire_speed=12;
const int max_bullet_speed=12;
//
int gameover_time=0;
int gamewin_time=0;
//敌人数量
int all_id=0;
int enemy_num;
int enemy_rest;
const int enemy_maxscreen=4;
const int enemy_max=100;
int enemy_time=0;
const int enemy_timemax=100;
//道具
int item;
int item_x;
int item_y;
int item_stay_time;
const int item_stay_timemax=1000;
//屏幕震动
double bgx,bgy;

//用以绘制玩家状态栏的一些坐标
double hpX1,hpY1,hpX2,hpY2,mpX1,mpY1,mpX2,mpY2,fullhpX,fullmpX;
double expX1,expY1,expX2,expY2,fullexpX;

#define MAX_LOADSTRING 100


// 全局变量:
//激光发射的全局控制变量
int laser_index=0;
bool laser_open=true;
//激光矩形坐标，开始和终点
int laserxs=0;
int laserys=0;
int laserxe=0;
int laserye=0;
//是否发射激光
int k_down=false;

//是否发射导弹
int l_down=false;
//导弹变量
int missile_index=0;
//爆炸激发一次即可,即OpenExplode在其中一帧动画调用即可
int onceExplode=0;
//被锁定的坦克指针
BaseTank *lock_enemy=NULL;
//导弹指针
Missile * myMissile=NULL;
//
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
					   _In_opt_ HINSTANCE hPrevInstance,
					   _In_ LPTSTR    lpCmdLine,
					   _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SUPERTANK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SUPERTANK));

	
	//开始游戏
	GameStart();
	mciSendString(_T("open honglian.mp3 Alias music"),NULL,0,NULL);
	mciSendString(_T ("play music repeat"),NULL,0,NULL);
	// 主消息循环:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SUPERTANK));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{


	hInst = hInstance; // 将实例句柄存储在全局变量中

	//屏幕宽和高
	int width, height;
	width = GetSystemMetrics(SM_CXSCREEN);
	height = GetSystemMetrics(SM_CYSCREEN);

	bool fullScreen = true;
	if (width != 1366 || height != 768)
		fullScreen = false;
	else
		fullScreen = true;
		

	if (!fullScreen){
		//在屏幕中央创建窗口
		hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
			(width - (GAME_W + 6)) / 2, (height - (GAME_H + 28)) / 2 - 10, GAME_W + 6, GAME_H + 28, NULL, NULL, hInstance, NULL);
	}
	else{
		//全屏
		hWnd = CreateWindow(
			szWindowClass,
			szTitle,
			WS_POPUP,
			0, 0,
			1366, 768,
			NULL, NULL,
			hInstance,
			NULL);
	}

	if (!hWnd)
	{
		return FALSE;
	}

	ShowCursor(FALSE);//显示时隐藏鼠标
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//播放视频
	//mciSendString(_T("open start.avi type MPEGVideo Alias movie"),NULL,0,NULL);
	//mciSendString(_T("play movie fullscreen"),NULL,0,NULL);


	//获得窗口设备
	winDC=GetDC(hWnd);

	//创建缓冲内存
	bufferDC=CreateCompatibleDC(winDC);
	//创建背景内存
	backgroundDC=CreateCompatibleDC(winDC);
	//创建玩家坦克内存
	player_tankDC=CreateCompatibleDC(winDC);
	//
	enemy_tankDC=CreateCompatibleDC(winDC);
	//创建炮弹内存
	bulletDC=CreateCompatibleDC(winDC);
	armorDC=CreateCompatibleDC(winDC);
	//创建图块内存
	barrierDC=CreateCompatibleDC(winDC);
	//创建火花内存
	bombDC=CreateCompatibleDC(winDC);
	//导弹内存
	missileDC=CreateCompatibleDC(winDC);

	sandDC=CreateCompatibleDC(winDC);

	//模拟WINDC
	bufferDC2=CreateCompatibleDC(winDC);   

	//用以绘制玩家状态栏的DC
	player_state_mapDC=CreateCompatibleDC(winDC);
	//堡垒
	bastionDC=CreateCompatibleDC(winDC);
	//new
	thingDC=CreateCompatibleDC(winDC);
	
	topDC=CreateCompatibleDC(winDC);
	buttonDC=CreateCompatibleDC(winDC);

	skillDC=CreateCompatibleDC(winDC);
	recoveryDC=CreateCompatibleDC(winDC);
	gamewinallDC=CreateCompatibleDC(winDC);

	//blankDC=CreateCompatibleDC(winDC);

	//载入背景草地
	blank = (HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(IDB_BG),IMAGE_BITMAP,GAME_W,576,LR_DEFAULTCOLOR);
	//载入沙地冰块图
	sand= (HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(IDB_SAND),IMAGE_BITMAP,256,256,LR_DEFAULTCOLOR);
	recoveryBMP=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(IDB_RECOVERY),IMAGE_BITMAP,567,425,LR_DEFAULTCOLOR);
	//player_tankBMP=CreateCompatibleBitmap(winDC,256,256);
	//创建缓冲位图
	bufferBMP=CreateCompatibleBitmap(winDC,GAME_TOTW,GAME_H);

	bufferBMP2=CreateCompatibleBitmap(winDC,GAME_W,GAME_H);

	player_state_map=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(IDB_PLAYER_STATE_MAP),IMAGE_BITMAP,286,96,LR_DEFAULTCOLOR);

	hBruRed=CreateSolidBrush(RGB(161,23,21));

	hBruBlue=CreateSolidBrush(RGB(0,90,171));

	hBruYellow=CreateSolidBrush(RGB(251,178,23));

	hBruWhite=CreateSolidBrush(RGB(255,255,255));



	hBru_Laser=CreateSolidBrush(RGB(255,255,255));

	hBru_Black=CreateSolidBrush(RGB(50,50,50));

	hPen_Border=CreatePen(0,1,RGB(100,100,100));

	hPen_laser=CreatePen(0,1,RGB(255,255,255));

	hPen_black=CreatePen(0,1,RGB(0,0,0));

	hBru_hp=CreateSolidBrush(RGB(186,40,53));

	hBru_charge=CreateSolidBrush(RGB(255,222,0));

	attrDC=CreateCompatibleDC(winDC);

	

	adding_attrDC=CreateCompatibleDC(winDC);

	level_upDC=CreateCompatibleDC(winDC);

	lvDC=CreateCompatibleDC(winDC);

	bastionBMP=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(IDB_BASTION),IMAGE_BITMAP,256,64,LR_DEFAULTCOLOR);

	//new
    thing_map=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(IDB_THING),IMAGE_BITMAP,320,64,LR_DEFAULTCOLOR);
	//载入背景位图
	//backgroundBMP=(HBITMAP)LoadImage(hInstance,MAKEINTRESOURCE(BACK_GROUND),IMAGE_BITMAP,GAME_W,GAME_H,LR_DEFAULTCOLOR);
	//载入坦克位图
	player_tankBMP=(HBITMAP)LoadImage(hInstance,MAKEINTRESOURCE(IDB_PLAYERTANK),IMAGE_BITMAP,256,192,LR_DEFAULTCOLOR);
	//载入敌人坦克位图
	enemy_tankBMP=(HBITMAP)LoadImage(hInstance,MAKEINTRESOURCE(IDB_ENEMYTANK),IMAGE_BITMAP,256,960,LR_DEFAULTCOLOR);
	//载入炮弹位图
	bulletBMP=(HBITMAP)LoadImage(hInstance,MAKEINTRESOURCE(IDB_BULLET),IMAGE_BITMAP,256,832,LR_DEFAULTCOLOR);
	//载入武器位图
	armorBMP=(HBITMAP)LoadImage(hInstance,MAKEINTRESOURCE(IDB_ARMOR),IMAGE_BITMAP,256,640,LR_DEFAULTCOLOR);
	//载入障碍物位图
	barrierBMP=(HBITMAP)LoadImage(hInstance,MAKEINTRESOURCE(IDB_BARRIER),IMAGE_BITMAP,256,640,LR_DEFAULTCOLOR);
	//载入爆炸火花位图
	bombBMP=(HBITMAP)LoadImage(hInstance,MAKEINTRESOURCE(IDB_BOMB),IMAGE_BITMAP,1248,192,LR_DEFAULTCOLOR);
	//载入导弹位图
	missileBMP=(HBITMAP)LoadImage(hInstance,MAKEINTRESOURCE(IDB_MISSILE),IMAGE_BITMAP,256,192,LR_DEFAULTCOLOR);

	attrbmp=attrbmp=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(ATTR_BMP),IMAGE_BITMAP,329,96,LR_DEFAULTCOLOR);

	adding_attrbmp=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(ADDING_ATTR),IMAGE_BITMAP,333,96,LR_DEFAULTCOLOR);

	level_upbmp=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(LEVEL_UP_BMP),IMAGE_BITMAP,567,452,LR_DEFAULTCOLOR);

	 startBMP=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(IDB_START),IMAGE_BITMAP,1366,768,LR_DEFAULTCOLOR);
	 selectBMP=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(IDB_SELECT),IMAGE_BITMAP,1366,768,LR_DEFAULTCOLOR);
	 gameoverBMP=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(IDB_GAMEOVER),IMAGE_BITMAP,583,425,LR_DEFAULTCOLOR);
	 gamewinBMP=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(IDB_GAMEWIN),IMAGE_BITMAP,567,425,LR_DEFAULTCOLOR);
	 gamewinallBMP=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(IDB_GAMEWINALL),IMAGE_BITMAP,567,425,LR_DEFAULTCOLOR);
	 //playerdeadBMP=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(IDB_),IMAGE_BITMAP,1366,768,LR_DEFAULTCOLOR);
	 introduceBMP=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(IDB_INTRODUCE),IMAGE_BITMAP,700,500,LR_DEFAULTCOLOR);
	 //gamewinBMP=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(IDB_GAMEWIN),IMAGE_BITMAP,567,425,LR_DEFAULTCOLOR);
	 personBMP=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(IDB_PERSON),IMAGE_BITMAP,700,500,LR_DEFAULTCOLOR);
	 topbmp=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TOP_BMP),IMAGE_BITMAP,1366,96,LR_DEFAULTCOLOR);
	 buttonbmp=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(BUTTON_BMP),IMAGE_BITMAP,1366,96,LR_DEFAULTCOLOR);

	 skillbmp=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(SKILL_BMP),IMAGE_BITMAP,375,96,LR_DEFAULTCOLOR);

	 lvbmp=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(LV),IMAGE_BITMAP,370,26,LR_DEFAULTCOLOR);

	
	startDC=CreateCompatibleDC(winDC);
	selectDC=CreateCompatibleDC(winDC);
	gameoverDC=CreateCompatibleDC(winDC);
	gamewinDC=CreateCompatibleDC(winDC);
	playerdeadDC=CreateCompatibleDC(winDC);
	introduceDC=CreateCompatibleDC(winDC);
	//选入到对应内存
	SelectObject(gamewinallDC,gamewinallBMP);
	SelectObject(bufferDC,bufferBMP);
	SelectObject(backgroundDC,blank);
	SelectObject(player_tankDC,player_tankBMP);
	SelectObject(enemy_tankDC,enemy_tankBMP);
	SelectObject(bulletDC,bulletBMP);
	SelectObject(armorDC,armorBMP);
	SelectObject(barrierDC,barrierBMP);
	SelectObject(bombDC,bombBMP);
	SelectObject(sandDC,sand);
	SelectObject(missileDC,missileBMP);

	SelectObject(bufferDC2,bufferBMP2);
	SelectObject(player_state_mapDC,player_state_map);

	SelectObject(thingDC,thing_map);
	SelectObject(attrDC,attrbmp);
	SelectObject(adding_attrDC,adding_attrbmp);
	SelectObject(level_upDC,level_upbmp);
	
	SelectObject(startDC,startBMP);
	SelectObject(selectDC,selectBMP);
	SelectObject(gameoverDC,gameoverBMP);
	SelectObject(gamewinDC,gamewinBMP);
	SelectObject(playerdeadDC,playerdeadBMP);

	SelectObject(topDC,topbmp);
	SelectObject(buttonDC,buttonbmp);
	SelectObject(skillDC,skillbmp);
	
	SelectObject(recoveryDC,recoveryBMP);
	SelectObject(lvDC,lvbmp);

	SelectObject(bastionDC,bastionBMP);
	//
	//TransparentBlt(bufferDC,0,0,64,64,player_tankDC,0*64,0*64,64,64,RGB(255,255,255));

	//用系统时间初始化随机数种子
	srand((unsigned)time(NULL));
	
	//玩家坦克初始化 
	
	return TRUE;
}



bool return_up;
//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// 没用到
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_TIMER:
			switch (game_state)
			{
			case GAME:
				Game();
				break;
			case GAMESTART:
				/*
				mciSendString(_T("open honglian.mp3 Alias music2"),NULL,0,NULL);
				mciSendString(_T("play music2 repeat"),NULL,0,NULL);*/
				/*	PLAYA(IDR_START);*/
				
				
				DrawStart();
				if (keydown_f1==true){
					DrawIntroduce();
				}
				if (keydown_f2==true){
					DrawCredits();
				}
				if (KEYDOWN(VK_RETURN)){
					game_state=GAMESELECT;
				}
				BitBlt(winDC,0,0,GAME_W,GAME_H,bufferDC,0,0,SRCCOPY);

				return_up = false;
				break;
			case GAMESELECT:
				/*mciSendString(_T("close music2"),NULL,0,NULL);*/
				DrawSelect();

				/*
				if (keydown_f1==true){
					DrawIntroduce();
				}
				if (keydown_f2==true){
					DrawCredits();
				}

				
				if (KEYDOWN('1')){
					player_tank->attack+=20;
					game_state=GAME;
				}else if (KEYDOWN('2')){
					player_tank->speed+=2;
					game_state=GAME;
				}else if (KEYDOWN('3')){
					player_tank->attack_cd-=15;
					game_state=GAME;
				}else if (KEYDOWN('4')){
					player_tank->maxhp+=150;
					player_tank->hp=player_tank->maxhp;
					game_state=GAME;
				}else if (KEYDOWN('5')){
					player_tank->maxmp+=75;
					player_tank->mp=player_tank->maxmp;
					game_state=GAME;
				}
				*/

				if (KEYUP(VK_RETURN))
					return_up = true;

				if (return_up&&KEYDOWN(VK_RETURN))
					game_state = GAME;
				break;
			case GAMEOVER:
				gameover_time--;
				TransparentBlt(winDC,350,100,583,425,gameoverDC,0,0,583,425,RGB(255,255,255));
				if (gameover_time==0){
					GameStart();
				}
				break;
			case GAMEWIN:
				gamewin_time--;
				if(game_no==game_max-1){
					TransparentBlt(winDC,350,100,567,425,gamewinallDC,0,0,567,425,RGB(255,255,255));
				}
				else TransparentBlt(winDC,350,100,567,425,gamewinDC,0,0,567,425,RGB(255,255,255));
				if (gamewin_time==0){
					game_no++;
					if (game_no==game_max){
						game_state=GAMESTART;
						game_no=0;
						GameStart();
					}else
					{
					game_state=GAME;
					DataInit();
					}
				}
				break;
			default:
				break;
			}
			break;
		break;
		//ESC键退出
	case WM_KEYDOWN:
		//mciSendString(_T("close movie"),NULL,0,NULL);
		
		switch (wParam)
		{
			case VK_ESCAPE:
				if (MessageBox(hWnd,_T("确定要退出吗？"),_T("Keyboard"),MB_OKCANCEL)==IDOK)
				{
					PostMessage(hWnd, WM_CLOSE, 0, 0);//给窗口发送WM_CLOSE消息
				}				
				break;
			case WM_CLOSE: //准备退出
				DestroyWindow( hWnd ); //释放窗口
				break;		
			case VK_F1:
				keydown_f1^=1;
				keydown_f2=false;
				break;
			case VK_F2:
				keydown_f2^=1;
				keydown_f1=false;				
				break;
			case VK_F3:
				keydown_f3^=1;
				if (keydown_f3){
					mciSendString(_T("close music"),NULL,0,NULL);
				}else{
					  mciSendString(_T("open honglian.mp3 Alias music"),NULL,0,NULL);
					  mciSendString(_T ("play music repeat"),NULL,0,NULL);
				}
				break;
			case VK_F4:
				keydown_f4=!keydown_f4;
				break;
			case VK_F5:
				keydown_f5^=1;
				break;
		}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


//自己写的函数代码
//游戏开始
void GameStart(){

	game_state=GAMESTART;

	all_id=0;
	//这边生成一个玩家坦克，@有待写
	player_tank=new BaseTank();
	player_tank->maxhp=200;
	player_tank->maxmp=100;
	player_tank->id=all_id++;
	player_tank->owner=0;
	player_tank->armor=0;
	player_tank->life=4;
	player_tank->attack=25;
	
	stage=0;
	//game_state=GAME;
	DataInit();
}

//游戏过程
void Game(){

	
	//屏幕移动
	ScreenMove();
	//检测敌方坦克是否在视野区
	TankBarrierCheck();
	

	//玩家按键响应
	if ((uping==0)&&(!keydown_f5)){
		if (player_death==0)
		{
			Key();
		}
		//更新状态
		BulletMove();
		PlayerTankStep(*player_tank);
		EnemyTankStep();
		if (proton_collider>0) ProtonCollide();

		frame++;
		time_now=GetTickCount();
		if (time_now-time_pre>=1000){
			fps=frame;
			frame=0;
			time_pre=time_now;
		}
	}
	if(adding>0)
	{
		adding--;
		if(adding<0)
			adding=0;
	}
	if (uping>0){
		uping--;
	}
	if (keydown_f3)
	{
		mciSendString(_T("close music"),NULL,0,NULL);
	}


	//绘制游戏界面
	DrawGame();
	//@还有一些其他的处理
	

}

//按键处理
void Key(){
	//坦克行走，转动和锁定炮台，超级功能，开火
	if(KEYDOWN('S')){	
		player_tank->face=DOWN;
		player_tank->stop=false;
		player_tank->gun_face=DOWN;
		if (!keydown_f4)
		{
			PLAYB(MOVE_SOUND);
		}
		
		Move(*player_tank,DOWN);
	}else if(KEYDOWN('A')){
		player_tank->face=LEFT;
		player_tank->stop=false;
		player_tank->gun_face=LEFT;
		if(!keydown_f4)
		PLAYB(MOVE_SOUND);
		Move(*player_tank,LEFT);
	}else if(KEYDOWN('W')){
		player_tank->face=UP;
		player_tank->stop=false;
		player_tank->gun_face=UP;
		if(!keydown_f4)
		PLAYB(MOVE_SOUND);
		Move(*player_tank,UP);
	}else if(KEYDOWN('D')){
		player_tank->face=RIGHT;
		player_tank->stop=false;
		player_tank->gun_face=RIGHT;
		if(!keydown_f4)
		PLAYB(MOVE_SOUND);
		Move(*player_tank,RIGHT);
	}else if(KEYUP('S')){
		//player_tank->face=DOWN;
		player_tank->stop=true;
	}else if(KEYUP('A')){
		//player_tank->face=LEFT;
		player_tank->stop=true;
	}else if(KEYUP('W')){
		//player_tank->face=UP;
		player_tank->stop=true;
	}else if(KEYUP('D')){
		//player_tank->face=RIGHT;
		player_tank->stop=true;
	};
	if (KEYDOWN('J')){
		OpenFire(*player_tank);
	}
	if (KEYDOWN('K'))
	{
		if (player_tank->mp>=20)
		{
			k_down=true;
			if ((++laser_index)>1)//按住按钮
			{
				laser_open=false;
				if (laser_index%20==0)
				{
					player_tank->mp-=10;
					OpenLaser(*player_tank);

				}
			}
			if (laser_open)//按一下
			{
				player_tank->mp-=10;
				OpenLaser(*player_tank);
			}				
		}
		
	}else if (KEYUP('K'))
	{
		k_down=false;
		laser_index=0;
		laser_open=true;
	}

	//发射导弹
	if (KEYDOWN('L'))
	{
		if (player_tank->mp>=20 && myMissile==NULL)
		{
			int px = player_tank->x+32;
			int py = player_tank->y+32;
			int minDist = 1e9;
			for (list<BaseTank*>::iterator iter = enemy_tank.begin(); iter != enemy_tank.end(); iter++)
			{
				BaseTank &enemyTank = **iter;
				int ex = enemyTank.x + 32;
				int ey = enemyTank.y + 32;

				if (enemyTank.activate==true && enemyTank.hp>0 && (ex - px)*(ex - px) + (ey - py)*(ey - py)< minDist)
				{
					minDist = (ex - px)*(ex - px) + (ey - py)*(ey - py);
					//锁定坦克信息
					lock_enemy = &enemyTank;
				}
			}

			if (minDist != 1e9)
			{
				player_tank->mp -= 20;
				if (!keydown_f4)
				{
					PLAYA(OPEN_MISSILE);
				}
				missile_index = 0;
				myMissile = new Missile(player_tank->x,player_tank->y,lock_enemy->x,lock_enemy->y);
				//OpenMissile(lock_enemy);
			}
		}
	}

	if ((KEYDOWN(VK_SPACE))&&(charge==-1)&&(player_tank->mp>=10)){
		if (player_tank->attack_frame==0){
			charge=0;
			player_tank->attack_frame=player_tank->attack_cd;
			player_tank->mp-=10;
		}	
	}
	if ((KEYUP(VK_SPACE))&&(charge!=-1)){
		OpenFireCharge(*player_tank,charge,chargemax);
		charge=-1;
	}
	if (KEYDOWN(VK_OEM_1)){
		if ((proton_collider==0)&&(player_tank->mp>=80)){
			proton_collider=300;
			player_tank->mp-=80;
		}
	}

	//升级 加攻击力
	if(LevelUping==true&&KEYDOWN('U'))
	{
		player_tank->attack+=12;
		LevelUping=false;
		AddAttring=1;
		adding=150;
	}
	if(LevelUping==true&&KEYUP('U'))
	{
		//if(adding==0)
			//AddAttring=0;
	}
	//升级 加速度
	if(LevelUping==true&&KEYDOWN('I'))
	{
		AddAttring=2;
		player_tank->speed+=1;
		LevelUping=false;
		adding=150;
	
	}
	if(LevelUping==true&&KEYUP('I'))
	{
		
		
	}
	//升级 加最大HP
	if(LevelUping==true&&KEYDOWN('O'))
	{
		AddAttring=3;
		player_tank->maxhp+=100;
		player_tank->hp=player_tank->maxhp;
		LevelUping=false;
		adding=150;
	
	}
	if(LevelUping==true&&KEYUP('O'))
	{
		
	}
	//升级 加最大MP
	if(LevelUping==true&&KEYDOWN('P'))
	{
		AddAttring=4;
		player_tank->maxmp+=50;
		player_tank->mp=player_tank->maxmp;
		LevelUping=false;
		adding=150;
	
	}
	if(LevelUping==true&&KEYUP('P'))
	{
	
	} 
}

//游戏绘制
void DrawGame(){
	//BitBlt(bufferDC,0,0,GAME_TOTW,GAME_H,player_tankDC,0,0,WHITENESS);
	
	//绘制背景
	DrawBG();
	//绘制铁钉
	DrawPiton();
	//绘制玩家坦克（如果没死）
	if (player_death==0){
		DrawPlayer();
		DrawLaser(laserxs,laserys,laserxe,laserye);	
	}
	//绘制敌人坦克
	DrawEnemy();
	//绘制障碍物
	DrawBarrier();
	//处理和绘制道具
	Item();
	//绘制子弹
	DrawBullet();
	//绘制爆炸火花
	if (!keydown_f5){
	DrawBomb();
	}
	//绘制蓄力条
	if (player_death == 0 && charge >= 0) DrawCharge();
	//绘制导弹
	DrawMissile();
	//输出到屏幕
	//处理道具
	HandleThing();	
	//DrawLaser(500,500,800,800);
	if(shaking>0)
	{
		ShakeScreen();
		shaking--;
	}
	if (keydown_f1==true){
			DrawIntroduce();
	}
	if (keydown_f2==true){
			DrawCredits();
	}
	PrintToScreen();
}


//初始化
void DataInit(){
	SetTimer(hWnd,GAME_ID,GAME_TIME,NULL);
	player_tank->face=RIGHT;
	player_tank->gun_face=RIGHT;
	player_tank->hp=player_tank->maxhp;
	player_tank->mp=player_tank->maxmp;
	player_tank->x=30;
	player_tank->y=250;
	offset_x=0;

	time_now=0;
	time_pre=GetTickCount();
	fps=0;
	frame=0;

	for (int i=0;i<block_wide;i++)
		for (int j=0;j<block_high;j++){
			barrier_layout[j*block_wide+i]=barrier_all[game_no][j*block_wide+i];
		}
	for (int i=0;i<block_wide;i++)
		for (int j=0;j<block_high;j++){
			mapIndex[j*block_wide+i]=map_all[game_no][j*block_wide+i];
		}

	//BOSS模式
	boss_mode=false;
	//以下为动态资源的释放
	//子弹清空
	for(list<Bullet*>::iterator i=bullet.begin();i!=bullet.end();++i)
		delete *i;
	bullet.clear();
	//火花容器清空
	for(list<Bomb*>::iterator i=bomb.begin();i!=bomb.end();++i)
	  delete *i;
    bomb.clear();
	//敌人容器清空
	for(list<BaseTank*>::iterator i=enemy_tank.begin();i!=enemy_tank.end();++i)
		delete *i;
	enemy_tank.clear();

	for(list<Thing*>::iterator i=thing.begin();i!=thing.end();++i)
		delete *i;
	thing.clear();
	player_tank->attack_temp=0;
	player_tank->speed_temp=0;

	for(list<Barrier*>::iterator i=object.begin();i!=object.end();++i)
		delete *i;
	object.clear();
	//关卡
	wintime=0;
	//基地
	base_time=0;
	//玩家恢复
	player_death=false;
	//敌人数量
	//enemy_num=0;
	//enemy_rest=enemy_max;
	//enemy_time=1;
	//道具清零
	item=NONE;
	item_stay_time=0;
	AssignBarrierMap();


	//初始化object容器
	int barrierX;
	int barrierY;
	int mapX;
	int mapY;
	int blood;
	int i;//计算第几个障碍物
	Barrier *barrier;
	object.clear();
	for(vector<int>::iterator iter=barrier_map.begin();iter!=barrier_map.end();++iter){
		int &id=*iter;
		i=iter-barrier_map.begin();
		barrierX=i%block_wide;
		barrierY=i/block_wide;

		if ((id>0)&&(id<40)) {
			mapX=barrierX*64;
			mapY=barrierY*64-offset_y;
			blood=barrier_info[id][1];		
			barrier=new Barrier(id,mapX,mapY,blood);
			object.push_back(barrier);
		}

		if (id>=90){
			int tank_no=id%10;//第几类坦克，如90表示第0类，91表示第1类
			BaseTank* et=new BaseTank();
			//maxhp,speed,attack,attack_cd,armor
			et->maxhp=tank_attr[tank_no][0];
			et->hp=et->maxhp;
			et->speed=tank_attr[tank_no][1];
			et->attack=tank_attr[tank_no][2];
			et->attack_cd=tank_attr[tank_no][3];
			et->armor=tank_attr[tank_no][4];
			et->exp=tank_attr[tank_no][5];
			et->face=LEFT;
			et->gun_face=LEFT;
			et->activate=false;
			et->x=barrierX*64;
			et->y=barrierY*64;
			et->id=all_id++;	//唯一标识符
			et->owner=1;		//1表示敌人
			et->no=tank_no;		//第几类坦克
			enemy_tank.push_back(et);
		}

	}
}

void DrawStart(){
	BitBlt(bufferDC,0,0,GAME_W,GAME_H,startDC,0,0,SRCCOPY);
}

void DrawIntroduce(){
	SelectObject(introduceDC,introduceBMP);
	TransparentBlt(bufferDC,333,134,700,500,introduceDC,0,0,700,500,RGB(255,255,255));
}
void DrawCredits(){
	SelectObject(introduceDC,personBMP);
	TransparentBlt(bufferDC,333,134,700,500,introduceDC,0,0,700,500,RGB(255,255,255));
}
void DrawDeath(){
	TransparentBlt(bufferDC2,350,100,567,425,recoveryDC,0,0,567,425,RGB(255,255,255));
}


void DrawSelect(){
	BitBlt(bufferDC,0,0,GAME_W,GAME_H,bufferDC,0,0,WHITENESS);
	BitBlt(bufferDC,0,0,GAME_W,GAME_H,selectDC,0,0,SRCCOPY);
	TransparentBlt(bufferDC,player_tank->x,player_tank->y-offset_y,64,64,player_tankDC,64*3,0,64,64,RGB(255,255,255));
	TransparentBlt(bufferDC,player_tank->x,player_tank->y-offset_y,64,64,armorDC,player_tank->gun_face*64,player_tank->armor*64,64,64,RGB(255,255,255));
	BitBlt(winDC,0,0,GAME_W,GAME_H,bufferDC,0,0,SRCCOPY);
}


//绘制地图的各种障碍物，铁定另外画
void DrawBarrier(){
	for (list<Barrier *>::iterator iter=object.begin();iter!=object.end();)
	{
		bool erase=false;
		if (((*iter)->activate) && ((*iter)->id!=PITON))
		{
			if ((*iter)->id == BASTION)
			{
				//赢了
				if ((*iter)->life<=0)
				{
					game_state=GAMEWIN;
					if (game_no==game_max-1){
						gamewin_time=400;
					}else gamewin_time=250;
				}
				(*iter)->DrawBarrier(bufferDC,bastionDC);

			}else
			{
				(*iter)->DrawBarrier(bufferDC,barrierDC);
			}
		}
		if ((*iter)->id==BARRIER_NONE)
		{
			JudgeThingB(*iter);
			iter=object.erase(iter);
			erase=true;
		}
		if (!erase)
		{
			iter++;
		}
	}
}
//画铁钉子

void DrawPiton(){
	for (list<Barrier *>::iterator iter=object.begin();iter!=object.end();iter++)
	{
		if ((*iter)->id==PITON)
		{
			(*iter)->DrawBarrier(bufferDC,barrierDC);
		}
	}
}
//绘制背景
void DrawBG(){
	double X;


	X=(((offset_x)/double(GAME_W))-(int)(offset_x/GAME_W))*GAME_W;
	//绘制草地背景
	BitBlt(bufferDC,offset_x+(double)(GAME_W-X)-1,0+96,X,576,backgroundDC,0,0,SRCCOPY);
	BitBlt(bufferDC,offset_x,0+96,GAME_W-X,576,backgroundDC,X,0,SRCCOPY);
	//绘制山
	BitBlt(bufferDC,offset_x+(double)(GAME_W-X)-1,0,X,96,topDC,0,0,SRCCOPY);
	BitBlt(bufferDC,offset_x,0,GAME_W-X,GAME_H,topDC,X,0,SRCCOPY);
	//绘制海
	BitBlt(bufferDC,offset_x+(double)(GAME_W-X)-1,GAME_H-96,X,96,buttonDC,0,0,SRCCOPY);
	BitBlt(bufferDC,offset_x,GAME_H-96,GAME_W-X,GAME_H-96  ,buttonDC,X,0,SRCCOPY);
	for(int i=0;i<rows*cols;i++)
	{

		int rowNum=i/cols;
		int colNum=i%cols;
		int x=colNum*64;
		int y=rowNum*64;
		if(mapIndex[i]!=BLANK)
			TransparentBlt(bufferDC,x,y+96,64,64,sandDC,(mapIndex[i]%4)*64,(mapIndex[i]/4)*64,64,64,RGB(255,255,255));
	}
}

//绘制导弹
void DrawMissile(){

	if (myMissile == NULL) return;

	if (lock_enemy != NULL){
		myMissile->target_x = lock_enemy->x;
		myMissile->target_y = lock_enemy->y;
	}
	
	if (missile_index < 24)//先放导弹升起动画
	{
		int pic_index = missile_index / 4;
		myMissile->y -= 3;
		TransparentBlt(bufferDC, myMissile->x, myMissile->y+64, 64, 64, missileDC, pic_index*64, 0, 64, 64, RGB(255, 255, 255));
	}
	if (missile_index == 16){
		double degree_d = atan2(myMissile->target_y - myMissile->y, myMissile->target_x - myMissile->x);
		int degree = (int)(degree_d * 180 / PI);
		int area=-1;
		if (degree <= -157.5 || degree>=157.5) area = 3; //left
		else if (degree >= -157.5 && degree <= -112.5) area = 4; //left-up
		else if (degree >= -112.5 && degree <= -67.5) area = 0;//up
		else if (degree >= -67.5 && degree <= -22.5) area = 5;//right-up
		else if (degree >= -22.5 && degree <= 22.5) area = 1;//right
		else if (degree >= 22.5 && degree <= 67.5) area = 6; //right-down
		else if (degree >= 67.5 && degree <= 112.5) area = 2;//down
		else if (degree >= 112.5 && degree <= 157.5) area = 7;//left-down

		printf("degree is:%d #area is:%d \n", degree,area);

		if (area == -1) area = 1;
		myMissile->direction = area;

		TransparentBlt(bufferDC, myMissile->x, myMissile->y + 64, 64, 64, missileDC, myMissile->direction % 4 * 64, (myMissile->direction / 4 + 1) * 64, 64, 64, RGB(255, 255, 255));
	}
	if (missile_index > 16)
	{
		int move_dist = 50;
		double real_dist = sqrt(pow(myMissile->target_x - myMissile->x, 2) + pow(myMissile->target_y - myMissile->y, 2));
		if (real_dist < move_dist)
		{
			myMissile->x = myMissile->target_x;
			myMissile->y = myMissile->target_y;

			if (lock_enemy!=NULL) 
				lock_enemy->hp -= 300;//巨大强度伤害,一般敌人坦克致死
			OpenExplode(12, myMissile->x+32, myMissile->y+32, PLAYER_BOMB, BUCKET);
			TransparentBlt(bufferDC, myMissile->x, myMissile->y + 64, 64, 64, missileDC, myMissile->direction % 4 * 64, (myMissile->direction / 4 + 1) * 64, 64, 64, RGB(255, 255, 255));
			lock_enemy = NULL;
			myMissile = NULL;
		}
		else{
			double degree_d = atan2(myMissile->target_y - myMissile->y, myMissile->target_x - myMissile->x);
			myMissile->x += move_dist*cos(degree_d);
			myMissile->y += move_dist*sin(degree_d);
			TransparentBlt(bufferDC, myMissile->x, myMissile->y + 64, 64, 64, missileDC, myMissile->direction % 4 * 64, (myMissile->direction / 4 + 1) * 64, 64, 64, RGB(255, 255, 255));
		}

	}

	missile_index++;
}

//输出到屏幕
//输出缓冲区到屏幕
void PrintToScreen()	
{
	BitBlt(bufferDC2,0+bgx,0+bgy,GAME_W,GAME_H,bufferDC,0+offset_x,0,SRCCOPY);
	char str[10]="";
	sprintf_s(str,"%d",fps);
	//TextOutA(bufferDC2,1350,0,str,strlen(str)); // 显示fps，去掉即可用
	DrawStateMap();
	DrawLevelUp();
	TransparentBlt(bufferDC2,995,677,375,96,skillDC,0,0,375,96,RGB(255,255,255));
	if(player_death>0) DrawDeath();
	BitBlt(winDC,0,0,GAME_W,GAME_H,bufferDC2,0,0,SRCCOPY);
}
//绘制爆炸火花
void DrawBomb(){
	for (list<Bomb*>::iterator iter=bomb.begin();iter!=bomb.end();)
	{
		//爆炸范围和坐标
		int x;
		int y;
		int size;
		Bomb *b=*iter;
		int damage = b->id / 5 + 1;
		if (b->id == 12) damage *= 2;
		b->DrawBomb(bufferDC,bombDC);
		//爆炸每次产生的是都检测周围障碍物和坦克扣血
		size=b->size;
		x=b->x;//这个是中心坐标
		y=b->y+offset_y;

		for (list<Barrier*>::iterator iter=object.begin();iter!=object.end();iter++)
		{
			Barrier &b=**iter;
			//if (b.id!=BUCKET)
			{
				if (Collide(b.x,b.y,64,64,x-size/2,y-size/2-offset_y,size,size))
			     {
					 b.life -= damage;
			     }
			}
			
		}

		switch (b->owner)
		{
		case PLAYER_BOMB:
			//检测敌方坦克
			for (list<BaseTank *>::iterator enermy_iter=enemy_tank.begin();enermy_iter!=enemy_tank.end();enermy_iter++)
			{
				BaseTank &enermy = **enermy_iter;
				if (Collide(enermy.x,enermy.y,64,64,x-size/2,y-size/2,size,size))
				{
					enermy.hp -= damage;
				}

			}
			break;
		case ENERMY_BOMB:
			if (Collide(player_tank->x,player_tank->y,64,64,x-size/2,y-size/2,size,size))
			{
				player_tank->hp -= damage;
			}
			break;
		case OBJECT_BOMB:
			for (list<BaseTank *>::iterator enermy_iter=enemy_tank.begin();enermy_iter!=enemy_tank.end();enermy_iter++)
			{
				BaseTank &enemy = **enermy_iter;
				if (Collide(enemy.x, enemy.y, 64, 64, x - size / 2, y - size / 2, size, size))
				{
					enemy.hp -= damage;//这些都是没帧动画扣得血量
				}

			}
			if (Collide(player_tank->x,player_tank->y,64,64,x-size/2,y-size/2,size,size))
			{
				player_tank->hp-= damage;
			}
			break;

		default:
			break;
		}
		
		

		bool erase=false;
		if ((*iter)->end==true)
		{
			//delete (*iter);
			iter=bomb.erase(iter);
			erase=true;
		}
		if (erase==false)
		{
			iter++;
		}
	}
}

//处理和绘制玩家炮弹和炮口闪光
void PlayerBullet(){

}
//处理和绘制敌人坦克
void EnemyTank(){

}
void EnemyBullet(){

}

//处理和绘制道具
void Item(){

}
//载入所有地图
void AssignBarrierMap(){
	
	barrier_map.assign(barrier_layout,barrier_layout+block_wide*block_high*map_max);
}


//检测碰撞，分别为两矩形的左上点坐标及长宽
bool Collide(int ax,int ay,int aw,int ah,int bx,int by,int bw,int bh){

	ax+=offset;
	ay+=offset;
	aw-=offset*2;
	ah-=offset*2;
	bx+=offset;
	by+=offset;
	bw-=offset*2;
	bh-=offset*2;
	if ((ax>=bx)&&(ax<=bx+bw)&&(ay>=by)&&(ay<=by+bh))return true;
	if ((ax+aw>=bx)&&(ax+aw<=bx+bw)&&(ay>=by)&&(ay<=by+bh))return true;
	if ((ax>=bx)&&(ax<=bx+bw)&&(ay+ah>=by)&&(ay+ah<=by+bh))return true;
	if ((ax+aw>=bx)&&(ax+aw<=bx+bw)&&(ay+ah>=by)&&(ay+ah<=by+bh))return true;

	if ((bx>=ax)&&(bx<=ax+aw)&&(by>=ay)&&(by<=ay+ah))return true;
	if ((bx+bw>=ax)&&(bx+bw<=ax+aw)&&(by>=ay)&&(by<=ay+ah))return true;
	if ((bx>=ax)&&(bx<=ax+aw)&&(by+bh>=ay)&&(by+bh<=ay+ah))return true;
	if ((bx+bw>=ax)&&(bx+bw<=ax+aw)&&(by+bh>=ay)&&(by+bh<=ay+ah))return true;
	return false;
}

void BulletEnd(Bullet* b,int _x,int _y,int id){
	int power=b->attack/12;
	if (power<=0)power=1;
	if (power>=11)power=11;
	if (id == BUCKET) id = STONE;
	switch (b->face){
		case DOWN:
			OpenExplode(power,_x+b->wide/2,_y+b->high/2,b->owner,id);
		break;
		case LEFT:
			OpenExplode(power,_x+b->wide/2,_y+b->high/2,b->owner,id);
		break;
		case UP:
			OpenExplode(power,_x+b->wide/2,_y+b->high/2,b->owner,id);
		break;
		case RIGHT:
			OpenExplode(power,_x+b->wide/2,_y+b->high/2,b->owner,id);
		break;
	}

}

void BulletMove()
{
	for(list<Bullet*>::iterator iter_bullet=bullet.begin();iter_bullet!=bullet.end();){
		Bullet* b=*iter_bullet;
		if (b->dead){iter_bullet++;continue;}
		bool erase=false;
		int _x=b->x;
		int _y=b->y;
		switch (b->face){
			case DOWN:
				_y=_y+b->speed;
				if (_y>GAME_H-offset_y+100){
					iter_bullet=bullet.erase(iter_bullet);
					erase=true;
					continue;
				}		
			break;
			case LEFT:
				_x=_x-b->speed;
				if (_x<offset_x-400){
					iter_bullet=bullet.erase(iter_bullet);
					erase=true;
					continue;
				}
			break;
			case UP:
				_y=_y-b->speed;
				if (_y<0+offset_y-100){
					iter_bullet=bullet.erase(iter_bullet);
					erase=true;
					continue;
				}

			break;
			case RIGHT:
				_x=_x+b->speed;
				if (_x>offset_x+GAME_W+400){
					iter_bullet=bullet.erase(iter_bullet);
					erase=true;
					continue;
				}
			break;
		}//switch end



		for(list<Barrier*>::iterator iter_object=object.begin();iter_object!=object.end();iter_object++){
			Barrier*o=*iter_object;
			if ((Collide(_x,_y,b->wide,b->high,o->x,o->y+offset_y,64,64))){
				if ((o->id==TREE)||(o->id==WALL)||(o->id==STONE)||(o->id==BUCKET)||(o->id==IRON)||(o->id==BASTION)){
					o->life-=b->attack;
					if ((o->id==TREE)&&(o->state==NORMAL_STATE)){
						o->state=SHOOT_STATE;
					}/*
					if ((o->id==BUCKET)&&(o->life<=0)){
						OpenExplode(12,o->x+32,o->y+offset_y+32,OBJECT_BOMB,BUCKET);
					}*/
					BulletEnd(b,_x,_y,o->id);		
					iter_bullet=bullet.erase(iter_bullet);
					erase=true;
					
					break;
				}
				if ((o->id==GRASS)&&(o->state==NORMAL_STATE)){
					o->life-=b->attack;
					o->state=SHOOT_STATE;
				}
			}
		}//object for end
		if (erase)continue;

		for(list<BaseTank*>::iterator iter_tank=enemy_tank.begin();iter_tank!=enemy_tank.end();iter_tank++){
			BaseTank* t=*iter_tank;
			if ((b->owner!=t->owner)&&(t->activate)&&(Collide((int)b->x,(int)b->y,b->wide,b->high,t->x,t->y,64,64))){
				t->hp-=b->attack;
				BulletEnd(b,_x,_y,TANK);
				iter_bullet=bullet.erase(iter_bullet);
				erase=true;
				break;
			}

		}//enemy_tank for end
		if ((b->owner==1)&&(Collide(player_tank->x,player_tank->y,64,64,b->x,b->y,b->wide,b->high))){
			player_tank->hp-=b->attack;
			BulletEnd(b,_x,_y,TANK);
			iter_bullet=bullet.erase(iter_bullet);
			erase=true;
			break;
		}
		if (erase)continue;

		for(list<Bullet*>::iterator iter_bullet2=bullet.begin();iter_bullet2!=bullet.end();iter_bullet2++){
			Bullet* b2=*iter_bullet2;

			if ((b->owner!=b2->owner)&&(Collide(b->x,b->y,b->wide,b->high,b2->x,b2->y,b2->wide,b2->high))){
				b->hp-=b2->attack;
				b2->hp-=b->attack;
				if (b2->hp<=0)b2->dead=true;
				if (b->hp<=0){
					b->dead=true;
					BulletEnd(b,_x,_y,TANK);
					iter_bullet=bullet.erase(iter_bullet);
					erase=true;
					break;
				}
			}

		}//bullet2 for end
		if (erase)continue;

		b->x=_x;
		b->y=_y;
		if (!erase)iter_bullet++;
	}//bullet1 for end

	for(list<Bullet*>::iterator iter_bullet=bullet.begin();iter_bullet!=bullet.end();){
		Bullet* b=*iter_bullet;
		if (b->dead){
			iter_bullet=bullet.erase(iter_bullet);
			BulletEnd(b,b->x,b->y,TANK);
			continue;
		}
		iter_bullet++;
	}
}


void PlayerTankStep(BaseTank & t)
{
	if (player_death>0){
		player_death--;
		if(player_death==0){
			t.hp=t.maxhp;
		}
	}else{
		if (!t.stop){
			t.frame++;
			t.step=(t.frame/t.frameper);
			if (t.step==t.stepmax){
				t.step=0;
				t.frame=0;
			}
		}
		if (t.hp<=0){
			t.life--;
			OpenExplode(6,t.x+32,t.y+32,PLAYER_BOMB,TANK);
			if (t.life==0){
				game_state=GAMEOVER;
				gameover_time=150;
			}else{
				player_death=200;
			}
		}
		if (t.exp>=lvexp[t.lv]){
			uping=100;
			t.exp-=lvexp[t.lv];
			t.lv++;
			LevelUping=true;
		}
		if (mp_decrease_frame>0)mp_decrease_frame--;
		if (mp_decrease_frame==0){
			mp_decrease_frame=mp_decrease_cd;
			t.mp--;
		}
		if (t.attack_frame>0)t.attack_frame--;
	}
}
//更新敌人坦克状态
void EnemyTankStep(){
	for(list<BaseTank*>::iterator iter_tank=enemy_tank.begin();iter_tank!=enemy_tank.end();){
		BaseTank* et=*iter_tank;
		bool erase=false;
		if (et->hp<=0){
			JudgeThingE(et);
			iter_tank=enemy_tank.erase(iter_tank);
			OpenExplode(6,et->x+32,et->y+32,ENERMY_BOMB,TANK);
			player_tank->exp+=et->exp;
			player_tank->mp+=et->exp/30+4;
			if (et == lock_enemy)lock_enemy = NULL;//如果被导弹锁定的敌人死亡，导弹解除锁定
			if (player_tank->mp>player_tank->maxmp){
				player_tank->mp=player_tank->maxmp;
			}
			erase=true;
		}
		if (!et->stop){
			et->frame++;
			et->step=(et->frame/et->frameper);
			if (et->step==et->stepmax){
				et->step=0;
				et->frame=0;
			}
			if ((!Move(*et,et->face))&&(et->face_frame==0)){
				et->face=(et->face+rand()%3+1)%4;
				et->gun_face=et->face;
				et->face_frame=et->face_cd;
			}
		}
		if (et->attack_frame>0)et->attack_frame--;
		if (et->face_frame>0)et->face_frame--;
		if(!erase)iter_tank++;
		if(et->activate)EnemyAI(*et);
	}
}

int AIsearch(BaseTank&t,int ex,int ey){
	int ox=offset_x/64;
	const int m=GAME_W/64+4;
	const int n=block_high;
	int a[m][n];
	bool b[m][n];
	
	struct point{
		int x;int y;int dist;int dire;
	}p;
	point dl[n*m];
	const int d[4][2]={0,1,-1,0,0,-1,1,0};
	for (int i=0;i<m;i++){
		for (int j=0;j<n;j++){
			a[i][j]=0;
			b[i][j]=false;
		}
	}
	for(list<Barrier*>::iterator iter_object=object.begin();iter_object!=object.end();iter_object++){
		Barrier*ob=*iter_object;
		int x=((double)ob->x-offset_x)/64;
		int y=(int)(((double)ob->y+offset_y)/64);
		if ((ob->activate)&&(x>=0)&&(x<m)){
			a[x][y]=ob->id;
		}
	}
	
	int sx=((t.x+32)/64)-ox;
	int sy=((t.y+32)/64);
	int xx,yy;
	int find=-1;
	if (sx>=m) return find;
	b[sx][sy]=true;
	int head=0;
	int tail=1;
	p.x=sx;
	p.y=sy;
	p.dist=0;
	p.dire=-1;
	dl[head]=p;
	while (head!=tail){
		for (int i=0;i<4;i++){
			xx=dl[head].x+d[i][0];
			yy=dl[head].y+d[i][1];
			if ((xx<0)||(xx>=m)||(yy<0)||(yy>=n))continue;
			if ( (!b[xx][yy]) && ((a[xx][yy]==BARRIER_NONE)||(a[xx][yy]==PITON)||(a[xx][yy]==GRASS)||(a[xx][yy]>=90)) ){	
				point newp;
				newp.x=xx;
				newp.y=yy;
				newp.dist=dl[head].dist+1;
				if (dl[head].dire==-1)newp.dire=i;
				else newp.dire=dl[head].dire;
				dl[tail]=newp;
				tail++;
				b[xx][yy]=true;
				if ((xx==ex)&&(yy==ey)){
					find=newp.dire;
					break;
				}
			}
		}
		head++;
		if (find>-1) break;
	}
	return find;
}

void AImove_close(BaseTank&t){
	int ox=offset_x/64;
	int ex=((player_tank->x+32)/64)-ox;
	int ey=((player_tank->y+32)/64);
	int find=AIsearch(t,ex,ey);
	if (find==-1){
		t.stop=true;
		int f=rand()%10;
		if (f<4){
			t.face=f;
			t.gun_face=f;
			t.stop=false;
		}

	}else{
		t.face=find;
		t.gun_face=find;
		t.stop=false;
	}
};
void AIstop(BaseTank&t){
	t.stop=true;
};
void AImove_away(BaseTank&t){
	int ox=offset_x/64;
	int ex=ox+GAME_W/64+2;
	int ey=rand()%block_high;
	int find=AIsearch(t,ex,ey);
	if (find==-1){
		t.stop=true;
		int f=rand()%10;
		if (f<4){
			t.face=f;
			t.gun_face=f;
			t.stop=false;
		}
	}else{
		t.face=find;
		t.gun_face=find;
		t.stop=false;
	}
};

//坦克智能行动
void EnemyAI(BaseTank& t){
	if (t.ai_frame>0)t.ai_frame--;
	if (t.attack_frame==0){
		int ran=rand()%1500;
		int px=player_tank->x;
		int py=player_tank->y;
		switch (t.face){
		case DOWN:
			if (t.y<py){
				if (abs(t.x-px)<=3){
					if (ran<60) OpenFire(t);
				}else if (ran<40) OpenFire(t);
			}else if (ran<20) OpenFire(t);
			break;
		case LEFT:
			if (t.x>px){
				if (abs(t.y-py)<=2){
					if (ran<60) OpenFire(t);
				}else if (ran<40) OpenFire(t);
			}else if (ran<20) OpenFire(t);
			break;
		case UP:
			if (t.y>py){
				if (abs(t.x-px)<=3){
					if (ran<60) OpenFire(t);
				}else if (ran<40) OpenFire(t);
			}else if (ran<20) OpenFire(t);
			break;
		case RIGHT:
			if (t.x<px){
				if (abs(t.x-px)<=2){
					if (ran<60) OpenFire(t);
				}else if (ran<40) OpenFire(t);
			}else if (ran<20) OpenFire(t);
			break;
		}
	}

	if ((t.ai_frame==0)||((t.ai_frame==t.ai_judgecd*4/5)&&(t.ai_step==0))){
		t.ai_frame=t.ai_judgecd;
		t.ai_step=-1;

		const BaseTank& p=*player_tank;
		double dist=abs(p.x-t.x)+abs(p.y-t.y);
		double hpercent=t.hp/t.maxhp;
		int ran=rand()%100;

		if (dist<=64*5){
			if (hpercent<0.25){
				if(ran<5) {
					AImove_away(t);
					t.ai_step=1;
				}else if (ran<90){ 
					AImove_close(t);
					t.ai_step=2;
				}else {
					AIstop(t);
					t.ai_step=0;
				}
			}else{
				if(ran<5) {
					AImove_away(t);
					t.ai_step=1;
				}else if (ran<90){ 
					AImove_close(t);
					t.ai_step=2;
				}else {
					AIstop(t);
					t.ai_step=0;
				}
			}
		}else if(dist<=64*12){
			if (hpercent<0.25){
				if(ran<5) {
					AImove_away(t);
					t.ai_step=1;
				}else if (ran<80){ 
					AImove_close(t);
					t.ai_step=2;
				}else {
					AIstop(t);
					t.ai_step=0;
				}
			}else{
				if(ran<5) {
					AImove_away(t);
					t.ai_step=1;
				}else if (ran<80){ 
					AImove_close(t);
					t.ai_step=2;
				}else {
					AIstop(t);
					t.ai_step=0;
				}
			}
		}else if(dist<=64*24){
			if (hpercent<0.25){
				if(ran<5) {
					AImove_away(t);
					t.ai_step=1;
				}else if (ran<50){ 
					AImove_close(t);
					t.ai_step=2;
				}else {
					AIstop(t);
					t.ai_step=0;
				}
			}else{
				if(ran<5) {
					AImove_away(t);
					t.ai_step=1;
				}else if (ran<70){ 
					AImove_close(t);
					t.ai_step=2;
				}else {
					AIstop(t);
					t.ai_step=0;
				}
			}
		}
	}else if (t.ai_frame%t.ai_searchcd==0){
		switch(t.ai_step){
			case 0:
				AIstop(t);
			break;
			case 1:
				AImove_away(t);
			break;
			case 2:
				AImove_close(t);
			break;
		}
	}

}

//坦克移动
bool Move(BaseTank& t,int dire)
	{
		if ((t.owner==0)&&(charge>=0))return false;
		double _x,_y;
		switch (dire)
		{
			case LEFT:
				_x=t.x-(t.speed+t.speed_temp)*t.speedbate;
				_y=t.y;
				if (_x<0) _x=0;
			break;
			case UP:
				_x=t.x;
				_y=t.y-(t.speed+t.speed_temp)*t.speedbate;
				if (_y<0) _y=0;
			break;
			case DOWN:
				_x=t.x;
				_y=t.y+(t.speed+t.speed_temp)*t.speedbate;
				if (_y+64>=block_high*64)_y=block_high*64-64;
			break;
			case RIGHT:
				_x=t.x+(t.speed+t.speed_temp)*t.speedbate;
				_y=t.y;
				if (_x+64>=block_wide*64)_x=block_wide*64-64;
			break;
		}
		int block_x=(int)(_x+32)/64;
		int block_y=(int)(_y+32)/64;
		int temp=mapIndex[block_y*block_wide+block_x];
		if (temp==BLANK){
			t.speedbate=1;
		}else if (temp==ROAD){
			t.speedbate=1.33;
		}else if (temp==ICE){
			t.speedbate=2;
		}else if (temp>=SAND1){
			t.speedbate=0.5;
		}
		for(list<Barrier*>::iterator iter_object=object.begin();iter_object!=object.end();iter_object++){
			Barrier*ob=*iter_object;
			if(ob->id!=BARRIER_NONE){
			//if(ob->activate){
				if (Collide((int)_x,(int)_y,64,64,ob->x,ob->y+offset_y,64,64)){
					if (ob->id==GRASS){
						if (ob->state==NORMAL_STATE){
							ob->state=SHAKE_STATE;
						}
					}else if (ob->id==PITON){
						if (ob->cd==0){
							if(t.owner==0)t.hp-=5;
							else t.hp-=3;
							ob->cd=50;
							if (!keydown_f4 && t.id==player_tank->id)
							{
								PLAYA(PITON_SOUND);
							}
							
						}
					}else return false;
				}
			}
		}//barrier for end
		if(t.owner==0){
			for(list<BaseTank*>::iterator iter_tank=enemy_tank.begin();iter_tank!=enemy_tank.end();iter_tank++)
			{
				BaseTank* bt=*iter_tank;
				if(bt->activate){
					if (Collide((int)_x,(int)_y,64,64,bt->x,bt->y,64,64)){
						return false;
					}
				}
			}
		}else if(t.owner==1){
			if (Collide(player_tank->x,player_tank->y,64,64,_x,_y,64,64))return false;
			for(list<BaseTank*>::iterator iter_tank=enemy_tank.begin();iter_tank!=enemy_tank.end();iter_tank++)
			{
				BaseTank* bt=*iter_tank;
				if ((bt->id!=t.id)&&(bt->activate)&&(Collide(bt->x,bt->y,64,64,_x,_y,64,64)))
					return false;
			}
		}
		t.x=_x;
		t.y=_y;
		return true;
	}

void DrawPlayer(){
	TransparentBlt(bufferDC,player_tank->x,player_tank->y-offset_y,64,64,player_tankDC,player_tank->face*64,player_tank->step*64,64,64,RGB(255,255,255));
	TransparentBlt(bufferDC,player_tank->x,player_tank->y-offset_y,64,64,armorDC,player_tank->gun_face*64,player_tank->armor*64,64,64,RGB(255,255,255));
}

void DrawEnemy(){
	tagPOINT poly[5];
	for(list<BaseTank*>::iterator iter_tank=enemy_tank.begin();iter_tank!=enemy_tank.end();iter_tank++){
		BaseTank* t=*iter_tank;
		if (t->activate){
			TransparentBlt(bufferDC,t->x,t->y-offset_y,64,64,enemy_tankDC,t->face*64,(t->no*3+t->step)*64,64,64,RGB(255,255,255));
			TransparentBlt(bufferDC,t->x,t->y-offset_y,64,64,armorDC,t->gun_face*64,(t->armor+5)*64,64,64,RGB(255,255,255));
			
			int len=((double)t->hp/(double)t->maxhp)*(64-10*2);
			poly[0].x=t->x+10;
			poly[0].y=t->y-offset_y-8;
			poly[1].x=t->x+10+(64-10*2);
			poly[1].y=t->y-offset_y-8;
			poly[2].x=t->x+10+(64-10*2);
			poly[2].y=t->y-offset_y-8+5;
			poly[3].x=t->x+10;
			poly[3].y=t->y-offset_y-8+5;
			poly[4].x=t->x+10;
			poly[4].y=t->y-offset_y-8;
			//画hp
			SelectObject(bufferDC,hPen_Border); //无边框
			SelectObject(bufferDC,hBru_hp);  //灰色填充
			Rectangle(bufferDC,t->x+10,t->y-offset_y-8,t->x+10+len,t->y-offset_y-8+5);

			SelectObject(bufferDC,hPen_black);
			Polyline(bufferDC,poly,5);
		}
	}
}


void OpenFireCharge(BaseTank&t,double charge,double chargemax){
		Bullet* b=new Bullet();
		b->owner=t.owner;
		if(b->owner==0)
		if (!keydown_f4)
		{	
			PLAYA(OPEN_FIRE);
		}
		b->id=10;
		b->face=t.gun_face;
		b->speed=bullet_attr[b->id][0]*(1+charge/chargemax*2);
		b->attack = (bullet_attr[b->id][1] + t.attack + t.attack_temp)*(1 + charge / chargemax * 4);
		b->hp=bullet_attr[b->id][4]*(1+charge/chargemax*10);
		b->offset_w=bullet_attr[b->id][5];
		b->offset_h=bullet_attr[b->id][6];
	
		switch (t.gun_face)
		{
			case DOWN:
				b->wide=bullet_attr[b->id][2];
				b->high=bullet_attr[b->id][3];
				b->x=t.x+32-b->high/2;
				b->y=t.y+64-b->offset_w;
			break;
			case LEFT:
				b->wide=bullet_attr[b->id][3];
				b->high=bullet_attr[b->id][2];
				b->x=t.x-b->wide+b->offset_w;
				b->y=t.y+32-b->high/2-b->offset_h;
			break;
			case UP:
				b->wide=bullet_attr[b->id][2];
				b->high=bullet_attr[b->id][3];
				b->x=t.x+32-b->high/2;
				b->y=t.y-b->wide+b->offset_w;;
			break;
			case RIGHT:
				b->wide=bullet_attr[b->id][3];
				b->high=bullet_attr[b->id][2];
				b->x=t.x+64-b->offset_w;
				b->y=t.y+32-b->high/2-b->offset_h;
			break;
		}
		if (charge>chargemax*2/3) b->id=10;
		else if(charge>chargemax*1/3) b->id=11;
		else b->id=12;
		bullet.push_back(b);
}

// 
void DrawCharge(){
			BaseTank* t=player_tank;
			
			if (++charge>=chargemax){
				charge=chargemax;
			}

			
			int len=((double)charge/(double)chargemax)*(64-10*2);
			tagPOINT poly[5];

			poly[0].x=t->x+10;
			poly[0].y=t->y-offset_y+64;
			poly[1].x=t->x+10+(64-10*2);
			poly[1].y=t->y-offset_y+64;
			poly[2].x=t->x+10+(64-10*2);
			poly[2].y=t->y-offset_y+64+5;
			poly[3].x=t->x+10;
			poly[3].y=t->y-offset_y+64+5;
			poly[4].x=t->x+10;
			poly[4].y=t->y-offset_y+64;
			//画hp
			SelectObject(bufferDC,hPen_Border); //无边框
			SelectObject(bufferDC,hBru_charge);  //灰色填充
			Rectangle(bufferDC,t->x+10,t->y-offset_y+64,t->x+10+len,t->y-offset_y+64+5);

			SelectObject(bufferDC,hPen_black);
			Polyline(bufferDC,poly,5);
}
void DrawBullet(){
		for(list<Bullet*>::iterator iter_bullet=bullet.begin();iter_bullet!=bullet.end();iter_bullet++){
			Bullet* b=*iter_bullet;
			TransparentBlt(bufferDC,b->x,b->y-offset_y,64,64,bulletDC,b->face*64,b->id*64,64,64,RGB(255,255,255));	
		}
}


//按下J键或者AI控制
void OpenFire(BaseTank& t){
	if (t.attack_frame>0)return;
	else{
		t.attack_frame=t.attack_cd;
		Bullet* b=new Bullet();
		b->owner=t.owner;
		if(b->owner==0){
		    if (!keydown_f4)
		    {
		    	PLAYA(OPEN_FIRE);
			}
		}
			
		b->id=t.armor;

		b->face=t.gun_face;
		b->speed=bullet_attr[b->id][0];
		b->attack=bullet_attr[b->id][1]+t.attack+t.attack_temp;
		b->hp=bullet_attr[b->id][4];
		b->offset_w=bullet_attr[b->id][5];
		b->offset_h=bullet_attr[b->id][6];


		switch (t.gun_face)
		{
			case DOWN:
				b->wide=bullet_attr[b->id][2];
				b->high=bullet_attr[b->id][3];
				b->x=t.x+32-b->high/2;
				b->y=t.y+64-b->offset_w;
			break;
			case LEFT:
				b->wide=bullet_attr[b->id][3];
				b->high=bullet_attr[b->id][2];
				b->x=t.x-b->wide+b->offset_w;
				b->y=t.y+32-b->high/2-b->offset_h;
			break;
			case UP:
				b->wide=bullet_attr[b->id][2];
				b->high=bullet_attr[b->id][3];
				b->x=t.x+32-b->high/2;
				b->y=t.y-b->wide+b->offset_w;;
			break;
			case RIGHT:
				b->wide=bullet_attr[b->id][3];
				b->high=bullet_attr[b->id][2];
				b->x=t.x+64-b->offset_w;
				b->y=t.y+32-b->high/2-b->offset_h;
			break;
		}
		bullet.push_back(b);
	}
}

//按下k键盘发射激光
void OpenLaser(BaseTank& play_tank){
	//能量大于20才能发射激光，每次发射损失20点能量
	
		//
		//坦克的坐标
		int x=player_tank->x;
		int y=player_tank->y;
	
		bool isHit=false;

		switch (play_tank.gun_face)
		{
		case DOWN:
			laserxs=x+32;
			laserxe=x+32;
			laserys=y+64-offset_y;
			
			for (list<Barrier*>::iterator iter=object.begin();iter!=object.end();iter++)//顺时针遍历障碍物
			{
				Barrier &b=**iter;

				if (b.id>0&&b.id<10)
				{
					//对障碍物的伤害
					if (b.x<=laserxs && b.x+64>=laserxs)//竖直范围内
					{
						if (b.y+10>=laserys)//障碍物在坦克下方
						{
							//草
							if (b.id==GRASS&&b.state==NORMAL_STATE)
							{
								b.state=SHOOT_STATE;
								b.life-=150;
							}
							//
							if (b.id==TREE || b.id==WALL || b.id==STONE || b.id==IRON || b.id==BUCKET||b.id==BASTION)//只要检测有就跳出，即为第一个
							{															
								laserye=b.y;
								b.life-=100;
								if (b.life>=100&&b.id==TREE&&b.state==NORMAL_STATE)
								{
									b.state=SHOOT_STATE;
								}
								/*
								if (b.id==BUCKET)
								{
									OpenExplode(6,laserxe,laserye+offset_y,PLAYER_BOMB,BARRIER_NONE);
								}else
								{*/
									OpenExplode(6,laserxe,laserye+offset_y,PLAYER_BOMB,b.id);
								/*}
								
								if (b.id==BUCKET)
								{
									if (b.life<=0)
									{
										OpenExplode(12,b.x+32,b.y+32+offset_y,OBJECT_BOMB,BUCKET);
									}
								}*/
								isHit=true;
								break;																													
							}		
						}
										
						
					}
				}
			}
			
			if (!isHit)//飞出地图
			{
				laserye=GAME_H+offset_y;
			}
		
			break;

		case UP:
			laserxs=play_tank.x+32;
			laserxe=play_tank.x+32;
			laserys=play_tank.y-offset_y;
			for (list<Barrier*>::iterator iter=--object.end();iter!=object.begin();iter--)//逆时针遍历障碍物
			{
				Barrier &b=**iter;

				if (b.id>0&&b.id<10)
				{

					if (b.x<=laserxs && b.x+64>=laserxs)//竖直范围内
					{
						if (b.y-10<=laserys)//障碍物在坦克上方
						{
							//草
							if (b.id==GRASS&&b.state==NORMAL_STATE)
							{
								b.state=SHOOT_STATE;
								b.life-=150;
							}
							//
							if (b.id==TREE || b.id==WALL || b.id==STONE || b.id==IRON || b.id==BUCKET||b.id==BASTION)//只要检测有就跳出，即为第一个
							{															
								laserye=b.y+64;
								b.life-=100;
								if (b.life>=100&&b.id==TREE&&b.state==NORMAL_STATE)
								{
									b.state=SHOOT_STATE;
								}/*
								if (b.id==BUCKET)
								{
									OpenExplode(6,laserxe,laserye+offset_y,PLAYER_BOMB,BARRIER_NONE);
								}else
								{*/
									OpenExplode(6,laserxe,laserye+offset_y,PLAYER_BOMB,b.id);
								/*}
								if (b.id==BUCKET)
								{
									if (b.life<=0)
									{
										OpenExplode(12,b.x+32,b.y+32+offset_y,OBJECT_BOMB,BUCKET);
									}
								}*/
								isHit=true;
								break;																														
							}		
						}


					}
				}
			}
			if (!isHit)//飞出地图
			{
				laserye=-offset_y;
			}
		
			break;
		case LEFT:
			laserxs=play_tank.x;
			laserys=play_tank.y+32-8-offset_y;
			laserye=play_tank.y+32-8-offset_y;
			for (list<Barrier*>::iterator iter=--object.end();iter!=object.begin();iter--)//逆时针遍历障碍物
			{
				Barrier &b=**iter;

				if (b.id>0&&b.id<10)
				{

					if (b.y<=laserys && b.y+64>=laserys)//水平范围内
					{
						if (b.x-10<=laserxs)//障碍物在坦克左边
						{
							//草
							if (b.id==GRASS&&b.state==NORMAL_STATE)
							{
								b.state=SHOOT_STATE;
								b.life-=100;
							}
							//
							if (b.id==TREE || b.id==WALL || b.id==STONE || b.id==IRON || b.id==BUCKET||b.id==BASTION)//只要检测有就跳出，即为第一个
							{															
								laserxe=b.x+64;
								b.life-=150;
								if (b.life>=100&&b.id==TREE&&b.state==NORMAL_STATE)
								{
									b.state=SHOOT_STATE;
								}/*
								if (b.id==BUCKET)
								{
									OpenExplode(6,laserxe,laserye+offset_y,PLAYER_BOMB,BARRIER_NONE);
								}else
								{*/
									OpenExplode(6,laserxe,laserye+offset_y,PLAYER_BOMB,b.id);
								/*}
								if (b.id==BUCKET)
								{
									if (b.life<=0)
									{
										OpenExplode(12,b.x+32,b.y+32+offset_y,OBJECT_BOMB,BUCKET);
									}
								}*/
								isHit=true;
								break;																														
							}		
						}


					}
				}
			}
			if (!isHit)//飞出地图
			{
				laserxe=offset_x;
			}
		
			break;
		case RIGHT:
			laserxs=play_tank.x+64;
			laserys=play_tank.y+32-8-offset_y;
			laserye=play_tank.y+32-8-offset_y;
			for (list<Barrier*>::iterator iter=object.begin();iter!=object.end();iter++)//顺时针遍历障碍物
			{
				Barrier &b=**iter;

				if (b.id>0&&b.id<10)
				{

					if (b.y<=laserys && b.y+64>=laserys)//水平范围内
					{
						if (b.x+10>=laserxs)//障碍物在坦克右边
						{
							//草
							if (b.id==GRASS&&b.state==NORMAL_STATE)
							{
								b.state=SHOOT_STATE;
								b.life-=100;
							}
							//
							if (b.id==TREE || b.id==WALL || b.id==STONE || b.id==IRON || b.id==BUCKET||b.id==BASTION)//只要检测有就跳出，即为第一个
							{															
								laserxe=b.x;
								b.life-=150;
								if (b.life>=100&&b.id==TREE&&b.state==NORMAL_STATE)
								{
									b.state=SHOOT_STATE;
								}/*
								if (b.id==BUCKET)
								{
									OpenExplode(6,laserxe,laserye+offset_y,PLAYER_BOMB,BARRIER_NONE);
								}else
								{*/
									OpenExplode(6,laserxe,laserye+offset_y,PLAYER_BOMB,b.id);
								/*}
								if (b.id==BUCKET)
								{
									if (b.life<=0)
									{
										OpenExplode(12,b.x+32,b.y+32+offset_y,OBJECT_BOMB,BUCKET);
									}
								}*/
								isHit=true;
								break;																														
							}		
						}


					}
				}
			}
			if (!isHit)//飞出地图
			{
				laserxe=GAME_W+offset_x;
			}
			
			break;
		

		default:
			break;
		}
		//处理矩形的四个角
		int temp=0;
		if (laserxe<laserxs)
		{
			temp=laserxe;
			laserxe=laserxs;
			laserxs=temp;
		}else if (laserye<laserys)
		{
			temp=laserye;
			laserye=laserys;
			laserys=temp;
		}
		laserys+=offset_y;
		laserye+=offset_y;
		//对敌人坦克的伤害
		for (list<BaseTank*>::iterator iter=enemy_tank.begin();iter!=enemy_tank.end();iter++)
		{
			BaseTank & b=**iter;
			if (( (b.x+32)>=laserxs  && (b.x+32)<=laserxe && b.y<=laserys && (b.y+64)>=laserye )  || (b.x<=laserxs && (b.x+64)>=laserxe && (b.y+32)>=laserys && (b.y+32)<=laserye ))
			{
				b.hp-=100;
			}
		}
	
}

void ScreenMove(){
	if(player_tank->x-offset_x>500&&player_tank->face==RIGHT)
	{
		offset_x+=(((player_tank->x-offset_x-500))/150)*(player_tank->speed+player_tank->speed_temp);
		if (offset_x>GAME_TOTW-GAME_W)
			offset_x=GAME_TOTW-GAME_W;
	}

	if((GAME_W-(player_tank->x-offset_x))>866&&player_tank->face==LEFT)
	{
		offset_x-=((GAME_W-(player_tank->x-offset_x))-866)/150*(player_tank->speed+player_tank->speed_temp);
		if(offset_x<0)
			offset_x=0;
	}
}
void TankBarrierCheck(){
	for(list<BaseTank*>::iterator iter_tank=enemy_tank.begin();iter_tank!=enemy_tank.end();iter_tank++){
		BaseTank* et=*iter_tank;
		if ((et->x>=offset_x-100)&&(et->x<=offset_x+GAME_W+400)){
			et->activate=true;
		}else et->activate=false;
	}
	for(list<Barrier*>::iterator iter_barrier=object.begin();iter_barrier!=object.end();iter_barrier++){
		Barrier* b=*iter_barrier;
		if ((b->x>=offset_x-100)&&(b->x<=offset_x+GAME_W+400)){
			b->activate=true;
		}else b->activate=false;
	}
}

//产生爆炸
void OpenExplode(int power, int  x, int y, int owner, int id){
	if (owner != ENERMY_BOMB)
	{
		if (id == BUCKET)
		{
			shaking = 50;
			if (!keydown_f4){
				PLAYA(OIL_EXPLODE);
			}
		}
		else
			if (id == WALL){
				if (!keydown_f4)
					PLAYA(WALL_DESTROY);
			}
			else
				if (id == IRON){
					if (!keydown_f4)
						PLAYA(IRON_SOUND);
				}
				else
					if (id == STONE){
						if (!keydown_f4)
							PLAYA(HIT_STONE);
					}
					else

						if (id == TREE){
							if (!keydown_f4)
								PLAYA(HIT_STONE);
						}
						else
							if (!keydown_f4){
								PLAYA(BULLET_EXPLODE);
							}

	}

	bomb.push_back(new Bomb(power, x, y - offset_y, owner));
}


void DrawStateMap()
{
	//绘制玩家HP
	hpX1=93.0;
	hpY1=25.0;
	hpY2=45.0;
	fullhpX=141;

	//hpX2=111.0+50.6;
	SelectObject(bufferDC2,hBruWhite);
	Rectangle(bufferDC2,hpX1,hpY1,hpX1+fullhpX,hpY2);
	hpX2=hpX1+(((double)(player_tank->hp)/(double)(player_tank->maxhp))*fullhpX);
	SelectObject(bufferDC2,hBruRed);
	Rectangle(bufferDC2,hpX1,hpY1,hpX2,hpY2);

	//绘制玩家MP
	mpX1=93.0;
	mpY1=45.5;
	mpY2=67.0;
	fullmpX=139.0;

	//mpX2=111.0+90.5;

	SelectObject(bufferDC2,hBruWhite);
	Rectangle(bufferDC2,mpX1,mpY1,mpX1+fullmpX,mpY2);
	mpX2=mpX1+(((double)(player_tank->mp)/(double)(player_tank->maxmp))*fullmpX);
	SelectObject(bufferDC2,hBruBlue);
	Rectangle(bufferDC2,mpX1,mpY1,mpX2,mpY2);
	//TransparentBlt(bufferDC2,0,1,332,110,player_state_mapDC,0,0,332,110,RGB(255,255,255));

	//绘制玩家EXP
	expX1=76.0;
	expY1=67.0;
	expY2=87.0;
	fullexpX=158.0;

	

	SelectObject(bufferDC2,hBruWhite);
	Rectangle(bufferDC2,expX1,expY1,expX1+fullexpX,expY2);
	expX2=expX1+(((double)(player_tank->exp)/(double)(lvexp[player_tank->lv]))*fullexpX);
	SelectObject(bufferDC2,hBruYellow);
	Rectangle(bufferDC2,expX1,expY1,expX2,expY2);
	TransparentBlt(bufferDC2,0,1,286,96,player_state_mapDC,0,0,286,96,RGB(255,255,255));
	TransparentBlt(bufferDC2,54,70,20,15,lvDC,(player_tank->lv-1)*37,0,37,26,RGB(255,255,255));

}


void JudgeThingB(Barrier* b)
{
	if(((b)->old_id==TREE||(b)->old_id==WALL||(b)->old_id==STONE))
	{
		//产生道具的几率
		int n;

		//产生道具的类型

		int k=rand()%5;
		if((b)->old_id==WALL)
			n=rand()%8;
		else if((b)->old_id==TREE)
			n=rand()%5;
		else 
			n=rand()%3;
		if(n==0)
			thing.push_back(new Thing(k,(b)->x,(b)->y+offset_y,2000,3000));

	}
}


void JudgeThingE(BaseTank* b){
	//产生道具的几率
	int n=rand()%(10-((b)->no));
	//产生道具的类型
	int k=rand()%5;
	int j=rand()%(10-(b->no));
	if(n==0)
		thing.push_back(new Thing(k,(b)->x,(b)->y,2000,2000));
	if(n!=0&&j==0)
		thing.push_back(new Thing((b->no)+10,(b)->x,(b)->y,2000,2000));

}

void HandleThing()
{
	for(list<Thing*>::iterator b=thing.begin();b!=thing.end();)
	{

		bool erase=false;   //判断是否删除该元素

		if((*b)->time>0)
		{
			if((*b)->id>=10&&(*b)->id<=14)
				TransparentBlt(bufferDC,(*b)->x,(*b)->y-offset_y+10,64,64,armorDC,64,((*b)->id-10+5)*64,64,64,RGB(255,255,255));
			else
			{
				TransparentBlt(bufferDC,(*b)->x,(*b)->y-offset_y,64,64,thingDC,(*b)->id*64,0,64,64,RGB(255,255,255));
			}
			
			--((*b)->time);
		}
		if(player_tank->face==RIGHT&&abs(((player_tank->x)-((*b)->x)))<43&&abs(((player_tank->y)-((*b)->y)))<58&&(*b)->time>0)
		{
			if(!keydown_f4)
			PLAYA(GET_THING);
			switch ((*b)->id)
			{
			case ADD_SPEED:
				player_tank->speed_temp+=1.5;
				break;
			case ADD_POWER:
				player_tank->attack_temp+=40;
				break;
			case ADD_HP:
				{
					player_tank->hp+=(int)(0.3*player_tank->maxhp);
					if(player_tank->hp>player_tank->maxhp)
						player_tank->hp=player_tank->maxhp;
				}
				break;
			 case ADD_MP:
			{
				player_tank->mp+=(int)(0.3*player_tank->maxmp);
				if(player_tank->mp>player_tank->maxmp)
					player_tank->mp=player_tank->maxmp;
				}
				break;  
			case CUT_HP:
				player_tank->hp-=(int)(0.15*player_tank->maxhp);
				break;
			case ARMOR1:
				player_tank->armor=0;
				break;
			case ARMOR2:
				player_tank->armor=1;
				break;
			case ARMOR3:
				player_tank->armor=2;
				break;
			case ARMOR4:
				player_tank->armor=3;
				break;
			case ARMOR5:
				player_tank->armor=4;
				break;
			}
			(*b)->time=-10;    //处理道具消失,并确认玩家已经拿到道具
		}else
		if(player_tank->face==LEFT&&abs(((player_tank->x)-((*b)->x)))<39&&abs(((player_tank->y)-((*b)->y)))<58&&(*b)->time>0)
		{
			if(!keydown_f4)
			PLAYA(GET_THING);
			switch ((*b)->id)
			{
			case ADD_SPEED:
				player_tank->speed_temp+=1.5;
				break;
			case ADD_POWER:
				player_tank->attack_temp+=40;
				break;
			case ADD_HP:
				{
					player_tank->hp+=(int)(0.3*player_tank->maxhp);
					if(player_tank->hp>player_tank->maxhp)
						player_tank->hp=player_tank->maxhp;
				}
				break;
			 case ADD_MP:
			{
				player_tank->mp+=(int)(0.3*player_tank->maxmp);
				if(player_tank->mp>player_tank->maxmp)
					player_tank->mp=player_tank->maxmp;
				}
				break;  
			case CUT_HP:
				player_tank->hp-=(int)(0.15*player_tank->maxhp);
				break;
			case ARMOR1:
				player_tank->armor=0;
				break;
			case ARMOR2:
				player_tank->armor=1;
				break;
			case ARMOR3:
				player_tank->armor=2;
				break;
			case ARMOR4:
				player_tank->armor=3;
				break;
			case ARMOR5:
				player_tank->armor=4;
				break;


			}
			(*b)->time=-10;    //处理道具消失,并确认玩家已经拿到道具
		}
		else
		if(player_tank->face==UP&&abs(((player_tank->y)-((*b)->y)))<49&&abs(((player_tank->x)-((*b)->x)))<58&&(*b)->time>0)
		{
			if(!keydown_f4)
			PLAYA(GET_THING);
			switch ((*b)->id)
			{
			case ADD_SPEED:
				player_tank->speed_temp+=1.5;
				break;
			case ADD_POWER:
				player_tank->attack_temp+=40;
				break;
			case ADD_HP:
				{
					player_tank->hp+=(int)(0.3*player_tank->maxhp);
					if(player_tank->hp>player_tank->maxhp)
						player_tank->hp=player_tank->maxhp;
				}
				break;
			 case ADD_MP:
			{
				player_tank->mp+=(int)(0.3*player_tank->maxmp);
				if(player_tank->mp>player_tank->maxmp)
					player_tank->mp=player_tank->maxmp;
				}
				break;  
				break;
			case CUT_HP:
				player_tank->hp-=(int)(0.15*player_tank->maxhp);
				break;
			case ARMOR1:
				player_tank->armor=0;
				break;
			case ARMOR2:
				player_tank->armor=1;
				break;
			case ARMOR3:
				player_tank->armor=2;
				break;
			case ARMOR4:
				player_tank->armor=3;
				break;
			case ARMOR5:
				player_tank->armor=4;
				break;
			}
			(*b)->time=-10;    //处理道具消失,并确认玩家已经拿到道具
		}
		else
		if(player_tank->face==DOWN&&abs(((player_tank->y)-((*b)->y)))<59&&abs(((player_tank->x)-((*b)->x)))<58&&(*b)->time>0)
		{
			if(!keydown_f4)
			PLAYA(GET_THING);
			switch ((*b)->id)
			{
			case ADD_SPEED:
				player_tank->speed_temp+=1.5;
				break;
			case ADD_POWER:
				player_tank->attack_temp+=40;
				break;
			case ADD_HP:
				{
					player_tank->hp+=(int)(0.3*player_tank->maxhp);
					if(player_tank->hp>player_tank->maxhp)
						player_tank->hp=player_tank->maxhp;
				}
				break;
			 case ADD_MP:
			{
				player_tank->mp+=(int)(0.3*player_tank->maxmp);
				if(player_tank->mp>player_tank->maxmp)
					player_tank->mp=player_tank->maxmp;
				}
				break;  
				break;
			case CUT_HP:
				player_tank->hp-=(int)(0.15*player_tank->maxhp);
				break;
			case ARMOR1:
				player_tank->armor=0;
				break;
			case ARMOR2:
				player_tank->armor=1;
				break;
			case ARMOR3:
				player_tank->armor=2;
				break;
			case ARMOR4:
				player_tank->armor=3;
				break;
			case ARMOR5:
				player_tank->armor=4;
				break;
			}
			(*b)->time=-10;    //处理道具消失,并确认玩家已经拿到道具
		}


		if((*b)->time==-10)                //道具作用时间减少
		{
			(*b)->last-=1;
			if((*b)->last<0)
				(*b)->last=0;
		}							


		if((*b)->time==-10&&(*b)->last==0)            //道具作用消失
		{
			switch ((*b)->id)
			{
			case ADD_SPEED:
				player_tank->speed_temp-=1.5;
				break;
			case ADD_POWER:
				player_tank->attack_temp-=40;
				break;
			case ADD_HP:
				break;
			case ADD_MP:
				break;
			case CUT_HP:
				break;	
			}
			erase=true;
		}

		if(erase==true)					//判断是否删除该元素
		{
			b=thing.erase(b);
		}
		else if (erase==false)
		{
			b++;
		}
	}
}

//爆炸时震屏
void ShakeScreen()
{
	int n = rand()%8;
	switch (n)
	{
	case 0:
		bgx=3.0;
		break;
	case 1:
		bgx=-3.0;
		break;
	case 2:
		bgy=3.0;
		break;
	case 3:
		bgy=-3.0;
		break;
	case 4:
		{
			bgx=1.2;
			bgy=1.2;
		}
		break;
	case 5:
		{
			bgx=1.2;
			bgy=1.2;
		}
		break;
	case 6:
		{
			bgx=-1.2;
			bgy=-1.2;
		}
		break;
	case 7:
		{
			bgx=-1.2;
			bgy=1.2;
		}
		break;

	default:
		break;
	}
}


void DrawLaser(int x1,int y1,int x2,int y2)
{
	if (k_down)
	{
		if (player_tank->mp >=20 )
		{
			if(!keydown_f4)
			PLAYA(LASER_SOUND);
			y1-=offset_y+3;
			y2-=offset_y+3;
			SelectObject(bufferDC,hBru_Laser);
			SelectObject(bufferDC,hPen_laser);
			if ((x2-x1)>(y2-y1))
			{
				y1-=2;
				y2+=2;
			}else
			{
				x1-=2;
				x2+=2;
			}
			Rectangle(bufferDC,x1,y1,x2,y2);
		}
	}else
	{
		return;
	}
	
}

void ProtonCollide(){
	if (proton_collider--%5==0){
		int x=rand()%GAME_W+offset_x;
		int y=rand()%(GAME_H-192);
		OpenExplode(12,x,y,PLAYER_BOMB,BUCKET);
		shaking=50;
	}
}

void DrawLevelUp()
{
	if (LevelUping == true)
	{
		if (!keydown_f4)
			PLAYB(LEVEL_UP_SOUND);
		TransparentBlt(bufferDC2, 5, 576 + 96 + 10, 329, 96, attrDC, 0, 0, 329, 96, RGB(255, 255, 255));
		if (uping > 0)
			TransparentBlt(bufferDC2, 350, 100, 567, 452, level_upDC, 0, 0, 567, 452, RGB(255, 255, 255));
	}
	if (LevelUping == false)
	{
		if (AddAttring == 1 && adding > 0)
			TransparentBlt(bufferDC2, player_tank->x - 25 - offset_x, player_tank->y + 15, 83, 96, adding_attrDC, 0, 0, 83, 96, RGB(255, 255, 255));
		if (AddAttring == 2 && adding > 0)
			TransparentBlt(bufferDC2, player_tank->x - 18 - offset_x, player_tank->y + 15, 83, 96, adding_attrDC, 83, 0, 83, 96, RGB(255, 255, 255));
		if (AddAttring == 3 && adding > 0)
			TransparentBlt(bufferDC2, player_tank->x - 22 - offset_x, player_tank->y + 15, 83, 96, adding_attrDC, 166, 0, 83, 96, RGB(255, 255, 255));
		if (AddAttring == 4 && adding > 0)
			TransparentBlt(bufferDC2, player_tank->x - offset_x, player_tank->y + 15, 83, 96, adding_attrDC, 249, 0, 83, 96, RGB(255, 255, 255));
	}
}