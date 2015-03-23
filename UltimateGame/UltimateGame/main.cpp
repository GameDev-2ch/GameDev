#include "DxLib.h"

// プログラムは WinMain から始まります
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
						LPSTR lpCmdLine, int nCmdShow )
{

	int color;

	int lastFrameTime, timeCount, frameCount, currentTime;
	float fps;
	
	// ウィンドウモードに変更
	ChangeWindowMode( TRUE );

	SetGraphMode(512, 480, 32);

	if( DxLib_Init() == -1 )		// ＤＸライブラリ初期化処理
	{
		return -1 ;			// エラーが起きたら直ちに終了
	}

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


		// ゲーム処理
//		color = GetColor(GetRand(255), GetRand(255), GetRand(255));
//		DrawPixel( GetRand(512-1), GetRand(480-1), color );



		// fps表示
		timeCount += currentTime - lastFrameTime;
		frameCount++;
		if (timeCount > 1000){
			fps = frameCount * 1000.0f / timeCount;
			frameCount = timeCount = 0;
		}

		DrawFormatString(0, 0, GetColor(255, 255, 255), _T("FPS:%.1f"), fps);
		lastFrameTime = currentTime;

		ScreenFlip();

	}

	DxLib_End() ;				// ＤＸライブラリ使用の終了処理

	return 0 ;				// ソフトの終了 
}
