#pragma once
#include <Novice.h>
#include"Struct.h"
#include"Stage.h"
#include"Bullet.h"
#include"Luminous.h"
#include"Particle.h"



class Player
{

public:
	Player();
	~Player();

	int leftTopX;//�����X���W
	int leftTopY;//�����Y���W
	int rightTopX;//�E���X���W
	int rightTopY;//�E���Y���W
	int leftBottomX;//������X���W
	int leftBottomY;//������Y���W
	int rightBottomX;//�E����X���W
	int rightBottomY;//�E����Y���W
	int playerPosOldX;//X�ɉ��ɐi�񂾂Ƃ��̕ϐ�
	int playerPosOldY;//Y�ɉ��ɐi�񂾂Ƃ��̕ϐ�
	int galle;
	int galleTimer;
	//�R���g���[���[�̃{�^���錾		
	int isBButtonPress = 0;//B�{�^��
	int isAButtonPress = 0;//A�{�^��
	int isStartButtonPress = 0;//Start�{�^��
	//�X�e�B�b�N����
	int stickPosX = 0;
	int stickPosY = 0;
	//�_���[�W
	float isDamag = false;
	float DamagTimer = 0;
	//���̃X�C�b�`
	int isBlood = 0;
	//�N�[���^�C��
	int canShot = 0;
	int canShotTime = 10;
	//���邭�Ȃ��Ă����
	int islight = 0;
	int light = 120;
	int charaDir;
	Bullet* bullet;
	Stage* stage;
	//�t�@�C�������̂��
	Luminous* luminous;
	Resources* resources;
	Particle* particle;

	int gamescene;
	int playerLife ;
	int playerResai;//�c�@
	int respoonTime;
	void Update(char* keys, char* preKeys);
	void Move(char* keys, char* preKeys);
	
	void Draw();
	void Reset();

	void CheckCollision();
	int tmpPosX;

	int tmpPosY;
	int tmpPosY1;

	int GetPosX() { return player.pos.x; };
	int GetPosY() { return player.pos.y; };
	int GetSpeed() { return player.speed; };
	
	int GetRadius() { return player.radius; };




	Player1 player{};


};

