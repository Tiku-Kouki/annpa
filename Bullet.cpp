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
	
	//�N�[���^�C��
	 canShot = false;
	 canShotTime = 10;
	
}

Bullet::~Bullet()
{
}

void Bullet::Shot(int charaDir)
{
	//�����ɒe�̈ړ�����������
	
		//�v���C���[���������ɒe��������
		if (charaDir == LEFT) {

			if (isbulletshot == 1) {
				playerBulletPosX = playerBulletPosX -bulletspeed;
			}
		}

		//�v���C���[���E�����ɒe��������
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
		
	Novice::DrawSprite(playerBulletPosX - scrollX - bulletRadius, playerBulletPosY - bulletRadius,resources->blt, 1.0, 1.0f,0.0f, 0xFFFFFFFF);
		
	}
}
