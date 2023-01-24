#include"Player.h"
#include"Bullet.h"



Player::Player()
{
	pos.x = 100;
	pos.y = 100;
	speed_ = 8;
	radius = 16;
	isBulletShot = 0;
	

}

Player::~Player()
{
	/*delete bullet;*/
}

void Player::Move(char* keys, char* preKeys)
{
	if (keys[DIK_W])
	{

		pos.y -= speed_;

	}

	if (keys[DIK_A])
	{
		pos.x -= speed_;
	}
	if (keys[DIK_D])
	{
		pos.x += speed_;

	}
	if (keys[DIK_S])
	{
		pos.y += speed_;

	}

//	//if (bullet->isShot == 0)
//	//{
//
//
//	//	if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
//	//	{
//	//		//弾を発射する
//	//		bullet->isShot = 1;
//
//
//	//		//弾の座標とプレイヤーの座標が一緒になる
//	//		bullet->bulletPos.x = pos.x;
//	//		bullet->bulletPos.y = pos.y;
//
//
//	//	}
//	//}
//	bullet->Update();
}
//
//void Player::Draw()
//{
//	Novice::DrawEllipse(pos.x, pos.y, radius, radius, 0.0f, WHITE, kFillModeSolid);
//	bullet->Draw();
//}
