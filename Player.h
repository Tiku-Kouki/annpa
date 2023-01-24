#pragma once
#include <Novice.h>
#include"Struct.h"

class Player
{
public:
	
	Vector2 pos;
	Player();
	~Player();
	int speed_;
	int radius;
	int isBulletShot;
public:

	void Move(char* keys, char* preKeys);
	void Draw();
};

