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

void Bullet::Shot(int charaDir)
{
	//ここに弾の移動処理を書く
	
		//プレイヤーが左向きに弾を撃つ処理
		if (charaDir == LEFT) {

			if (isbulletshot == 1) {
				playerBulletPosX = playerBulletPosX -bulletspeed;
			}
		}

		//プレイヤーが右向きに弾を撃つ処理
		else if (charaDir == RIGHT) {
			
			if (isbulletshot == 1) {
				playerBulletPosX = playerBulletPosX + bulletspeed;
			}
		}

	
}



void Bullet::Update()
{
	
}

void Bullet::Draw(int scrollX)
{
	if (isbulletshot == 1) {
		
	Novice::DrawBox(playerBulletPosX - scrollX - bulletRadius, playerBulletPosY - bulletRadius, bulletRadius * 2, bulletRadius * 2, 0.0f, 0xFFFFFFFF, kFillModeSolid);
		
	}
}
