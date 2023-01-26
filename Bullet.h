#pragma once
#include <Novice.h>
#include"Stage.h"
class Bullet
{
public:
	Resources* resources;
	Stage* stage;
	Bullet();
	~Bullet();
	void Update();
	void Draw();
public:
	/*******************
	�����g�̐錾��������
	*******************/
	int playerBulletPosX;
	int playerBulletPosY;
	int bulletspeed;
	int bulletRadius;
	int isbulletshot;
	int bulletMonitorX;
	/*******************
	�����g�̐錾�����܂�
	*******************/

	//�N�[���^�C��
	int canShot ;
	int canShotTime ;

};

