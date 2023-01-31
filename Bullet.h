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
	void Shot(int charaDir);
	void Update();
	void Draw(int scrollX);
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

