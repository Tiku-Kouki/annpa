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

	int leftTopX;//左上のX座標
	int leftTopY;//左上のY座標
	int rightTopX;//右上のX座標
	int rightTopY;//右上のY座標
	int leftBottomX;//左下のX座標
	int leftBottomY;//左下のY座標
	int rightBottomX;//右下のX座標
	int rightBottomY;//右下のY座標
	int playerPosOldX;//Xに仮に進んだときの変数
	int playerPosOldY;//Yに仮に進んだときの変数
	int galle;
	int galleTimer;
	//コントローラーのボタン宣言		
	int isBButtonPress = 0;//Bボタン
	int isAButtonPress = 0;//Aボタン
	int isStartButtonPress = 0;//Startボタン
	//スティック操作
	int stickPosX = 0;
	int stickPosY = 0;
	//ダメージ
	float isDamag = false;
	float DamagTimer = 0;
	//血のスイッチ
	int isBlood = 0;
	//クールタイム
	int canShot = 0;
	int canShotTime = 10;
	//明るくなっている間
	int islight = 0;
	int light = 120;
	int charaDir;
	Bullet* bullet;
	Stage* stage;
	//ファイル分けのやつ
	Luminous* luminous;
	Resources* resources;
	Particle* particle;

	int gamescene;
	int playerLife ;
	int playerResai;//残機
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

