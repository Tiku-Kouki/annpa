#pragma once
#include<Novice.h>

//ウィンドウの横幅
const float kWindowWidth_ = 1920;
//ウィンドウの横幅
const float kWindowHeight_ = 1080;


class Luminous
{
private: // メンバ変数


	// 定数の宣言


// フェード用の画像
	const int FADE_IMAGE[1]{
		Novice::LoadTexture("./Resources/shadowA.png"),

	};

	// X半径
	const float radX_ = 640;
	// Y半径
	const float radY_ = 360;


	// 変数の宣言


	// X座標
	float posX_;
	// Y座標
	float posY_;

	// フェードフレーム数の係数
	float fadeCoef_;
	// フェードのフレーム数
	int fadeTime_;
	// フェードのフレーム数を保存
	int fadeTimeIndex_;

	// フェードイン中か？
	bool isFadeIn_;
	// フェードアウト中か？
	bool isFadeOut_;
	// 点滅中か？
	bool isFlashing;

public:

	// 明度
	unsigned int value_;
	// 明度最低値
	unsigned int valueMax_;
	// 明度最大値
	unsigned int valueMin_;

	


public:	// メンバ関数

	// コンストラクタ
	Luminous();
	// デストラクタ
	~Luminous();


	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();


	/// <summary>
	/// 中心座標を設定
	/// </summary>
	/// <param name="posX">プレイヤーのX座標</param>
	/// <param name="posY">プレイヤーのY座標</param>
	void SetPosition(float posX, float posY);

	/// <summary>
	/// フェード処理の起動を行う
	/// </summary>
	/// <param name="mode:"></param>
	/// <param name="">true->フェードイン</param>
	/// <param name="">false->フェードアウト</param>
	void SetFade(bool mode);

	/// <summary>
	/// フラッシュ処理の起動を行う
	/// </summary>
	void SetFlash();

	/// <summary>
	/// フェードのフレーム数を設定 (1.0 ~ 2.0)
	/// </summary>
	/// <param name="coef">フェードにかかるフレーム係数</param>
	void SetFadeTime(float coef);
	
	/// <summary>
	/// 明度の最大値と最低値を設定
	/// </summary>
	/// <param name="Max">明度最大値</param>
	/// <param name="Min">明度最低値</param>
	void SetValue(unsigned int Max, unsigned int Min);

	/// <summary>
	/// フェード処理が起きているかどうか取得する
	/// </summary>
	/// <returns>フェードイン・フェードアウトの有無</returns>
	bool GetFade();

	/// <summary>
	/// 点滅処理が起きているかどうか取得する
	/// </summary>
	/// <returns>点滅の有無</returns>
	bool GetFlashing();

};

