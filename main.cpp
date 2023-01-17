#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h> 
#include <stdlib.h>

const char kWindowTitle[] = "暗波";
const int kWindowWidth = 1920;
const int kWindowHeight = 1024;

enum MapInfo {
	NONE, // 0　(ブロックなし)
	BLOCK, // 1　(ブロックあり)
	BLOOD,//2 (血)
	Galle//3　(ゴール)
};

//構造体の宣言 ここから

typedef struct Vector2 {
	float x;
	float y;
};

typedef struct Player {
	Vector2 pos;
	float speed;
	float radius;
};

Player player{
	400,512,4.0f,32.0f
};

//ブロックの構造体
typedef struct Block {
	MapInfo state; //ブロックの状態
	Vector2 pos; //座標
	Vector2 size; //画像の大きさ
	Vector2 imagePos; //読み込む画像の座標
};

//構造体の宣言 ここまで

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//シーン切り替えの宣言
	enum Gamescene {
		TITLE,
		TUTORIAL,
		RESULT,
		STAGE1,
		RESULT1,
		STAGE2,
		RESULT2,
		STAGE3,
		RESULT3,
		CLEAR,
		GAMEOVER,
	};

	//キャラの方向
	enum CharaDir {
		RIGHT,
		LEFT,
	};

	/*************************
	パーティクルなどの宣言ここから
	*************************/

	const int NUM = 300;
	const int NUM1 = 300;
	const int NUM2 = 300;
	const int NUM3 = 300;

	struct Vector3 {
		float x;
		float y;
	};

	struct Circle {
		Vector3 possition;
		Vector3 velocity;
		float width;
		float speed;
		int isActive;
		int isActiveTime;
		int color;
	};

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

	//色
	unsigned int color = 0x0000FF64; //半透明の青

	/*************************
	パーティクルなどの宣言ここまで
	*************************/

	//キャラの初期方向
	CharaDir charaDir = RIGHT;

	int playerLife = 1000;

	const int mapHeight = 8;//Y軸のブロックの数
	const int mapWidth = 30;//X軸のブロックの数

	int blockSize = 128;//ブロックサイズ

	int posXtmp = 0;//仮に進ませた時のX座標
	int posYtmp = 0;//仮に進ませた時のY座標

	//スクロール処理
	float scrollStartX = 400;
	float lineY = 0;

	int scrollX = 0;

	float monitorX = 0;

	//スティック操作
	int stickPosX = 0;
	int stickPosY = 0;

	//コントローラーのボタン宣言		
	int isBButtonPress = 0;//Bボタン
	int isAButtonPress = 0;//Aボタン
	int isStartButtonPress = 0;//Startボタン


	/*******************
	超音波の宣言ここから
	*******************/
	int playerBulletPosX = -200;
	int playerBulletPosY = -200;
	int bulletspeed = 10;
	int bulletRadius = 32;
	int isbulletshot = 0;
	int bulletMonitorX = 0;
	/*******************
	超音波の宣言ここまで
	*******************/

	//クールタイム
	int canShot = false;
	int canShotTime = 10;

	/*********************
	マップチップ配置ここから
	*********************/
	//チュートリアル
	int map[mapHeight][mapWidth]{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,},
		{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,},
		{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,2,0,0,0,0,0,1,0,0,0,2,0,0,3,},
		{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,3,},
		{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},
	};

	Block block[mapHeight][mapWidth]{};

	//ステージ１
	int map1[mapHeight][mapWidth]{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},
		{1,0,0,0,0,0,1,2,0,0,0,0,1,0,0,0,0,1,0,0,2,1,1,1,1,0,0,0,0,1,},
		{1,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,0,0,0,0,1,},
		{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,3,},
		{1,0,0,0,1,0,1,0,0,0,0,0,1,1,1,0,0,1,1,1,1,2,1,0,0,0,0,0,0,3,},
		{1,0,0,0,1,0,1,0,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,},
		{1,0,0,0,1,2,1,0,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},
	};

	Block block1[mapHeight][mapWidth]{};

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


	//ブロックの状況(チュートリアル)
	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			//ブロックの座標、サイズ設定
			block[y][x].pos.x = x * blockSize;
			block[y][x].pos.y = y * blockSize;
			block[y][x].size.x = 128;
			block[y][x].size.y = 128;



			//ブロックがある場合
			if (map[y][x] == 1) {
				block[y][x].state = BLOCK;
				block[y][x].imagePos.x = 0;
				block[y][x].imagePos.y = 128;
			}

			//ブロックがない場合
			if (map[y][x] == 0) {
				block[y][x].state = NONE;
				block[y][x].imagePos.x = 128;
				block[y][x].imagePos.y = 0;
			}

			//血がある場合
			if (map[y][x] == 2) {
				block[y][x].state = BLOOD;

			}

			//ゴール
			if (map[y][x] == 3) {
				block[y][x].state = Galle;
			}
		}
	}

	//ブロックの状況(ステージ１)
	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			//ブロックの座標、サイズ設定
			block1[y][x].pos.x = x * blockSize;
			block1[y][x].pos.y = y * blockSize;
			block1[y][x].size.x = 128;
			block1[y][x].size.y = 128;

			//ブロックがある場合
			if (map1[y][x] == 1) {
				block1[y][x].state = BLOCK;
				block1[y][x].imagePos.x = 0;
				block1[y][x].imagePos.y = 128;
			}

			//ブロックがない場合
			if (map1[y][x] == 0) {
				block1[y][x].state = NONE;
				block1[y][x].imagePos.x = 128;
				block1[y][x].imagePos.y = 0;
			}

			//血がある場合
			if (map1[y][x] == 2) {
				block1[y][x].state = BLOOD;

			}

			//ゴール
			if (map1[y][x] == 3) {
				block1[y][x].state = Galle;
			}

		}
	}

	//ゲームシーン　始めの処理
	int gamescene = TITLE;

	//画像
	int gh1 = Novice::LoadTexture("./Resources/block.png");

	//血のスイッチ
	int isBlood = 0;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		Novice::SetWindowMode(kFullscreen);

		//終わりのボタン
		if (Novice::IsTriggerButton(0, kPadButton4)) {
			isStartButtonPress = 1;
		}

		//ゲームシーン
		switch (gamescene)
		{
			//タイトル
		case TITLE:
			
			//Bボタン
			if (Novice::IsTriggerButton(0, kPadButton11)) {
				isBButtonPress = 1;
			}

			//チュートリアルに移行処理
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE] || Novice::IsTriggerButton(0, kPadButton11)) {
				gamescene = TUTORIAL;
			}

			break;

			//チュートリアル
		case TUTORIAL:

			if (galle == 0) {
				playerLife--;
			}
			if (playerLife <= 0) {
				gamescene = GAMEOVER;
			}
			if (playerLife >= 1000) {
				playerLife = 1000;
			}

			//シーンが変わった時のクールタイム
			if (gamescene == TUTORIAL) {
				canShotTime -= 1;
				if (canShotTime <= 0) {
					canShot = true;
				}
			}

			//右上座標
			rightTopX = (player.pos.x + player.radius - 1) / blockSize;
			rightTopY = (player.pos.y - player.radius) / blockSize;

			// 右下座標
			rightBottomX = (player.pos.x + player.radius - 1) / blockSize;
			rightBottomY = (player.pos.y + player.radius - 1) / blockSize;

			// 左上座標
			leftTopX = (player.pos.x - player.radius) / blockSize;
			leftTopY = (player.pos.y - player.radius) / blockSize;

			// 左下座標
			leftBottomX = (player.pos.x - player.radius) / blockSize;
			leftBottomY = (player.pos.y + player.radius - 1) / blockSize;

			//ポジションを仮に代入
			playerPosOldX = player.pos.x;
			playerPosOldY = player.pos.y;


			//コントローラーのボタン操作
			// Bボタン
			if (Novice::IsTriggerButton(0, kPadButton11)) {
				isBButtonPress = 1;
			}

			//Aボタン
			if (Novice::IsTriggerButton(0, kPadButton10)) {
				isAButtonPress = 1;
			}



			if (galle == 0) {
				//スティック操作
				Novice::GetAnalogInputLeft(0, &stickPosX, &stickPosY);


				//キーボード操作
				if (keys[DIK_W] || stickPosY <= -3000) {
					leftTopY = ((player.pos.y - player.speed) - player.radius) / blockSize;
					rightTopY = ((player.pos.y - player.speed) - player.radius) / blockSize;
					//ブロックに当たった時
					if (map[rightTopY][rightTopX] == BLOCK) {
						player.pos.x = playerPosOldX;
						player.pos.y = playerPosOldY;
					}
					else if (map[leftTopY][leftTopX] == BLOCK) {
						player.pos.x = playerPosOldX;
						player.pos.y = playerPosOldY;
					}
					else {
						player.pos.y -= player.speed;
					}
				}

				if (keys[DIK_S] || stickPosY >= 3000) {
					leftBottomY = ((player.pos.y + player.speed) + player.radius - 1) / blockSize;
					rightBottomY = ((player.pos.y + player.speed) + player.radius - 1) / blockSize;
					//ブロックに当たった時
					if (map[leftBottomY][leftBottomX] == BLOCK) {
						player.pos.x = playerPosOldX;
						player.pos.y = playerPosOldY;
					}
					else if (map[rightBottomY][rightBottomX] == BLOCK) {
						player.pos.x = playerPosOldX;
						player.pos.y = playerPosOldY;
					}
					else {
						player.pos.y += player.speed;
					}
				}

				if (keys[DIK_A] || stickPosX <= -3000) {
					leftTopX = ((player.pos.x - player.speed) - player.radius) / blockSize;
					leftBottomX = ((player.pos.x - player.speed) - player.radius) / blockSize;
					//ブロックに当たった時
					if (map[leftTopY][leftTopX] == BLOCK) {
						player.pos.x = playerPosOldX;
						player.pos.y = playerPosOldY;
					}
					else if (map[leftBottomY][leftBottomX] == BLOCK) {
						player.pos.x = playerPosOldX;
						player.pos.y = playerPosOldY;
					}
					else {
						player.pos.x -= player.speed;
					}
				}

				if (keys[DIK_D] || stickPosX >= 3000) {
					rightTopX = ((player.pos.x + player.speed) + player.radius - 1) / blockSize;
					rightBottomX = ((player.pos.x + player.speed) + player.radius - 1) / blockSize;
					//ブロックに当たった時
					if (map[rightTopY][rightTopX] == BLOCK) {
						player.pos.x = playerPosOldX;
						player.pos.y = playerPosOldY;
					}
					else if (map[rightBottomY][rightBottomX] == BLOCK) {
						player.pos.x = playerPosOldX;
						player.pos.y = playerPosOldY;
					}
					else {
						player.pos.x += player.speed;
					}
					//ゴール
					if (map[rightTopY][rightTopX] == Galle) {
						galle = 1;
					}
					else if (map[rightBottomY][rightBottomX] == Galle) {
						galle = 1;
					}

				}
			}
			//血の判定
			if (map[leftTopY][leftTopX] == BLOOD) {

				if (keys[DIK_RETURN] == 0 && preKeys[DIK_RETURN] || Novice::IsTriggerButton(0, kPadButton10)) {
					map[leftTopY][leftTopX] = NONE;
					isBlood = 1;
				}

			}
			else
				if (map[leftBottomY][leftBottomX] == BLOOD) {
					if (keys[DIK_RETURN] == 0 && preKeys[DIK_RETURN] || Novice::IsTriggerButton(0, kPadButton10)) {
						map[leftBottomY][leftBottomX] = NONE;
						isBlood = 1;
					}

				}
				else
					if (map[rightTopY][rightTopX] == BLOOD) {
						if (keys[DIK_RETURN] == 0 && preKeys[DIK_RETURN] || Novice::IsTriggerButton(0, kPadButton10)) {
							map[rightTopY][rightTopX] = NONE;
							isBlood = 1;
						}

					}
					else
						if (map[rightBottomY][rightBottomX] == BLOOD) {
							if (keys[DIK_RETURN] == 0 && preKeys[DIK_RETURN] || Novice::IsTriggerButton(0, kPadButton10)) {
								map[rightBottomY][rightBottomX] = NONE;
								isBlood = 1;
							}

						}
			if (isBlood == 1) {

				playerLife += 300;
				isBlood = 0;
			}


			if (galle == 0) {

				if (isbulletshot == 0) {
					if (keys[DIK_A] || stickPosX <= -3000) {
						charaDir = LEFT;
					}
					if (keys[DIK_D] || stickPosX >= 3000) {
						charaDir = RIGHT;
					}
				}
				if (canShot == 1) {
					//プレイヤーが左向きに弾を撃つ処理
					if (charaDir == LEFT) {
						if (keys[DIK_SPACE] == 0 && preKeys[DIK_SPACE] || Novice::IsTriggerButton(0, kPadButton11)) {
							if (isbulletshot == 0) {
								isbulletshot = 1;
								playerBulletPosX = player.pos.x;
								playerBulletPosY = player.pos.y;
								playerLife -= 30;
							}
						}
						if (isbulletshot == 1) {
							playerBulletPosX = playerBulletPosX - bulletspeed;
						}
					}

					//プレイヤーが右向きに弾を撃つ処理
					else if (charaDir == RIGHT) {
						if (keys[DIK_SPACE] == 0 && preKeys[DIK_SPACE] || Novice::IsTriggerButton(0, kPadButton11)) {
							if (isbulletshot == 0) {
								isbulletshot = 1;
								playerBulletPosX = player.pos.x;
								playerBulletPosY = player.pos.y;
								playerLife -= 30;
							}
						}
						if (isbulletshot == 1) {
							playerBulletPosX = playerBulletPosX + bulletspeed;
						}
					}

				}
			}
			//左向きの当たり判定
			if (charaDir == LEFT) {
				int tmpPosX = playerBulletPosX - bulletRadius;
				int tmpPosY = playerBulletPosY - bulletRadius;
				int tmpPosY1 = playerBulletPosY + bulletRadius;

				//弾の判定
				if (map[tmpPosY / 128][tmpPosX / 128] == BLOCK || map[tmpPosY1 / 128][tmpPosX / 128] == BLOCK) {

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
							particle1[num].possition.x = playerBulletPosX;
							particle1[num].possition.y = playerBulletPosY;
							if (degree > 360.0f) {
								degree = 0;
								break;
							}
						}
					}

					isbulletshot = 0;
					playerBulletPosX = player.pos.x;
					playerBulletPosY = player.pos.y;

				}
			}

			//右向きの当たり判定処理
			if (charaDir == RIGHT) {
				int tmpPosX = playerBulletPosX + bulletRadius;
				int tmpPosY = playerBulletPosY - bulletRadius;
				int tmpPosY1 = playerBulletPosY + bulletRadius;

				//弾の判定
				if (map[tmpPosY / 128][tmpPosX / 128] == BLOCK || map[tmpPosY1 / 128][tmpPosX / 128] == BLOCK) {

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
							particle1[num].possition.x = playerBulletPosX;
							particle1[num].possition.y = playerBulletPosY;
							degree += 7.2f + (rand() % 10 - 4);
							if (degree > 360.0f) {
								degree = 0;
								break;
							}
						}
					}

					isbulletshot = 0;
					playerBulletPosX = player.pos.x;
					playerBulletPosY = player.pos.y;

				}



			}

			for (int num = 0; num < NUM1; num++) {
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

			if (galle == 1) {
				Novice::ScreenPrintf(0, 0, "galle 1 　");
				galleTimer += 1;
				player.pos.x += player.speed;
				if (kWindowWidth + player.radius < player.pos.x) {
					if (galleTimer >= 120) {
						gamescene = RESULT;
					}
				}
			}

			//スクロール処理
			if (player.pos.x >= kWindowWidth + scrollStartX) {
				scrollX = kWindowWidth;
			}
			else if (player.pos.x >= scrollStartX) {
				scrollX = player.pos.x - scrollStartX;
			}

			break;

		case GAMEOVER:
			Novice::ScreenPrintf(0, 0, "GAME OVER 　");
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE] || Novice::IsTriggerButton(0, kPadButton11)) {

			}

			break;

		case RESULT:

			player.pos.x = 400;
			player.pos.y = 512;

			galleTimer = 0;
			galle = 0;
			charaDir = RIGHT;

			playerLife = 1000;

			//スクロール処理
			scrollStartX = 400;
			lineY = 0;

			scrollX = 0;

			monitorX = 0;

			//スティック操作
			stickPosX = 0;
			stickPosY = 0;

			/*******************
			超音波の宣言ここから
			*******************/
			playerBulletPosX = -200;
			playerBulletPosY = -200;
			bulletspeed = 10;
			bulletRadius = 32;
			isbulletshot = 0;
			bulletMonitorX = 0;
			/*******************
			超音波の宣言ここまで
			*******************/
			//クールタイム
			canShot = false;
			canShotTime = 10;

			if (keys[DIK_SPACE] || Novice::IsTriggerButton(0, kPadButton11)) {
				gamescene = STAGE1;
			}

			break;

		case STAGE1:

			if (galle == 0) {
				playerLife--;
			}
			if (playerLife <= 0) {
				gamescene = GAMEOVER;
			}
			if (playerLife >= 1000) {
				playerLife = 1000;
			}

			//シーンが変わった時のクールタイム
			if (gamescene == STAGE1) {
				canShotTime -= 1;
				if (canShotTime <= 0) {
					canShot = true;
				}
			}

			//右上座標
			rightTopX = (player.pos.x + player.radius - 1) / blockSize;
			rightTopY = (player.pos.y - player.radius) / blockSize;

			// 右下座標
			rightBottomX = (player.pos.x + player.radius - 1) / blockSize;
			rightBottomY = (player.pos.y + player.radius - 1) / blockSize;

			// 左上座標
			leftTopX = (player.pos.x - player.radius) / blockSize;
			leftTopY = (player.pos.y - player.radius) / blockSize;

			// 左下座標
			leftBottomX = (player.pos.x - player.radius) / blockSize;
			leftBottomY = (player.pos.y + player.radius - 1) / blockSize;

			//ポジションを仮に代入
			playerPosOldX = player.pos.x;
			playerPosOldY = player.pos.y;

			if (galle == 0) {
				//スティック操作
				Novice::GetAnalogInputLeft(0, &stickPosX, &stickPosY);

				//キーボード操作
				if (keys[DIK_W] || stickPosY <= -3000) {
					leftTopY = ((player.pos.y - player.speed) - player.radius) / blockSize;
					rightTopY = ((player.pos.y - player.speed) - player.radius) / blockSize;
					//ブロックに当たった時
					if (map1[rightTopY][rightTopX] == BLOCK) {
						player.pos.x = playerPosOldX;
						player.pos.y = playerPosOldY;
					}
					else if (map1[leftTopY][leftTopX] == BLOCK) {
						player.pos.x = playerPosOldX;
						player.pos.y = playerPosOldY;
					}
					else {
						player.pos.y -= player.speed;
					}
				}

				if (keys[DIK_S] || stickPosY >= 3000) {
					leftBottomY = ((player.pos.y + player.speed) + player.radius - 1) / blockSize;
					rightBottomY = ((player.pos.y + player.speed) + player.radius - 1) / blockSize;
					//ブロックに当たった時
					if (map1[leftBottomY][leftBottomX] == BLOCK) {
						player.pos.x = playerPosOldX;
						player.pos.y = playerPosOldY;
					}
					else if (map1[rightBottomY][rightBottomX] == BLOCK) {
						player.pos.x = playerPosOldX;
						player.pos.y = playerPosOldY;
					}
					else {
						player.pos.y += player.speed;
					}
				}

				if (keys[DIK_A] || stickPosX <= -3000) {
					leftTopX = ((player.pos.x - player.speed) - player.radius) / blockSize;
					leftBottomX = ((player.pos.x - player.speed) - player.radius) / blockSize;
					//ブロックに当たった時
					if (map1[leftTopY][leftTopX] == BLOCK) {
						player.pos.x = playerPosOldX;
						player.pos.y = playerPosOldY;
					}
					else if (map1[leftBottomY][leftBottomX] == BLOCK) {
						player.pos.x = playerPosOldX;
						player.pos.y = playerPosOldY;
					}
					else {
						player.pos.x -= player.speed;
					}
				}

				if (keys[DIK_D] || stickPosX >= 3000) {
					rightTopX = ((player.pos.x + player.speed) + player.radius - 1) / blockSize;
					rightBottomX = ((player.pos.x + player.speed) + player.radius - 1) / blockSize;
					//ブロックに当たった時
					if (map1[rightTopY][rightTopX] == BLOCK) {
						player.pos.x = playerPosOldX;
						player.pos.y = playerPosOldY;
					}
					else if (map1[rightBottomY][rightBottomX] == BLOCK) {
						player.pos.x = playerPosOldX;
						player.pos.y = playerPosOldY;
					}
					else {
						player.pos.x += player.speed;
					}
					//ゴール
					if (map1[rightTopY][rightTopX] == Galle) {
						galle = 1;
					}
					else if (map1[rightBottomY][rightBottomX] == Galle) {
						galle = 1;
					}

				}
			}
			//血の判定
			if (map1[leftTopY][leftTopX] == BLOOD) {

				if (keys[DIK_RETURN] == 0 && preKeys[DIK_RETURN] || Novice::IsTriggerButton(0, kPadButton10)) {
					map1[leftTopY][leftTopX] = NONE;
					isBlood = 1;
				}

			}
			else
				if (map1[leftBottomY][leftBottomX] == BLOOD) {
					if (keys[DIK_RETURN] == 0 && preKeys[DIK_RETURN] || Novice::IsTriggerButton(0, kPadButton10)) {
						map1[leftBottomY][leftBottomX] = NONE;
						isBlood = 1;
					}

				}
				else
					if (map1[rightTopY][rightTopX] == BLOOD) {
						if (keys[DIK_RETURN] == 0 && preKeys[DIK_RETURN] || Novice::IsTriggerButton(0, kPadButton10)) {
							map1[rightTopY][rightTopX] = NONE;
							isBlood = 1;
						}

					}
					else
						if (map1[rightBottomY][rightBottomX] == BLOOD) {
							if (keys[DIK_RETURN] == 0 && preKeys[DIK_RETURN] || Novice::IsTriggerButton(0, kPadButton10)) {
								map1[rightBottomY][rightBottomX] = NONE;
								isBlood = 1;
							}

						}
			if (isBlood == 1) {

				playerLife += 300;
				isBlood = 0;
			}


			if (galle == 0) {

				if (isbulletshot == 0) {
					if (keys[DIK_A] || stickPosX <= -3000) {
						charaDir = LEFT;
					}
					if (keys[DIK_D] || stickPosX >= 3000) {
						charaDir = RIGHT;
					}
				}
				if (canShot == 1) {
					//プレイヤーが左向きに弾を撃つ処理
					if (charaDir == LEFT) {
						if (keys[DIK_SPACE] == 0 && preKeys[DIK_SPACE] || Novice::IsTriggerButton(0, kPadButton11)) {
							if (isbulletshot == 0) {
								isbulletshot = 1;
								playerBulletPosX = player.pos.x;
								playerBulletPosY = player.pos.y;
								playerLife -= 30;
							}
						}
						if (isbulletshot == 1) {
							playerBulletPosX = playerBulletPosX - bulletspeed;
						}
					}

					//プレイヤーが右向きに弾を撃つ処理
					else if (charaDir == RIGHT) {
						if (keys[DIK_SPACE] == 0 && preKeys[DIK_SPACE] || Novice::IsTriggerButton(0, kPadButton11)) {
							if (isbulletshot == 0) {
								isbulletshot = 1;
								playerBulletPosX = player.pos.x;
								playerBulletPosY = player.pos.y;
								playerLife -= 30;
							}
						}
						if (isbulletshot == 1) {
							playerBulletPosX = playerBulletPosX + bulletspeed;
						}
					}

				}
			}
			//左向きの当たり判定
			if (charaDir == LEFT) {
				int tmpPosX = playerBulletPosX - bulletRadius;
				int tmpPosY = playerBulletPosY - bulletRadius;
				int tmpPosY1 = playerBulletPosY + bulletRadius;

				//弾の判定
				if (map1[tmpPosY / 128][tmpPosX / 128] == BLOCK || map1[tmpPosY1 / 128][tmpPosX / 128] == BLOCK) {

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
							particle1[num].possition.x = playerBulletPosX;
							particle1[num].possition.y = playerBulletPosY;
							if (degree > 360.0f) {
								degree = 0;
								break;
							}
						}
					}


					isbulletshot = 0;
					playerBulletPosX = player.pos.x;
					playerBulletPosY = player.pos.y;

				}
			}

			//右向きの当たり判定処理
			if (charaDir == RIGHT) {
				int tmpPosX = playerBulletPosX + bulletRadius;
				int tmpPosY = playerBulletPosY - bulletRadius;
				int tmpPosY1 = playerBulletPosY + bulletRadius;

				//弾の判定
				if (map1[tmpPosY / 128][tmpPosX / 128] == BLOCK || map1[tmpPosY1 / 128][tmpPosX / 128] == BLOCK) {

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
							particle1[num].possition.x = playerBulletPosX;
							particle1[num].possition.y = playerBulletPosY;
							degree += 7.2f + (rand() % 10 - 4);
							if (degree > 360.0f) {
								degree = 0;
								break;
							}
						}
					}

					isbulletshot = 0;
					playerBulletPosX = player.pos.x;
					playerBulletPosY = player.pos.y;

				}

			}

			for (int num = 0; num < NUM1; num++) {
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
			if (galle == 1) {
				Novice::ScreenPrintf(0, 0, "galle 1 　");
				galleTimer += 1;
				player.pos.x += player.speed;
				if (kWindowWidth + player.radius < player.pos.x) {
					if (galleTimer >= 120) {
						gamescene = RESULT1;
					}
				}



			}

			//スクロール処理
			if (player.pos.x >= kWindowWidth + scrollStartX) {
				scrollX = kWindowWidth;
			}
			else if (player.pos.x >= scrollStartX) {
				scrollX = player.pos.x - scrollStartX;
			}
			
			break;

		case RESULT1:
			galleTimer = 0;
			galle = 0;
			charaDir = RIGHT;

			playerLife = 1000;

			//スクロール処理
			scrollStartX = 400;
			lineY = 0;

			scrollX = 0;

			monitorX = 0;

			//スティック操作
			stickPosX = 0;
			stickPosY = 0;

			//コントローラーのボタン宣言		
			int isBButtonPress = 0;//Bボタン
			int isAButtonPress = 0;//Aボタン
			int isStartButtonPress = 0;//Startボタン

			/***************
			超音波の宣言ここから
			*******************/
			playerBulletPosX = -200;
			playerBulletPosY = -200;
			bulletspeed = 10;
			bulletRadius = 32;
			isbulletshot = 0;
			bulletMonitorX = 0;
			/*******************
			超音波の宣言ここまで
			*******************/
			//クールタイム
			canShot = false;
			canShotTime = 10;

			if (keys[DIK_SPACE] || Novice::IsTriggerButton(0, kPadButton11)) {
				gamescene = STAGE2;
			}

			break;

		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		switch (gamescene)
		{
		case TITLE:



			break;

		case TUTORIAL:

			//ブロックの描画
			for (int y = 0; y < 8; y++) {
				for (int x = 0; x < 30; x++) {
					if (map[y][x] == 1) {
						Novice::DrawSprite(
							x * 128 - scrollX, y * 128, gh1, 1, 1, 0.0f, WHITE);
					}
					if (map[y][x] == 2) {
						monitorX = x * 128 - scrollX;
						Novice::DrawSprite(
							monitorX, y * 128, gh1, 1, 1, 0.0f, RED);
					}
					if (map[y][x] == 3) {
						monitorX = x * 128 - scrollX;
						Novice::DrawSprite(
							monitorX, y * 128, gh1, 1, 1, 0.0f, BLUE);
					}
				}
			}

			Novice::DrawBox(900, 50, playerLife, 50, 0.0f, WHITE, kFillModeSolid);

			if (isbulletshot == 1) {
				if (charaDir == RIGHT) {
					Novice::DrawBox(playerBulletPosX - scrollX - bulletRadius, playerBulletPosY - bulletRadius, bulletRadius * 2, bulletRadius * 2, 0.0f, 0xFFFFFFFF, kFillModeSolid);
				}
				else if (charaDir == LEFT) {
					Novice::DrawBox(playerBulletPosX - scrollX - bulletRadius, playerBulletPosY - bulletRadius, bulletRadius * 2, bulletRadius * 2, 0.0f, 0xFFFFFFFF, kFillModeSolid);
				}
			}

			for (int num = 0; num < NUM1; num++) {
				if (particle1[num].isActive == 1) {
					Novice::DrawBox(particle1[num].possition.x - scrollX - particle1[num].width / 2, particle1[num].possition.y - particle1[num].width / 2,
						particle1[num].width, particle1[num].width, 0.0f, particle1[num].color, kFillModeSolid);
				}
			}

			Novice::DrawEllipse(player.pos.x - scrollX, player.pos.y, player.radius, player.radius, 0.0f, RED, kFillModeSolid);

			break;

		case GAMEOVER:

			break;

		case RESULT:

			break;

		case STAGE1:

			//ブロックの描画
			for (int y = 0; y < 8; y++) {
				for (int x = 0; x < 30; x++) {
					if (map1[y][x] == 1) {
						Novice::DrawSprite(
							x * 128 - scrollX, y * 128, gh1, 1, 1, 0.0f, WHITE);
					}
					if (map1[y][x] == 2) {
						monitorX = x * 128 - scrollX;
						Novice::DrawSprite(
							monitorX, y * 128, gh1, 1, 1, 0.0f, RED);
					}
					if (map1[y][x] == 3) {
						monitorX = x * 128 - scrollX;
						Novice::DrawSprite(
							monitorX, y * 128, gh1, 1, 1, 0.0f, BLUE);
					}
				}
			}

			Novice::DrawBox(900, 50, playerLife, 50, 0.0f, WHITE, kFillModeSolid);

			if (isbulletshot == 1) {
				if (charaDir == RIGHT) {
					Novice::DrawBox(playerBulletPosX - scrollX - bulletRadius, playerBulletPosY - bulletRadius, bulletRadius * 2, bulletRadius * 2, 0.0f, 0xFFFFFFFF, kFillModeSolid);
				}
				else if (charaDir == LEFT) {
					Novice::DrawBox(playerBulletPosX - scrollX - bulletRadius, playerBulletPosY - bulletRadius, bulletRadius * 2, bulletRadius * 2, 0.0f, 0xFFFFFFFF, kFillModeSolid);
				}
			}

			for (int num = 0; num < NUM1; num++) {
				if (particle1[num].isActive == 1) {
					Novice::DrawBox(particle1[num].possition.x - scrollX - particle1[num].width / 2, particle1[num].possition.y - particle1[num].width / 2,
						particle1[num].width, particle1[num].width, 0.0f, particle1[num].color, kFillModeSolid);
				}
			}

			Novice::DrawEllipse(player.pos.x - scrollX, player.pos.y, player.radius, player.radius, 0.0f, RED, kFillModeSolid);

			break;

		case RESULT1:

			break;

		}

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0 || Novice::IsTriggerButton(0, kPadButton4)) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
