//仅编译一次
#pragma once
//多媒体库
#pragma comment(lib, "winmm")
//API
#include <Windows.h>
//系统时间
#include <time.h>
//字符串库
#include <string>
//文件流
#include <fstream>
//顺序容器
#include <vector>
#include <list>
//资源头文件
#include "resource.h"
//坦克类
#include "BaseTank.h"

//导弹类
#include "Missile.h"
//子弹类
#include "Bullet.h"
//火花类
#include "Bomb.h"
//物体类
#include "Object.h"
//道具类
#include "Thing.h"
//命名空间
using namespace std;


//沙子和冰
#define ICE 0
#define ROAD 1
#define BLANK 3
#define SAND1 4
#define SAND2 5
#define SAND3 6
#define SAND4 7
#define SAND5 8
#define SAND6 9
#define SAND7 10
#define SAND8 11
#define SAND9 12
#define SAND10 13
#define SAND11 14

//游戏窗口宽和高
#define GAME_TOTW 64*40
#define GAME_W  1366
#define GAME_H  768
#define TANK_WIDE 64
#define TANK_HIGH 64
#define BULLET_WIDE 25
#define BULLET_HIGH 40
//游戏定时器
#define GAME_ID 1
#define GAME_TIME 15
//按键映射
#define KEYDOWN(key) GetAsyncKeyState(key)&0x8000
#define KEYUP(key) !(GetAsyncKeyState(key)&0x8000)
//播放音效
#define PLAYA(MUSIC) PlaySound(MAKEINTRESOURCE(MUSIC),GetModuleHandle(NULL),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT)
#define PLAYB(MUSIC) PlaySound(MAKEINTRESOURCE(MUSIC),GetModuleHandle(NULL),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT|SND_NOSTOP)

//游戏状态
#define GAME 0
#define PAUSE 1
#define GAMEOVER 2
#define WIN 3
#define NEXTSTAGE 4
#define EDIT 5
#define GAMESTART 6
#define GAMESELECT 7
#define GAMEWIN 8
//敌人坦克种类
#define NORMAL_TANK 0
#define SPEED_TANK 1
#define POWER_TANK 2
#define ARMOR_TANK 3
//道具种类
#define NONE 4
#define LIFE 0
#define POWER 1
#define SPEED 2
#define WEAPON 3

//道具种类
#define ADD_SPEED 0
#define ADD_POWER 1
#define ADD_HP 2
#define ADD_MP 3
#define CUT_HP 4
//玩家坦克产生的爆炸还是地方差生的，或者是物体爆炸
#define PLAYER_BOMB 0
#define ENERMY_BOMB 1
#define OBJECT_BOMB 2

#define ARMOR1 10
#define ARMOR2 11
#define ARMOR3 12
#define ARMOR4 13
#define ARMOR5 14

//敌人坦克代号
#define TANK  99
//过程函数
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//游戏开始
void GameStart();
//游戏循环
void Game();
//按键判断
void Key();
//画背景
void DrawBG();
//画游戏
void DrawGame();
//输出到窗口
void PrintToScreen();
//画地图块
void DrawBarrier();
//画铁钉
void DrawPiton();
//处理和画玩家子弹
void PlayerBullet();
//画爆炸火花
void DrawBomb();
//发射导弹，对可视范围内最远的坦克进攻
void OpenMissile(BaseTank&);
//绘制导弹
void DrawMissile();
//初始化
void DataInit();
//子弹击中砖块
bool BulletHitBlock(Bullet&);
//坦克碰到砖块
bool TankHitBlock(BaseTank&);
//子弹击中坦克
bool BulletHitTank(Bullet&,BaseTank&);
//坦克碰到坦克
bool TankHitTank(BaseTank&,BaseTank&);
//子弹击中子弹
bool BulletHitBullet(Bullet&,Bullet&);
//处理和画敌人坦克
void EnemyTank();
//处理和画敌人子弹
void EnemyBullet();
//处理和画道具
void Item();
//地图编辑
void Edit();
//地图保存
void Save();
//地图载入
void Load();
//载入障碍物地图
void AssignBarrierMap();
//移动坦克
bool Move(BaseTank&,int);
//碰撞检测
bool Collide(int,int,int,int,int,int,int,int);
//画自己坦克
void DrawPlayer();
//更新坦克状态
void PlayerTankStep(BaseTank&);
//开炮
void OpenFire(BaseTank&);
//开激光
void OpenLaser(BaseTank&);
//发射导弹，对可视范围内最近的坦克进攻
void OpenMissile(BaseTank&);
//子弹
void BulletMove();
//屏幕移动
void ScreenMove();
//爆炸产生
void OpenExplode(int,int,int,int,int);
//画子弹
void DrawBullet();
//检测敌方坦克是否在视野区
void TankBarrierCheck();
//更新敌方坦克状态
void EnemyTankStep();
//绘制敌人坦克
void DrawEnemy();
//敌人坦克智能
void EnemyAI(BaseTank&);
//绘制玩家坦克状态栏
void DrawStateMap();


//处理道具
void HandleThing();
//屏幕震动函数
void ShakeScreen();

void DrawLaser(int,int,int,int);

void DrawCharge();

void OpenFireCharge(BaseTank&,double,double);


void ProtonCollide();

void DrawStart();

void DrawIntroduce();

void DrawSelect();

void DrawCredits();


void DrawLevelUp();

void DrawDeath();