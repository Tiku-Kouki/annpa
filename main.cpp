#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h> 
#include <stdlib.h>
#include"Struct.h"
#include "Player.h"


const char kWindowTitle[] = "暗波";





// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//ファイル分けのやつ
	Luminous* luminous = new Luminous;
	Player* player = new Player(400, 512, 4.0f, 32.0f);
	Stage* stage = new Stage;

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
			player->isStartButtonPress = 1;
		}
		player->Move(keys, preKeys);
		

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		stage->Draw();
		player->Draw();

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

	delete luminous;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
