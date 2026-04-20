// C_・・・クラス
// M_・・・メンバ
// A_・・・引数
// E_・・・列挙体
// S_・・・構造体
// P_・・・ポインター

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
	KdTexture l;
	Math::Matrix m;

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

	// ゲームの場面を切り替える(シーン遷移)
	void ChangeScene();

	// ゲームの場面切り替え(シーン遷移)を行うかここで判定する
	void JudgeChangeScene();

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
