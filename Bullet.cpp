#include "Bullet.h"





Bullet::Bullet()
{
	resources = new Resources;
	stage = new Stage;
	 playerBulletPosX = -200;
	 playerBulletPosY = -200;
	 bulletspeed = 10;
	 bulletRadius = 32;
	 isbulletshot = 0;
	 bulletMonitorX = 0;
	
	//クールタイム
	 canShot = false;
	 canShotTime = 10;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	
}

void Bullet::Draw()
{
	if (isbulletshot == 1) {
		
	Novice::DrawBox(playerBulletPosX - stage->scrollX - bulletRadius, playerBulletPosY - bulletRadius, bulletRadius * 2, bulletRadius * 2, 0.0f, 0xFFFFFFFF, kFillModeSolid);
		
	}
}
