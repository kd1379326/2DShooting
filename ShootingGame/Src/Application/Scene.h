// C_・・・クラス
// M_・・・メンバ
// A_・・・引数
// E_・・・列挙体
// S_・・・構造体
// P_・・・ポインター
// F_・・・フラグ

#pragma once

class Scene
{
private:

	// 画面の端の座標
		// 上
		static const int M_ScreenSize_Top		= 360;		
		// 下
		static const int M_ScreenSize_Bottom = -360;	
		// 右
		static const int M_ScreenSize_Right	= 640;		
		// 左
		static const int M_ScreenSize_Left		= -640;		

public:

	// 初期設定
	void Init();

	// 解放
	void Release();

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D();

	// GUI処理
	void ImGuiUpdate();

	// ゲッター
	// 画面端の座標を返す。
		// 上
		int Getter_ScreenSize_Top()			{ return M_ScreenSize_Top; }
		// 下
		int Getter_ScreenSize_Bottom()		{ return M_ScreenSize_Bottom; }	
		// 右
		int Getter_ScreenSize_Right()			{ return M_ScreenSize_Right; }		
		// 左
		int Getter_ScreenSize_Left()			{ return M_ScreenSize_Left; }		

private:

	Scene() {}

public:
	static Scene& Instance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::Instance()
