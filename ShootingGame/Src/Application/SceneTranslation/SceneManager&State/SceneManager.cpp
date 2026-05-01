#include "SceneManager.h"

// 各シーンのクラス
#include "../Title/TitleScene.h"
#include "../MainGame/MainGameScene.h"
#include "../Result/ResultScene.h"
#include "../GameOver/GameOverScene.h"

// このクラスが生成された時に動かしたいものをここに(コンストラクタ)
C_SceneManager::C_SceneManager()
{

}

// このクラスが作成された時に動かしたいものをここに(コンストラクタ)
C_SceneManager::~C_SceneManager()
{
	// 解放処理
	Release();

}

// 初期化内容
void C_SceneManager::Init()
{
	ChangeScene(M_CurrentSceneType);
}

// 更新前に行いたい更新処理はここに書く。
void C_SceneManager::PreUpdate()
{
	// 現在のシーンとは別のシーンへ移りたいと予約が入ればシーン遷移を行う。
	if (M_CurrentSceneType != M_NextSceneType)
	{
		ChangeScene(M_NextSceneType);
	}
}

// 更新内容
void C_SceneManager::Update()
{
	M_CurrentScene->Update();
}

// 描画内容
void C_SceneManager::Draw()
{
	M_CurrentScene->Draw();
}

// デバッグに表示したいものはここに。
void C_SceneManager::ImGuiUpdate()
{
	M_CurrentScene->ImGuiUpdate();
}

// 解放処理
void C_SceneManager::Release()
{

}

void C_SceneManager::ChangeScene(E_SceneType A_NextSceneType)
{
	// 遷移したいシーンのインスタンスを生成する。
	switch (A_NextSceneType)
	{
	case E_SceneType::ME_Title:
		{
			M_CurrentScene = std::make_shared<C_TitleScene>();
			break;
		}
	case E_SceneType::ME_MainGame:
		{
			M_CurrentScene = std::make_shared<C_MainGameScene>();
			break;
		}
	case E_SceneType::ME_Result:
		{
			M_CurrentScene = std::make_shared<C_ResultScene>();
			break;
		}
	case E_SceneType::ME_GameOver:
		{
			M_CurrentScene = std::make_shared<C_GameOverScene>();
			break;
		}
	}

	// インスタンスを生成できたら初期化する。
	M_CurrentScene->Init();

	// 現在のシーンを更新する。
	M_CurrentSceneType = A_NextSceneType;

}