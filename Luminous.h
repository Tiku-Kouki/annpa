#pragma once
#include<Novice.h>

//�E�B���h�E�̉���
const float kWindowWidth_ = 1920;
//�E�B���h�E�̉���
const float kWindowHeight_ = 1080;


class Luminous
{
private: // �����o�ϐ�


	// �萔�̐錾


// �t�F�[�h�p�̉摜
	const int FADE_IMAGE[1]{
		Novice::LoadTexture("./Resources/shadowA.png"),

	};

	// X���a
	const float radX_ = 640;
	// Y���a
	const float radY_ = 360;


	// �ϐ��̐錾


	// X���W
	float posX_;
	// Y���W
	float posY_;

	// �t�F�[�h�t���[�����̌W��
	float fadeCoef_;
	// �t�F�[�h�̃t���[����
	int fadeTime_;
	// �t�F�[�h�̃t���[������ۑ�
	int fadeTimeIndex_;

	// �t�F�[�h�C�������H
	bool isFadeIn_;
	// �t�F�[�h�A�E�g�����H
	bool isFadeOut_;
	// �_�Œ����H
	bool isFlashing;

public:

	// ���x
	unsigned int value_;
	// ���x�Œ�l
	unsigned int valueMax_;
	// ���x�ő�l
	unsigned int valueMin_;

	


public:	// �����o�֐�

	// �R���X�g���N�^
	Luminous();
	// �f�X�g���N�^
	~Luminous();


	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Draw();


	/// <summary>
	/// ���S���W��ݒ�
	/// </summary>
	/// <param name="posX">�v���C���[��X���W</param>
	/// <param name="posY">�v���C���[��Y���W</param>
	void SetPosition(float posX, float posY);

	/// <summary>
	/// �t�F�[�h�����̋N�����s��
	/// </summary>
	/// <param name="mode:"></param>
	/// <param name="">true->�t�F�[�h�C��</param>
	/// <param name="">false->�t�F�[�h�A�E�g</param>
	void SetFade(bool mode);

	/// <summary>
	/// �t���b�V�������̋N�����s��
	/// </summary>
	void SetFlash();

	/// <summary>
	/// �t�F�[�h�̃t���[������ݒ� (1.0 ~ 2.0)
	/// </summary>
	/// <param name="coef">�t�F�[�h�ɂ�����t���[���W��</param>
	void SetFadeTime(float coef);
	
	/// <summary>
	/// ���x�̍ő�l�ƍŒ�l��ݒ�
	/// </summary>
	/// <param name="Max">���x�ő�l</param>
	/// <param name="Min">���x�Œ�l</param>
	void SetValue(unsigned int Max, unsigned int Min);

	/// <summary>
	/// �t�F�[�h�������N���Ă��邩�ǂ����擾����
	/// </summary>
	/// <returns>�t�F�[�h�C���E�t�F�[�h�A�E�g�̗L��</returns>
	bool GetFade();

	/// <summary>
	/// �_�ŏ������N���Ă��邩�ǂ����擾����
	/// </summary>
	/// <returns>�_�ł̗L��</returns>
	bool GetFlashing();

};

