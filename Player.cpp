#include"Player.h"



Player::Player()
{
	stage = new Stage;
	bullet = new Bullet;
	particle = new  Particle;
	luminous = new Luminous;
	player.pos.x = 400;
	player.pos.y = 512;
	player.speed = 4.0f;
	player.radius = 32.0f;
	galle = 0;
	galleTimer = 0;
	//�E����W
	rightTopX = (player.pos.x + player.radius - 1) / stage->blockSize;
	rightTopY = (player.pos.y - player.radius) / stage->blockSize;

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
	//�L�����̏�������
	charaDir = RIGHT;

	playerLife = 1000;
	gamescene = 0;
	//�R���g���[���[�̃{�^���錾		
	isBButtonPress = 0;//B�{�^��
	isAButtonPress = 0;//A�{�^��
	isStartButtonPress = 0;//Start�{�^��
   //�X�e�B�b�N����
	stickPosX = 0;
	stickPosY = 0;
	//�_���[�W
	isDamag = false;
	DamagTimer = 0;
	//���̃X�C�b�`
	isBlood = 0;
	//�N�[���^�C��
	canShot = false;
	canShotTime = 10;
	//���邭�Ȃ��Ă����
	islight = 0;
	light = 120;
	charaDir = 0;

	//���邭�Ȃ��Ă����
	islight = 0;
	light = 120;

	tmpPosX = 0;
	tmpPosY = 0;
	tmpPosY1 =0;

}

Player::~Player()
{
	delete stage;

	delete particle;
	delete luminous;
	delete bullet;
}


