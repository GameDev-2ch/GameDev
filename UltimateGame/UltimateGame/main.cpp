#include "DxLib.h"

#include "game.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
						LPSTR lpCmdLine, int nCmdShow )
{

	int lastFrameTime, timeCount, frameCount, currentTime;
	float fps;
	
	// �E�B���h�E���[�h�ɕύX
	ChangeWindowMode( TRUE );

	SetGraphMode(512, 480, 32);
	SetWaitVSyncFlag(FALSE);

	if( DxLib_Init() == -1 )		// �c�w���C�u��������������
	{
		return -1 ;			// �G���[���N�����璼���ɏI��
	}

	Game game(512, 480, _T("player.png"), _T("tama.png"), 3000);

	timeCount = 0;
	frameCount = 0;
	fps = 0.0f;
	lastFrameTime = GetNowCount();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		if( CheckHitKey( KEY_INPUT_ESCAPE ) == 1 )
		{
			break;
		}

		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();

		currentTime = GetNowCount();


		// �Q�[������
		game.update(currentTime - lastFrameTime);

		// fps�\��
		timeCount += currentTime - lastFrameTime;
		frameCount++;
		if (timeCount > 1000){
			fps = frameCount * 1000.0f / timeCount;
			frameCount = timeCount = 0;
		}

		DrawFormatString(0, 0, GetColor(255, 255, 255), _T("FPS:%.1f"), fps);
		DrawFormatString(0, 16, GetColor(255, 255, 255), _T("�ړ��@�@:ASDW"));
		DrawFormatString(0, 32, GetColor(255, 255, 255), _T("�V���b�g:���N���b�N"));
		lastFrameTime = currentTime;

		ScreenFlip();

	}

	DxLib_End() ;				// �c�w���C�u�����g�p�̏I������

	return 0 ;				// �\�t�g�̏I�� 
}
