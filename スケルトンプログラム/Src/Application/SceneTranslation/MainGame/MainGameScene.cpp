#include "MainGameScene.h"
#include "../../Tool/RandomNumericalValue.h"

// キャラクターのクラスを取り込む
// メインキャラクター
#include "Entity_MainGame/MainCharacter/MainCharacter.h"
// 弾
#include "Entity_MainGame/Bullet/Bullet.h"
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
	// アップキャストを使って各キャラの実体(インスタンス)を生成
	// アップキャストという技術を使えば子クラスをまとめて親クラスで管理できる。
	// std::make_uniqueだとCM_Entityから消えた時自動でメモリが解放される。
	// メインキャラクター
		CM_Entity.push_back(std::make_unique<C_MainCharacter_MainGame>());
	// 弾
		CM_Entity.push_back(std::make_unique<C_Bullet_MainGame>());
	// 初期化
	// CM_Entity配列を最前列から最後尾まで一気に処理してくれる。
	for (auto& p : CM_Entity) { p->Init(); }
}

// 更新内容はここに(描画に使うMatrix(行列)の作成や画像の指定もここ)
void C_MainGameScene::Update()
{
	// 毎秒60回値が出力され、1%の確率で敵を出現させる。
	if (C_RandomNumericalValue::GetInstance().RandomNumericalValue(100) == 100)
	{
		// 配列の列を追加し、敵１クラスの実体を生成→初期化する。
		CM_Entity.push_back(std::make_unique<C_Enemy1_MainGame>());
		CM_Entity.back()->Init();
	}

	// 更新処理
	for (auto& p : CM_Entity) { p->Update(); }
}

// 描画処理はここに
void C_MainGameScene::Draw()
{
	// 描画処理
	for (auto& p : CM_Entity) { p->Draw(); }
}

// デバッグ画面に表示させたいものはここに
void C_MainGameScene::ImGuiUpdate()
{
	ImGui::Text(u8"敵の数　：%d", CM_Entity.size() - 1);
	// デバッグ表示
	for (auto& p : CM_Entity) { p->ImGuiUpdate(); }

}

// このクラスの実体が削除された時に行う領域解放処理。
void C_MainGameScene::Release()
{
	//// 各クラスの実体がまだ残っていればここで削除する。
	//// メインキャラクター
	//if (CM_MainCharacter)
	//{
	//	// 実体の削除→中身を空(nullptr)にする。
	//	// 中身を空にすれば次実体が作成されない限り削除処理されなくなる。
	//	delete CM_MainCharacter;
	//	CM_MainCharacter = nullptr;
	//}
	//// 敵１
	//if (CM_Enemy1)
	//{
	//	// 実体の削除→中身を空(nullptr)にする。
	//	// 中身を空にすれば次実体が作成されない限り削除処理されなくなる。
	//	delete CM_Enemy1;
	//	CM_Enemy1 = nullptr;
	//}
}