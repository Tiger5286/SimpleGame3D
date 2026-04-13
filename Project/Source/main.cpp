#include "DxLib.h"
#include "Game.h"
#include <memory>

#include "Application.h"

// プログラムは WinMain から始まる
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// アプリケーションのインスタンスを取得
	auto& app = Application::GetInstance();
	// アプリケーションの初期化
	if (!app.Init())
	{
		return -1;			// 初期化に失敗したら終了
	}
	app.Run();				// メインループを開始
	app.Terminate();		// 終了処理

	return 0;				// ソフトの終了 
}