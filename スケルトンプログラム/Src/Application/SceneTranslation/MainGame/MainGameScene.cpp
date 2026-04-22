#include "MainGameScene.h"

// キャラクターのクラスを取り込む
// メインキャラクター
#include "Entity_MainGame/MainCharacter/MainCharacter.h"
// 敵１
#include "Entity_MainGame/Enemy/Enemy1/Enemy1.h"

// このクラスが生成された時に処理したい内容はここに
C_MainGameScene::C_MainGameScene()
{
	M_Game.MS_Pos = { 0,0 };
}

// このクラスが削除された時に処理したい内容はここに
C_MainGameScene::~C_MainGameScene()
{
	// 自動で領域解放処理を行う。
	Release();
}

// 初期化したい内容はここに
void C_MainGameScene::Init()
{
	// メインキャラクターの実体(インスタンス)生成→初期化
	// 実体がまだ作成されていない(中身が空のnullptr)場合のみ生成する
	if (!CM_MainCharacter)
	{
		CM_MainCharacter = new C_MainCharacter_MainGame();
		CM_MainCharacter->Init();
	}

	// 敵１の実体(インスタンス)生成→初期化
	if (!CM_Enemy1)
	{
		CM_Enemy1 = new C_Enemy1_MainGame();
		CM_Enemy1->Init();
	}
}

// 更新内容はここに(描画に使うMatrix(行列)の作成や画像の指定もここ)
void C_MainGameScene::Update()
{
	// メインキャラクターの更新処理
	CM_MainCharacter->Update();

	// 敵１の更新処理
	CM_Enemy1->Update();
}

// 描画処理はここに
void C_MainGameScene::Draw()
{
	// メインキャラクターの描画処理
	CM_MainCharacter->Draw();

	// 敵１の描画処理
	CM_Enemy1->Draw();
}

// デバッグ画面に表示させたいものはここに
void C_MainGameScene::ImGuiUpdate()
{
	// メインキャラクターのデバッグ表示内容
	CM_MainCharacter->ImGuiUpdate();

	// 敵１のデバッグ表示内容
	CM_Enemy1->ImGuiUpdate();
}

// このクラスの実体が削除された時に行う領域解放処理。
void C_MainGameScene::Release()
{
	// 各クラスの実体がまだ残っていればここで削除する。
	// メインキャラクター
	if (CM_MainCharacter)
	{
		// 実体の削除→中身を空(nullptr)にする。
		// 中身を空にすれば次実体が作成されない限り削除処理されなくなる。
		delete CM_MainCharacter;
		CM_MainCharacter = nullptr;
	}
	// 敵１
	if (CM_Enemy1)
	{
		// 実体の削除→中身を空(nullptr)にする。
		// 中身を空にすれば次実体が作成されない限り削除処理されなくなる。
		delete CM_Enemy1;
		CM_Enemy1 = nullptr;
	}
}