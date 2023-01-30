#pragma once

typedef struct Vector2 {
	float x;
	float y;

};
enum MapInfo {
	NONE, // 0　(ブロックなし)
	BLOCK, // 1　(ブロックあり)
	BLOOD,//2 (血)
	Galle,//3　(ゴール)
	UP_NEEDLE,//4 (上向きの鍾乳洞)
	DOWN_NEEDLE//5 (下向きの鍾乳洞)
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
const int mapHeight=8;//Y軸のブロックの数
const int mapWidth=30;//X軸のブロックの数
const int NUM = 300;
const int NUM1 = 300;
const int NUM2 = 300;
const int NUM3 = 300;