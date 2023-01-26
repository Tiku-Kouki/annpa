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
	超音波の宣言ここから
	*******************/
	int playerBulletPosX;
	int playerBulletPosY;
	int bulletspeed;
	int bulletRadius;
	int isbulletshot;
	int bulletMonitorX;
	/*******************
	超音波の宣言ここまで
	*******************/

	//クールタイム
	int canShot ;
	int canShotTime ;

};

