#include <Windows.h>//ウィンドウの作成や操作、メッセージ処理などのOSレベルの操作
#include <tchar.h>//_Tマクロを利用しマルチバイト文字セットとUnicode文字セットの両方をサポートするため
#ifdef _DEBUG //デバッグビルド時にのみ _DEBUG 起動
#include <iostream>
#endif

using namespace std;

// @brief コンソール画面にフォーマット付き文字列を表示
// @param format フォーマット (%d とか %f とかの)
// @param 可変長引数
// @ remarks この関数はデバッグ用です。デバッグ時にしか動作しない
void DebugOutputFormatString(const char* format, ...)
{
#ifdef _DEBUG
	va_list valist;//可変長引数のリストを管理
	va_start(valist, format);//valistを初期化し、追加の引数へのアクセスを可能にする
	printf(format, valist);
	va_end(valist);
#endif
}

//ウィンドウに送られるメッセージを処理する関数
LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//ウィンドウが破棄されたら呼ばれる
	if (msg == WM_DESTROY)
	{
		PostQuitMessage(0);// OSに対して「もうこのアプリは終わる」と伝える
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);//既定の処理を行う
}

//デバッグモードではコンソールアプリケーション用の main 関数がエントリーポイント
//リリースモードではGUIアプリケーションのエントリーポイントである WinMain
#ifdef _DEBUG
int main()
{
	#else
	int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
	{
	#endif
	const unsigned int window_width = 1280;//ウィンドウの幅
	const unsigned int window_Height = 720;//ウィンドウの高

	//ウィンドウクラスの生成＆登録
	WNDCLASSEX w = {};

	w.cbSize = sizeof(WNDCLASSEX);//構造体のサイズを指定
	w.lpfnWndProc = (WNDPROC)WindowProcedure;//コールバック関数の指定(メッセージ処理用)
	w.lpszClassName = _T("DX12Sample");//アプリケーションクラス名（今後ライブラリを作るときにそれ用の名前に変える）
	w.hInstance = GetModuleHandle(nullptr);//ハンドルの取得

	RegisterClassEx(&w);//ウィンドウサイズを決める

	RECT wrc = { 0, 0, window_width, window_Height };//描画可能領域のサイズを設定

	//関数を使ってウィンドウのサイズを補正する(これにより、タイトルバーや境界線の分を考慮したサイズに)
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);
	//ウィンドウオブジェクトの生成
	HWND hwnd = CreateWindow(w.lpszClassName,//クラス名指定
		_T("DX12 テスト"),//タイトルバー文字
		WS_OVERLAPPEDWINDOW,//タイトルバーと境界線があるウィンドウ
		CW_USEDEFAULT,//表示 x 座標は OS におまかせ
		CW_USEDEFAULT,//表示 y 座標は OS におまかせ
		wrc.right - wrc.left,//ウィンドウ幅
		wrc.bottom - wrc.top,//ウィンドウ高
		nullptr,//親ウィンドウハンドル
		nullptr,//メニューハンドル
		w.hInstance,//呼び出しアプリケーションハンドル
		nullptr);//追加パラメータ

	//ウィンドウ表示
	ShowWindow(hwnd, SW_SHOW);

	//メッセージループ
	while (true)
	{
		MSG msg;//メッセージの種類やウィンドウハンドル、送信者などの情報
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			//アプリケーションが終わるときに message が　WM_QUIT　になる
			if (msg.message == WM_QUIT)
			{
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	//もうこのクラスは使わないので登録解除する
	UnregisterClass(w.lpszClassName, w.hInstance);

	return 0;
}