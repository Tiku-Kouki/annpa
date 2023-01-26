#include"Player.h"
#include"Bullet.h"


Player::Player(float posX, float posY, float speed, float radius)
{
	stage = new Stage;
	bullet = new Bullet;

	player.pos.x = posX;
	player.pos.y = posY;
	player.speed = speed;
	player.radius = radius;
	 galle = 0;
	 galleTimer = 0;
	 //�L�����̏�������
	  charaDir = RIGHT;

	  playerLife = 1000;

	//�E����W
	rightTopX = (player.pos.x + player.radius - 1) / stage->blockSize;
	rightTopY = (player.pos.y - player.radius) /stage-> blockSize;

	// �E�����W
	rightBottomX = (player.pos.x + player.radius - 1) / stage->blockSize;
	rightBottomY = (player.pos.y + player.radius - 1) / stage->blockSize;

	// ������W
	leftTopX = (player.pos.x - player.radius) / stage->blockSize;
	leftTopY = (player.pos.y - player.radius) / stage->blockSize;

	// �������W
	leftBottomX = (player.pos.x - player.radius) / stage->blockSize;
	leftBottomY = (player.pos.y + player.radius - 1) / stage->blockSize;

	//�|�W�V���������ɑ��
	playerPosOldX = player.pos.x;
	playerPosOldY = player.pos.y;


}

Player::~Player()
{
	
	delete bullet;
}

