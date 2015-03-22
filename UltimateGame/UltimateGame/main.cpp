#include "DxLib.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
						LPSTR lpCmdLine, int nCmdShow )
{
	int color;

	// �E�B���h�E���[�h�ɕύX
	ChangeWindowMode( TRUE );

	SetGraphMode(512, 480, 32);

	if( DxLib_Init() == -1 )		// �c�w���C�u��������������
	{
		return -1 ;			// �G���[���N�����璼���ɏI��
	}

	while(1)
	{
		if( CheckHitKey( KEY_INPUT_ESCAPE ) == 1 )
		{
			break;
		}

		color = GetColor(GetRand(255), GetRand(255), GetRand(255));

		DrawPixel( GetRand(512), GetRand(480), color );
	}

	DxLib_End() ;				// �c�w���C�u�����g�p�̏I������

	return 0 ;				// �\�t�g�̏I�� 
}
