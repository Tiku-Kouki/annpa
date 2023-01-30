#pragma once

typedef struct Vector2 {
	float x;
	float y;

};
enum MapInfo {
	NONE, // 0�@(�u���b�N�Ȃ�)
	BLOCK, // 1�@(�u���b�N����)
	BLOOD,//2 (��)
	Galle,//3�@(�S�[��)
	UP_NEEDLE,//4 (������̏ߓ���)
	DOWN_NEEDLE//5 (�������̏ߓ���)
};
enum Gamescene {
	TITLE,
	STAGE,
	RESULT,
	CLEAR,
	GAMEOVER,
};
enum GameStage {
	TUTORIAL,
	STAGE1,
	STAGE2,
	STAGE3,
	STAGE4,
};
enum CharaDir {
	RIGHT,
	LEFT,
};
struct Circle {
	Vector2 possition;
	Vector2 velocity;
	float width;
	float speed;
	int isActive;
	int isActiveTime;
	int color;
};
const int kWindowWidth = 1920;
const int kWindowHeight = 1024;
const int mapHeight=8;//Y���̃u���b�N�̐�
const int mapWidth=30;//X���̃u���b�N�̐�
const int NUM = 300;
const int NUM1 = 300;
const int NUM2 = 300;
const int NUM3 = 300;