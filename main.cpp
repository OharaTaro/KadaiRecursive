#include "DxLib.h"

#include "game.h"
#include "MineSweeper.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// window���[�h�ݒ�
	ChangeWindowMode(Game::kWindowMode);
	// �E�C���h�E���ݒ�
	SetMainWindowText(Game::kTitleText);
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	///////////////////////////////////////////////////
	// ���
	///////////////////////////////////////////////////

	// �}�C���X�C�[�p�[�̎������s��

	// ���1
	// open�����s�����Ƃ���0�̃}�X���J�����炻�̎���8�}�X���J��
	// �������ĊJ����8�}�X�̒���0������ꍇ�͓��l�Ɏ���8�}�X���J���Ă���
	// ��L�𖞂����������ċA��p���čs��

	// ���2
	// open�̏������ׂ��\�Ȍ��菬��������

	MineSweeper game;
	game.create();

	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// ��ʂ̃N���A
		ClearDrawScreen();

		game.update();
		game.draw();

		//����ʂ�\��ʂ����ւ���
		ScreenFlip();

		// esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}