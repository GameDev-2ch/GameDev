#include "DxLib.h"

// プログラムは WinMain から始まります
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
						LPSTR lpCmdLine, int nCmdShow )
{
	int color;

	// ウィンドウモードに変更
	ChangeWindowMode( TRUE );

	SetGraphMode(512, 480, 32);

	if( DxLib_Init() == -1 )		// ＤＸライブラリ初期化処理
	{
		return -1 ;			// エラーが起きたら直ちに終了
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

	DxLib_End() ;				// ＤＸライブラリ使用の終了処理

	return 0 ;				// ソフトの終了 
}
