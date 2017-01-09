//������һ��
#pragma once
//��ý���
#pragma comment(lib, "winmm")
//API
#include <Windows.h>
//ϵͳʱ��
#include <time.h>
//�ַ�����
#include <string>
//�ļ���
#include <fstream>
//˳������
#include <vector>
#include <list>
//��Դͷ�ļ�
#include "resource.h"
//̹����
#include "BaseTank.h"

//������
#include "Missile.h"
//�ӵ���
#include "Bullet.h"
//����
#include "Bomb.h"
//������
#include "Object.h"
//������
#include "Thing.h"
//�����ռ�
using namespace std;


//ɳ�Ӻͱ�
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

//��Ϸ���ڿ�͸�
#define GAME_TOTW 64*40
#define GAME_W  1366
#define GAME_H  768
#define TANK_WIDE 64
#define TANK_HIGH 64
#define BULLET_WIDE 25
#define BULLET_HIGH 40
//��Ϸ��ʱ��
#define GAME_ID 1
#define GAME_TIME 15
//����ӳ��
#define KEYDOWN(key) GetAsyncKeyState(key)&0x8000
#define KEYUP(key) !(GetAsyncKeyState(key)&0x8000)
//������Ч
#define PLAYA(MUSIC) PlaySound(MAKEINTRESOURCE(MUSIC),GetModuleHandle(NULL),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT)
#define PLAYB(MUSIC) PlaySound(MAKEINTRESOURCE(MUSIC),GetModuleHandle(NULL),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT|SND_NOSTOP)

//��Ϸ״̬
#define GAME 0
#define PAUSE 1
#define GAMEOVER 2
#define WIN 3
#define NEXTSTAGE 4
#define EDIT 5
#define GAMESTART 6
#define GAMESELECT 7
#define GAMEWIN 8
//����̹������
#define NORMAL_TANK 0
#define SPEED_TANK 1
#define POWER_TANK 2
#define ARMOR_TANK 3
//��������
#define NONE 4
#define LIFE 0
#define POWER 1
#define SPEED 2
#define WEAPON 3

//��������
#define ADD_SPEED 0
#define ADD_POWER 1
#define ADD_HP 2
#define ADD_MP 3
#define CUT_HP 4
//���̹�˲����ı�ը���ǵط������ģ����������屬ը
#define PLAYER_BOMB 0
#define ENERMY_BOMB 1
#define OBJECT_BOMB 2

#define ARMOR1 10
#define ARMOR2 11
#define ARMOR3 12
#define ARMOR4 13
#define ARMOR5 14

//����̹�˴���
#define TANK  99
//���̺���
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//��Ϸ��ʼ
void GameStart();
//��Ϸѭ��
void Game();
//�����ж�
void Key();
//������
void DrawBG();
//����Ϸ
void DrawGame();
//���������
void PrintToScreen();
//����ͼ��
void DrawBarrier();
//������
void DrawPiton();
//����ͻ�����ӵ�
void PlayerBullet();
//����ը��
void DrawBomb();
//���䵼�����Կ��ӷ�Χ����Զ��̹�˽���
void OpenMissile(BaseTank&);
//���Ƶ���
void DrawMissile();
//��ʼ��
void DataInit();
//�ӵ�����ש��
bool BulletHitBlock(Bullet&);
//̹������ש��
bool TankHitBlock(BaseTank&);
//�ӵ�����̹��
bool BulletHitTank(Bullet&,BaseTank&);
//̹������̹��
bool TankHitTank(BaseTank&,BaseTank&);
//�ӵ������ӵ�
bool BulletHitBullet(Bullet&,Bullet&);
//����ͻ�����̹��
void EnemyTank();
//����ͻ������ӵ�
void EnemyBullet();
//����ͻ�����
void Item();
//��ͼ�༭
void Edit();
//��ͼ����
void Save();
//��ͼ����
void Load();
//�����ϰ����ͼ
void AssignBarrierMap();
//�ƶ�̹��
bool Move(BaseTank&,int);
//��ײ���
bool Collide(int,int,int,int,int,int,int,int);
//���Լ�̹��
void DrawPlayer();
//����̹��״̬
void PlayerTankStep(BaseTank&);
//����
void OpenFire(BaseTank&);
//������
void OpenLaser(BaseTank&);
//���䵼�����Կ��ӷ�Χ�������̹�˽���
void OpenMissile(BaseTank&);
//�ӵ�
void BulletMove();
//��Ļ�ƶ�
void ScreenMove();
//��ը����
void OpenExplode(int,int,int,int,int);
//���ӵ�
void DrawBullet();
//���з�̹���Ƿ�����Ұ��
void TankBarrierCheck();
//���µз�̹��״̬
void EnemyTankStep();
//���Ƶ���̹��
void DrawEnemy();
//����̹������
void EnemyAI(BaseTank&);
//�������̹��״̬��
void DrawStateMap();


//�������
void HandleThing();
//��Ļ�𶯺���
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