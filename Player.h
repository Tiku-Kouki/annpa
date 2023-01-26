#pragma once
#include <Novice.h>
#include"Struct.h"
#include"Stage.h"
#include"Bullet.h"

typedef struct Player1 {
	Vector2 pos;
	float speed;
	float radius;
};

class Player
{
public:
	Player(float posX, float posY, float speed, float radius);
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
	//�_���[�W
	float isDamag = false;
	float DamagTimer = 0;
	//���̃X�C�b�`
	int isBlood = 0;
	//�N�[���^�C��
	int canShot = false;
	int canShotTime = 10;

	Bullet* bullet;
	Stage* stage;
	//�L�����̏�������
	CharaDir charaDir;

	int gamescene;
	int playerLife ;
	void Move(char* keys, char* preKeys);
	void Draw();

private:

	
	Player1 player{
	400,512,4.0f,32.0f
	};
	
};

