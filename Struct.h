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
	TUTORIAL,
	RESULT,
	STAGE,
	CLEAR,
	GAMEOVER,
};
enum CharaDir {
	RIGHT,
	LEFT,
};
const int kWindowWidth = 1920;
const int kWindowHeight = 1024;
const int mapHeight=8;//Y���̃u���b�N�̐�
const int mapWidth=30;//X���̃u���b�N�̐�
const int NUM = 300;
const int NUM1 = 300;
const int NUM2 = 300;
const int NUM3 = 300;