void Player::Update(char* keys, char* preKeys) {
	if (bullet->isbulletshot == 0) {
		if (keys[DIK_A] || stickPosX <= -3000) {
			charaDir = LEFT;
		}
		if (keys[DIK_D] || stickPosX >= 3000) {
			charaDir = RIGHT;
		}
	}
	if (canShot == 1) {
		// �e�̏���
		if (keys[DIK_SPACE] && preKeys[DIK_SPACE] || Novice::IsTriggerButton(0, kPadButton11)) {
			if (bullet->isbulletshot == 0) {
				bullet->playerBulletPosX = player.pos.x;
				bullet->playerBulletPosY = player.pos.y;
				
				playerLife -= 30;
				bullet->isbulletshot = 1;
			}
		}
		
		if (bullet->isbulletshot == 1) {
			bullet->Shot(charaDir);
		}
	}
	bullet->Update();

	//// ���@�̏���
	//Move(keys,preKeys);


	// �����蔻��
	CheckCollision();
	particle->Move();
	if (islight == 1) {
		//���邭����
		if (luminous->value_ == luminous->valueMax_) {
			luminous->SetFade(true);
		}

	}

	if (!luminous->GetFade()) {
		if (luminous->value_ == luminous->valueMin_) {
			light--;
		}
	}

	//�Â�����
	if (light <= 0) {
		if (luminous->value_ == luminous->valueMin_) {
			luminous->SetFade(false);
			islight = 0;
			light = 120;
		}

	}

}
void Player::CheckCollision()
{
	//�������̓����蔻��
	if (charaDir == LEFT) {
		tmpPosX =bullet->playerBulletPosX - bullet->bulletRadius;
		tmpPosY =bullet->playerBulletPosY - bullet->bulletRadius;
		tmpPosY1 = bullet->playerBulletPosY +bullet->bulletRadius;

		//�e�̔���
		if (stage->map[tmpPosY / 128][tmpPosX / 128] == BLOCK || stage->map[tmpPosY1 / 128][tmpPosX / 128] == BLOCK) {

			particle->Update(bullet->playerBulletPosX, bullet->playerBulletPosY);
			
			/*******************
			���Ï����@��������
			*******************/

			if (islight == 0) {
			islight = 1;
			}

			/*******************
			���Ï����@�����܂�
			*******************/

			bullet->isbulletshot = 0;
			bullet->playerBulletPosX = player.pos.x;
			bullet->playerBulletPosY = player.pos.y;

		}


	}

	//�E�����̓����蔻�菈��
	if (charaDir == RIGHT) {
		tmpPosX = bullet->playerBulletPosX +bullet->bulletRadius;
		tmpPosY = bullet->playerBulletPosY -bullet->bulletRadius;
		tmpPosY1 = bullet->playerBulletPosY + bullet->bulletRadius;

		//�e�̔���
		if (stage->map[tmpPosY / 128][tmpPosX / 128] == BLOCK || stage->map[tmpPosY1 / 128][tmpPosX / 128] == BLOCK) {

			particle->Update(bullet->playerBulletPosX, bullet->playerBulletPosY);
			
			/*******************
			���Ï����@��������
			*******************/

			if (islight == 0) {
				islight = 1;
			}

			/*******************
			���Ï����@�����܂�
			*******************/

			bullet->isbulletshot = 0;
			bullet->playerBulletPosX = player.pos.x;
			bullet->playerBulletPosY = player.pos.y;

		}

	}

}
void Player::Move(char* keys, char* preKeys)
{
	switch (gamescene)
	{
	case TITLE:

		//B�{�^��
		if (Novice::IsTriggerButton(0, kPadButton11)) {
			isBButtonPress = 1;
		}

		//�`���[�g���A���Ɉڍs����
		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE] || Novice::IsTriggerButton(0, kPadButton11)) {
			gamescene = STAGE;
		}

		break;
	case STAGE:

		luminous->Update();

		


		if (galle == 0) {
			playerLife--;
		}
		if (playerLife <= 0) {
			gamescene = GAMEOVER;
		}
		if (playerLife >= 1000) {
			playerLife = 1000;
		}
		//�V�[�����ς�������̃N�[���^�C��
		if (gamescene == STAGE) {
			canShotTime -= 1;
			islight = 0;
			if (canShotTime <= 0) {
				canShot = 1;
			}
		}
		//�R���g���[���[�̃{�^������
			// B�{�^��
		if (Novice::IsTriggerButton(0, kPadButton11)) {
			isBButtonPress = 1;
		}

		//A�{�^��
		if (Novice::IsTriggerButton(0, kPadButton10)) {
			isAButtonPress = 1;
		}
		//�E����W
		rightTopX = (player.pos.x + player.radius - 1) / stage->blockSize;
		rightTopY = (player.pos.y - player.radius) / stage->blockSize;

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
		if (galle == 0) {
			Novice::GetAnalogInputLeft(0, &stickPosX, &stickPosY);
			if (keys[DIK_W] || stickPosY <= -3000)
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

			if (keys[DIK_A] || stickPosX <= -3000)
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
			if (keys[DIK_D] || stickPosX >= 3000)
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
			if (keys[DIK_S] || stickPosY >= 3000)
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
		}
		if (isBlood == 1) {

			playerLife += 300;
			isBlood = 0;
		}

		Update(keys,preKeys);

		if (galle == 1) {
			Novice::ScreenPrintf(0, 0, "galle 1 �@");
			galleTimer += 1;
			player.pos.x += player.speed;
			if (kWindowWidth + player.radius < player.pos.x) {
			
				if (galleTimer >= 120) {
					gamescene = RESULT;
			
				}
			}
		}
			//�X�N���[������
			if (player.pos.x >= kWindowWidth + stage->scrollStartX) {
				stage->scrollX = kWindowWidth;
			}
			else if (player.pos.x >= stage->scrollStartX) {
				stage->scrollX = player.pos.x - stage->scrollStartX;
			}
		break;
	case GAMEOVER:

		break;

	case RESULT:
		player.pos.x = 400;
		player.pos.y = 512;

		galleTimer = 0;
		galle = 0;
		charaDir = RIGHT;

		playerLife = 1000;

		//�X�N���[������
		stage->scrollStartX = 400;
		stage->lineY = 0;

		stage->scrollX = 0;

		stage->monitorX = 0;

		//�X�e�B�b�N����
		stickPosX = 0;
		stickPosY = 0;

		/*******************
		�����g�̐錾��������
		*******************/
		bullet->playerBulletPosX = -200;
		bullet->playerBulletPosY = -200;
		bullet->bulletspeed = 10;
		bullet->bulletRadius = 32;
		bullet->isbulletshot = 0;
		bullet->bulletMonitorX = 0;
		/*******************
		�����g�̐錾�����܂�
		*******************/
		//�N�[���^�C��
		canShot = false;
		canShotTime = 10;

		//�_���[�W
		isDamag = false;
		DamagTimer = 0;

		if (keys[DIK_SPACE] || Novice::IsTriggerButton(0, kPadButton11)) {
			gamescene = STAGE;
		}

		break;
			
		

	}
}
void Player::Draw() {
	switch (gamescene)
	{
	case STAGE:
		stage->Draw();
		luminous->Draw();
		bullet->Draw(stage->scrollX);
		particle->Draw(stage->scrollX);

		Novice::DrawEllipse(player.pos.x - stage->scrollX, player.pos.y, player.radius, player.radius, 0.0f, RED, kFillModeSolid);

		Novice::DrawBox(900, 50, playerLife, 50, 0.0f, WHITE, kFillModeSolid);


		break;
	}
}
