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

	enum E_SceneType
	{
		ME_Title,
		ME_MainGame,
		ME_Result,
		ME_GameOver
	};

	// ゲームの場面切り替え(シーン遷移)を一つ一つ行う為のキーフラグ
	bool	M_ChangeSceneFlg;

	// 現在のシーン(ゲーム場面)を監視させる
	int		M_NowScene;

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

	// ゲームの場面切り替え(シーン遷移)を行うかここで判定する
	void JudgeChangeScene();

	// ゲッター
	// 画面端の座標を返す。
		// 上
		static const int Getter_ScreenSize_Top()			{ return M_ScreenSize_Top; }
		// 下
		static const int Getter_ScreenSize_Bottom()	{ return M_ScreenSize_Bottom; }	
		// 右
		static const int Getter_ScreenSize_Right()		{ return M_ScreenSize_Right; }		
		// 左
		static const int Getter_ScreenSize_Left()			{ return M_ScreenSize_Left; }		

private:

	Scene() {}

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
