#pragma once
#include <Novice.h>
#include"Struct.h"
#include"Bullet.h"
class Particle
{
public:
	Particle();
	void Move();
	void Draw(int scrollX);
	void Update(int bulletX, int bulletY);
	Circle particle1[NUM1]{
		{0, 0},
		{0, 0},
		5,
		5,
		0,
		0
	};
	float width = 0;
	float movePoint = 0;
	float movePointflag = 0;
	int trigger = 0;
	int widthY = 0;

	int mauseposX = 0;
	int mauseposY = 0;

	float degree = 0;
	float rotate = 0;
	float theta = 0;
	int galle = 0;
	int galleTimer = 0;
	Bullet* bullet;
	Stage* stage;
};

