#include"Luminous.h"

// �R���X�g���N�^
Luminous::Luminous() {

	this->Initialize();
}

// �f�X�g���N�^
Luminous::~Luminous() {

}


// ������
void Luminous::Initialize() {

	// X���W
	posX_ = 640;
	// Y���W
	posY_ = 360;

	// �t�F�[�h�t���[�����̌W��(1.0~2.0)
	fadeCoef_ = 2.0f;
	// �t�F�[�h�̃t���[����
	fadeTime_ = (64 * fadeCoef_);
	// �t�F�[�h�̃t���[������ۑ�
	fadeTimeIndex_ = (64 * fadeCoef_);

	// �t�F�[�h�����̃o�O��h�~����( coef = 2.0f �̎��̂� )
	if (fadeCoef_ == 2.0f) {
		fadeCoef_ = 1.99f;
	}

	// ���x
	value_ = 0x000000FF;
	// ���x�Œ�l
	valueMax_ = 0x000000FF;
	// ���x�ő�l
	valueMin_ = 0x00000000;

	// �t�F�[�h�C�������H
	isFadeIn_ = false;
	// �t�F�[�h�A�E�g�����H
	isFadeOut_ = false;
	// �_�Œ���?
	isFlashing = false;

}

// �X�V
void Luminous::Update() {
	
	// �t�F�[�h�C������
	if (isFadeIn_) {

		// �^�C�}�[�̐��l��0�łȂ��ꍇ�����x������������
		if (fadeTime_ > 0) {

			// �^�C�}�[�̒l������
			fadeTime_--;

			// �����ɂ���
			if (value_ > valueMin_) {
				value_ -= (valueMax_ / fadeTimeIndex_) * fadeCoef_;
			}

			// �����x�����̒l�ɂȂ����瓧�����������~
			else if (value_ <= valueMin_) {
				value_ = valueMin_;
				isFadeIn_ = false;
				fadeTime_ = fadeTimeIndex_;
			}

		}
		else {

			// �����x�����������ł���Ή����ɍĐݒ�
			if (value_ < valueMin_) {
				value_ = valueMin_;
			}

			//�^�C�}�[�̐��l�����Ƃɖ߂�
			fadeTime_ = fadeTimeIndex_;

			// �t�F�[�h�C�����~
			isFadeIn_ = false;

		}
	}

	// �t�F�[�h�A�E�g����
	if (isFadeOut_) {

		// �^�C�}�[�̐��l��0�łȂ��ꍇ�����x������������
		if (fadeTime_ > 0) {

			// �^�C�}�[�̒l������
			fadeTime_--;

			// �s�����ɂ���
			if (value_ < valueMax_) {
				value_ += (valueMax_ / fadeTimeIndex_) * (fadeCoef_* fadeCoef_);
			}

			// �����x�����̒l�ɂȂ�����s�������������~
			else if (value_ >= valueMax_) {
				value_ = valueMax_;
				isFadeOut_ = false;
				fadeTime_ = fadeTimeIndex_;
			}

		}
		else {

			// �����x���������ł���Ώ���ɍĐݒ�
			if (value_ > valueMax_) {
				value_ = valueMax_;
			}

			//�^�C�}�[�̐��l�����Ƃɖ߂�
			fadeTime_ = fadeTimeIndex_;

			// �t�F�[�h�A�E�g���~
			isFadeOut_ = false;

		}
	}

	// �t���b�V������
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

		// �����x�����̒l�ɂȂ����瓧�����������~
		if (fadeTime_ == 0) {
			value_ = valueMin_;
			isFlashing = false;
			fadeTime_ = fadeTimeIndex_;
		}

		// �^�C�}�[�̒l������
		fadeTime_--;
	}
}

// �`��
void Luminous::Draw() {

	// �`����s��
	Novice::DrawSprite(
		0,0,
		FADE_IMAGE[0],
		2,2,0.0f,
		value_
	);


	// �p�����[�^��\��

	//// ���݂̖��x��\��
	//Novice::ScreenPrintf(10, 410, "light:%x", value_);
	//Novice::ScreenPrintf(10, 430, "lightMax:%x", valueMax_);
	//Novice::ScreenPrintf(10, 450, "lightMin:%x", valueMin_);

	//// �t�F�[�h���s�����Ԃ�\��
	//Novice::ScreenPrintf(1000, 410, "Time:%d", fadeTime_);
	//Novice::ScreenPrintf(1000, 430, "TimeIndex:%d", fadeTimeIndex_);

	//// ���ݖ��x�ύX�����ǂ���
	//Novice::ScreenPrintf(10, 470, "isMove:%d", GetFlashing());
	
}

/// ���S���W��ݒ�
void Luminous::SetPosition(float posX, float posY) {

	// X���W���v���C���[��X���W�ɍ��킹��
	posX_ = posX - radX_;
	// Y���W���v���C���[��Y���W�ɍ��킹��
	posY_ = posY + radY_;
}

/// �t�F�[�h�����̋N�����s��
void Luminous::SetFade(bool mode) {

	// �t�F�[�h���ł͂Ȃ��ꍇ�؂�ւ��������s��
	if (isFadeIn_ == false && isFadeOut_ == false) {

		// �t�F�[�h�C��
		if (mode == true) {
			isFadeIn_ = true;
		}
		// �t�F�[�h�A�E�g
		else if (mode == false) {
			isFadeOut_ = true;
		}
	}

}

/// �t���b�V�������̋N�����s��
void Luminous::SetFlash() {

	// ���Ԃ�ݒ�
	fadeTime_ = 120;

	// �F��ύX
	Luminous::value_ = 0xFF000000;

	// �t���b�V��������
	isFlashing = true;

}

/// �t�F�[�h�̃t���[������ݒ�
void Luminous::SetFadeTime(float coef) {

	// �t�F�[�h�t���[�����̌W��(1.0~2.0)
	fadeCoef_ = coef;
	// �t�F�[�h�̃t���[����
	fadeTime_ = (64 * fadeCoef_);
	// �t�F�[�h�̃t���[������ۑ�
	fadeTimeIndex_ = (64 * fadeCoef_);

	// �t�F�[�h�����̃o�O��h�~����( coef = 2.0f �̎��̂� )
	if (fadeCoef_ == 2.0f) {
		fadeCoef_ = 1.99f;
	}

}

/// ���x�̍ő�l�ƍŒ�l��ݒ�
void Luminous::SetValue(unsigned int Max, unsigned int Min) {

	// ���x�Œ�l�̍X�V
	valueMax_ = Max;
	// ���x�ő�l�̍X�V
	valueMin_ = Min;

}

/// �t�F�[�h�������N���Ă��邩�ǂ����擾����
bool Luminous::GetFade() {

	// �t�F�[�h���ł����true��Ԃ�
	if (isFadeIn_ == true || isFadeOut_ == true) {
		return true;
	}

	// �����łȂ��ꍇ��false��Ԃ�
	return false;
}

/// �_�ŏ������N���Ă��邩�ǂ����擾����
bool Luminous::GetFlashing() {
	
	// �_�Œ���true��Ԃ�
	if (isFlashing) {
		return true;
	}

	// �����łȂ��ꍇ��false��Ԃ�
	return false;
}