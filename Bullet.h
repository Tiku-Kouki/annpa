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
	�����g�̐錾��������
	*******************/
	int playerBulletPosX = -200;
	int playerBulletPosY = -200;
	int bulletspeed = 10;
	int bulletRadius = 32;
	int isbulletshot = 0;
	int bulletMonitorX = 0;
	/*******************
	�����g�̐錾�����܂�
	*******************/

	//�N�[���^�C��
	int canShot = false;
	int canShotTime = 10;

};

