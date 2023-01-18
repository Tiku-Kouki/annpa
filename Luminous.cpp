#include"Luminous.h"

// コンストラクタ
Luminous::Luminous() {

	this->Initialize();
}

// デストラクタ
Luminous::~Luminous() {

}


// 初期化
void Luminous::Initialize() {

	// X座標
	posX_ = 640;
	// Y座標
	posY_ = 360;

	// フェードフレーム数の係数(1.0~2.0)
	fadeCoef_ = 2.0f;
	// フェードのフレーム数
	fadeTime_ = (64 * fadeCoef_);
	// フェードのフレーム数を保存
	fadeTimeIndex_ = (64 * fadeCoef_);

	// フェード処理のバグを防止する( coef = 2.0f の時のみ )
	if (fadeCoef_ == 2.0f) {
		fadeCoef_ = 1.99f;
	}

	// 明度
	value_ = 0x000000FF;
	// 明度最低値
	valueMax_ = 0x000000FF;
	// 明度最大値
	valueMin_ = 0x00000000;

	// フェードイン中か？
	isFadeIn_ = false;
	// フェードアウト中か？
	isFadeOut_ = false;
	// 点滅中か?
	isFlashing = false;

}

// 更新
void Luminous::Update() {
	
	// フェードイン処理
	if (isFadeIn_) {

		// タイマーの数値が0でない場合透明度を減少させる
		if (fadeTime_ > 0) {

			// タイマーの値を減少
			fadeTime_--;

			// 透明にする
			if (value_ > valueMin_) {
				value_ -= (valueMax_ / fadeTimeIndex_) * fadeCoef_;
			}

			// 透明度が一定の値になったら透明化処理を停止
			else if (value_ <= valueMin_) {
				value_ = valueMin_;
				isFadeIn_ = false;
				fadeTime_ = fadeTimeIndex_;
			}

		}
		else {

			// 透明度が下限未満であれば下限に再設定
			if (value_ < valueMin_) {
				value_ = valueMin_;
			}

			//タイマーの数値をもとに戻す
			fadeTime_ = fadeTimeIndex_;

			// フェードインを停止
			isFadeIn_ = false;

		}
	}

	// フェードアウト処理
	if (isFadeOut_) {

		// タイマーの数値が0でない場合透明度を減少させる
		if (fadeTime_ > 0) {

			// タイマーの値を減少
			fadeTime_--;

			// 不透明にする
			if (value_ < valueMax_) {
				value_ += (valueMax_ / fadeTimeIndex_) * (fadeCoef_* fadeCoef_);
			}

			// 透明度が一定の値になったら不透明化処理を停止
			else if (value_ >= valueMax_) {
				value_ = valueMax_;
				isFadeOut_ = false;
				fadeTime_ = fadeTimeIndex_;
			}

		}
		else {

			// 透明度が上限より上であれば上限に再設定
			if (value_ > valueMax_) {
				value_ = valueMax_;
			}

			//タイマーの数値をもとに戻す
			fadeTime_ = fadeTimeIndex_;

			// フェードアウトを停止
			isFadeOut_ = false;

		}
	}

	// フラッシュ処理
	if (isFlashing) {

		if (fadeTime_ >= 90) {
			value_ += 0x00000002;
		}

		else if (fadeTime_ >= 60) {
			value_ -= 0x00000002;
		}
		
		else if (fadeTime_ >= 30) {
			value_ += 0x00000003;
		}

		else if (fadeTime_ > 0) {
			value_ -= 0x00000003;
		}

		// 透明度が一定の値になったら透明化処理を停止
		if (fadeTime_ == 0) {
			value_ = valueMin_;
			isFlashing = false;
			fadeTime_ = fadeTimeIndex_;
		}

		// タイマーの値を減少
		fadeTime_--;
	}
}

// 描画
void Luminous::Draw() {

	// 描画を行う
	Novice::DrawSprite(
		0,0,
		FADE_IMAGE[0],
		2,2,0.0f,
		value_
	);


	// パラメータを表示

	//// 現在の明度を表示
	//Novice::ScreenPrintf(10, 410, "light:%x", value_);
	//Novice::ScreenPrintf(10, 430, "lightMax:%x", valueMax_);
	//Novice::ScreenPrintf(10, 450, "lightMin:%x", valueMin_);

	//// フェードを行う時間を表示
	//Novice::ScreenPrintf(1000, 410, "Time:%d", fadeTime_);
	//Novice::ScreenPrintf(1000, 430, "TimeIndex:%d", fadeTimeIndex_);

	//// 現在明度変更中かどうか
	//Novice::ScreenPrintf(10, 470, "isMove:%d", GetFlashing());
	
}

/// 中心座標を設定
void Luminous::SetPosition(float posX, float posY) {

	// X座標をプレイヤーのX座標に合わせる
	posX_ = posX - radX_;
	// Y座標をプレイヤーのY座標に合わせる
	posY_ = posY + radY_;
}

/// フェード処理の起動を行う
void Luminous::SetFade(bool mode) {

	// フェード中ではない場合切り替え処理を行う
	if (isFadeIn_ == false && isFadeOut_ == false) {

		// フェードイン
		if (mode == true) {
			isFadeIn_ = true;
		}
		// フェードアウト
		else if (mode == false) {
			isFadeOut_ = true;
		}
	}

}

/// フラッシュ処理の起動を行う
void Luminous::SetFlash() {

	// 時間を設定
	fadeTime_ = 120;

	// 色を変更
	Luminous::value_ = 0xFF000000;

	// フラッシュさせる
	isFlashing = true;

}

/// フェードのフレーム数を設定
void Luminous::SetFadeTime(float coef) {

	// フェードフレーム数の係数(1.0~2.0)
	fadeCoef_ = coef;
	// フェードのフレーム数
	fadeTime_ = (64 * fadeCoef_);
	// フェードのフレーム数を保存
	fadeTimeIndex_ = (64 * fadeCoef_);

	// フェード処理のバグを防止する( coef = 2.0f の時のみ )
	if (fadeCoef_ == 2.0f) {
		fadeCoef_ = 1.99f;
	}

}

/// 明度の最大値と最低値を設定
void Luminous::SetValue(unsigned int Max, unsigned int Min) {

	// 明度最低値の更新
	valueMax_ = Max;
	// 明度最大値の更新
	valueMin_ = Min;

}

/// フェード処理が起きているかどうか取得する
bool Luminous::GetFade() {

	// フェード中であればtrueを返す
	if (isFadeIn_ == true || isFadeOut_ == true) {
		return true;
	}

	// そうでない場合はfalseを返す
	return false;
}

/// 点滅処理が起きているかどうか取得する
bool Luminous::GetFlashing() {
	
	// 点滅中はtrueを返す
	if (isFlashing) {
		return true;
	}

	// そうでない場合はfalseを返す
	return false;
}