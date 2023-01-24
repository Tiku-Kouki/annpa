#pragma once
class Bullet
{
public:
	Bullet();
	~Bullet();
	void Update();
	void Draw();
private:
	/*******************
	超音波の宣言ここから
	*******************/
	int playerBulletPosX = -200;
	int playerBulletPosY = -200;
	int bulletspeed = 10;
	int bulletRadius = 32;
	int isbulletshot = 0;
	int bulletMonitorX = 0;
	/*******************
	超音波の宣言ここまで
	*******************/

	//クールタイム
	int canShot = false;
	int canShotTime = 10;

};

