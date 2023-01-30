#include "Particle.h"
#define _USE_MATH_DEFINES
#include <math.h> 

Particle::Particle()
{
	stage = new Stage;
	bullet = new Bullet;
	 width = 0;
	 movePoint = 0;
	 movePointflag = 0;
	 trigger = 0;
	 widthY = 0;

	 mauseposX = 0;
	 mauseposY = 0;

	 degree = 0;
	 rotate = 0;
	 theta = 0;
	
	
}

void Particle::Move()
{
	//パーティクル
	for (int num = 0; num < NUM1; num++) {
		if (particle1[num].isActive == 0) {
			particle1[num].isActive = 1;
			particle1[num].width = 10.0f;
			particle1[num].isActiveTime = 0;
			particle1[num].color = WHITE;
			particle1[num].speed = (rand() % 5 + 5) * 0.1f + rand() % 2 + 1;
			particle1[num].velocity.x = particle1[num].speed * cosf(degree * (M_PI / 180.0f)) - particle1[num].speed * sinf(degree * (M_PI / 180.0f));
			particle1[num].velocity.y = particle1[num].speed * sinf(degree * (M_PI / 180.0f)) + particle1[num].speed * cosf(degree * (M_PI / 180.0f));
			degree += 7.2f + (rand() % 10 - 4);
			particle1[num].possition.x = bullet->playerBulletPosX;
			particle1[num].possition.y = bullet->playerBulletPosY;
			if (degree > 360.0f) {
				degree = 0;
				break;
			}
		}

		if (particle1[num].isActive == 1) {
			particle1[num].isActiveTime += 1;
			particle1[num].possition.x += particle1[num].velocity.x;
			particle1[num].possition.y += particle1[num].velocity.y;
			if (particle1[num].isActiveTime % 45 == 0) {
				particle1[num].color = 0xFFFFFF21;
			}
			else if (particle1[num].isActiveTime % 30 == 0) {
				particle1[num].color = 0xFFFFFF39;
			}
			else if (particle1[num].isActiveTime % 15 == 0) {
				particle1[num].color = 0xFFFFFF40;
			}
			if (particle1[num].isActiveTime > 60) {
				particle1[num].isActive = 0;
			}
		}
	}
}

void Particle::Draw()
{
	for (int num = 0; num < NUM1; num++) {
		if (particle1[num].isActive == 1) {
			Novice::DrawBox(particle1[num].possition.x - stage->scrollX - particle1[num].width / 2, particle1[num].possition.y - particle1[num].width / 2,
				particle1[num].width, particle1[num].width, 0.0f, particle1[num].color, kFillModeSolid);
		}
	}
}