void Player::Move(char* keys, char* preKeys)
{
	switch (gamescene)
	{
	case TITLE:



		break;

		if (keys[DIK_W])
		{
			leftTopY = ((player.pos.y - player.speed) - player.radius) / stage->blockSize;
			rightTopY = ((player.pos.y - player.speed) - player.radius) / stage->blockSize;
			////�u���b�N�ɓ���������
			if (stage->map[rightTopY][rightTopX] == BLOCK) {
				player.pos.x = playerPosOldX;
				player.pos.y = playerPosOldY;
			}
			else if (stage->map[leftTopY][leftTopX] == BLOCK) {
				player.pos.x = playerPosOldX;
				player.pos.y = playerPosOldY;
			}
			else {
				player.pos.y -= player.speed;
			}

		}

		if (keys[DIK_A])
		{
			leftTopX = ((player.pos.x - player.speed) - player.radius) / stage->blockSize;
			leftBottomX = ((player.pos.x - player.speed) - player.radius) / stage->blockSize;
			//�u���b�N�ɓ���������
			if (stage->map[leftTopY][leftTopX] == BLOCK) {
				player.pos.x = playerPosOldX;
				player.pos.y = playerPosOldY;
			}
			else if (stage->map[leftBottomY][leftBottomX] == BLOCK) {
				player.pos.x = playerPosOldX;
				player.pos.y = playerPosOldY;
			}
			else {
				player.pos.x -= player.speed;
			}
		}
		if (keys[DIK_D])
		{
			rightTopX = ((player.pos.x + player.speed) + player.radius - 1) / stage->blockSize;
			rightBottomX = ((player.pos.x + player.speed) + player.radius - 1) / stage->blockSize;
			//�u���b�N�ɓ���������
			if (stage->map[rightTopY][rightTopX] == BLOCK) {
				player.pos.x = playerPosOldX;
				player.pos.y = playerPosOldY;
			}
			else if (stage->map[rightBottomY][rightBottomX] == BLOCK) {
				player.pos.x = playerPosOldX;
				player.pos.y = playerPosOldY;
			}
			else {
				player.pos.x += player.speed;
			}
			//�S�[��
			if (stage->map[rightTopY][rightTopX] == Galle) {
				galle = 1;
			}
			else if (stage->map[rightBottomY][rightBottomX] == Galle) {
				galle = 1;
			}

		}
		if (keys[DIK_S])
		{
			leftBottomY = ((player.pos.y + player.speed) + player.radius - 1) / stage->blockSize;
			rightBottomY = ((player.pos.y + player.speed) + player.radius - 1) / stage->blockSize;
			//�u���b�N�ɓ���������
			if (stage->map[leftBottomY][leftBottomX] == BLOCK) {
				player.pos.x = playerPosOldX;
				player.pos.y = playerPosOldY;
			}
			else if (stage->map[rightBottomY][rightBottomX] == BLOCK) {
				player.pos.x = playerPosOldX;
				player.pos.y = playerPosOldY;
			}
			else {
				player.pos.y += player.speed;
			}

		}
		//���̔���
		if (stage->map[leftTopY][leftTopX] == BLOOD) {

			if (keys[DIK_RETURN] == 0 && preKeys[DIK_RETURN] || Novice::IsTriggerButton(0, kPadButton10)) {
				stage->map[leftTopY][leftTopX] = NONE;
				isBlood = 1;
			}

		}
		else
			if (stage->map[leftBottomY][leftBottomX] == BLOOD) {
				if (keys[DIK_RETURN] == 0 && preKeys[DIK_RETURN] || Novice::IsTriggerButton(0, kPadButton10)) {
					stage->map[leftBottomY][leftBottomX] = NONE;
					isBlood = 1;
				}

			}
			else
				if (stage->map[rightTopY][rightTopX] == BLOOD) {
					if (keys[DIK_RETURN] == 0 && preKeys[DIK_RETURN] || Novice::IsTriggerButton(0, kPadButton10)) {
						stage->map[rightTopY][rightTopX] = NONE;
						isBlood = 1;
					}

				}
				else
					if (stage->map[rightBottomY][rightBottomX] == BLOOD) {
						if (keys[DIK_RETURN] == 0 && preKeys[DIK_RETURN] || Novice::IsTriggerButton(0, kPadButton10)) {
							stage->map[rightBottomY][rightBottomX] = NONE;
							isBlood = 1;
						}

					}
		if (isBlood == 1) {

			playerLife += 300;
			isBlood = 0;
		}
		if (galle == 0) {

			if (bullet->isbulletshot == 0) {
				if (keys[DIK_A] || stickPosX <= -3000) {
					charaDir = LEFT;
				}
				if (keys[DIK_D] || stickPosX >= 3000) {
				if (keys[DIK_D] || stickPosX >= 3000) {
					charaDir = RIGHT;
				}
			}
			if (canShot == 1) {
				//�v���C���[���������ɒe��������
				if (charaDir == LEFT) {
					if (keys[DIK_SPACE] == 0 && preKeys[DIK_SPACE] || Novice::IsTriggerButton(0, kPadButton11)) {
						if (bullet->isbulletshot == 0) {
							bullet->isbulletshot = 1;
							bullet->playerBulletPosX = player.pos.x;
							bullet->playerBulletPosY = player.pos.y;
							playerLife -= 30;
						}
					}
					if (bullet->isbulletshot == 1) {
						bullet->playerBulletPosX = bullet->playerBulletPosX - bullet->bulletspeed;
					}
				}

				//�v���C���[���E�����ɒe��������
				else if (charaDir == RIGHT) {
					if (keys[DIK_SPACE] == 0 && preKeys[DIK_SPACE] || Novice::IsTriggerButton(0, kPadButton11)) {
						if (bullet->isbulletshot == 0) {
							bullet->isbulletshot = 1;
							bullet->playerBulletPosX = player.pos.x;
							bullet->playerBulletPosY = player.pos.y;
							playerLife -= 30;
						}
					}
					if (bullet->isbulletshot == 1) {
						bullet->playerBulletPosX = bullet->playerBulletPosX + bullet->bulletspeed;
					}
				}

			}
		}
	}
}
void Player::Draw(){
	Novice::DrawEllipse(player.pos.x, player.pos.y, player.radius, player.radius, 0.0f, WHITE, kFillModeSolid);

	bullet->Draw();

}
