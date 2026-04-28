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
	for (int i = 0; i < ME_Entity_KindNumber; i++) { CM_Entity.push_back({}); }
	// メインキャラクター
		CM_Entity[0].push_back(std::make_unique<C_MainCharacter_MainGame>());
	// 弾
		//CM_Entity.push_back(std::make_unique<C_Bullet_MainGame>());
	// 初期化
	// CM_Entity配列を最前列から最後尾まで一気に処理してくれる。
		for (auto& Row : CM_Entity) { for (auto& Column : Row) { Column->Init(); } }
}

// 更新内容はここに(描画に使うMatrix(行列)の作成や画像の指定もここ)
void C_MainGameScene::Update()
{
	// 毎秒60回値が出力され、1%の確率で敵を出現させる。
	if (C_RandomNumericalValue::GetInstance().RandomNumericalValue(100) == 100)
	{
		// 配列の列を追加し、敵１クラスの実体を生成→初期化する。
		CM_Entity[1].push_back(std::make_unique<C_Enemy1_MainGame>());
		CM_Entity[1].back()->Init();
	}

	// 誰か弾を放ったか確認する。
	for (auto& Row : CM_Entity)
	{
		for (auto& Column : Row)
		// 一人一人弾を放ったか確認する。
		if (Column->ShootBullet() == true)
		{ 
			// 弾が放たれる度にその数を記録していく。
			M_ShootBulletNumber++;
		}
	}

	// ループ処理はCM_Entityの要素の数だけ行うように指示している為、弾を生成するなら一回CM_Entity関連のループを抜ける必要がある。
	for (int i = 0; i < M_ShootBulletNumber; i++)
	{
		// 弾の実体を作成し、初期化する。
		CM_Entity[2].push_back(std::make_unique<C_Bullet_MainGame>());
		CM_Entity[2].back()->Init();
	}
	// 必要数弾を生成したら放たれた弾の数を０に戻す。
	M_ShootBulletNumber = 0;

	// 更新処理
	for (auto& Row : CM_Entity) { for (auto& Column : Row) { Column->Update(); } }
}

// 描画処理はここに
void C_MainGameScene::Draw()
{
	// 描画処理
	for (auto& Row : CM_Entity) { for (auto& Column : Row) { Column->Draw(); } }
}

// デバッグ画面に表示させたいものはここに
void C_MainGameScene::ImGuiUpdate()
{
	ImGui::Text(u8"敵の数　：%d", CM_Entity.size() - 1);
	// デバッグ表示
	for (auto& Row : CM_Entity) { for (auto& Column : Row) { Column->ImGuiUpdate(); } }

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