#pragma once

// 前方宣言
class C_State;

class C_SceneManager
{
public:

	// シーンの種類
	enum E_SceneType
	{
		ME_Title,
		ME_MainGame,
		ME_Result,
		ME_GameOver
	};

	static C_SceneManager& Instance()
	{
		static C_SceneManager Instance;
		return Instance;
	}

	// 初期化
	void Init();

	// 更新前に行う更新処理
	void PreUpdate();

	// 更新処理
	void Update();

	// 描画
	void Draw();

	// デバッグ表示させる内容
	void ImGuiUpdate();

	// シーンを移動したい時にここに該当するシーンを入れる。
	void SetterNextScene(E_SceneType A_NextScene) { M_NextSceneType = A_NextScene; }

	// 現在のシーンを確認できる。
	E_SceneType GetterCrurrentSceneType()const { return M_CurrentSceneType; }

private:

	// コンストラクタとデストラクタ。
	C_SceneManager();
	~C_SceneManager();

	// 解放処理
	void Release();
	
	// シーン遷移をここで行う。
	void  ChangeScene(E_SceneType A_NextSceneType);

	// ここにアップキャストしてシーンのクラスを一括で扱う。
	std::shared_ptr<C_State>M_CurrentScene;
	// 現在のシーン
	E_SceneType M_CurrentSceneType = E_SceneType::ME_Title;
	// 移りたいシーンをここに入れる。
	E_SceneType M_NextSceneType = M_CurrentSceneType;
};

#define SCENEMANAGER C_SceneManager::Instance() // インスタンスがなくてもSCENEMANAGERで呼び出せる(シングルトンってやつ)