#include "MainGameScene.h"
#include "../../Tool/RandomNumericalValue.h"

// シーン遷移を行うクラス
#include "../SceneManager&State/SceneManager.h"

// キャラクターのクラスを取り込む
// メインキャラクター
#include "Entity_MainGame/MainCharacter/MainCharacter.h"
// メインキャラクターの弾
#include "Entity_MainGame/Bullet/MainCharacter/Bullet_MainCharacter.h"
// 敵１
#include "Entity_MainGame/Enemy/Enemy1/Enemy1.h"
// 敵１の弾
#include "Entity_MainGame/Bullet/Enemy1/Bullet_Enemy1.h"

// 当たり判定をするクラス
#include "Entity_MainGame/HitJudgment/HitJudgment.h"

// このクラスが生成された時に処理したい内容はここに
C_MainGameScene::C_MainGameScene()
{
	M_Game.MS_Position = { 0,0 };
	// シーン遷移させないようフラグを立てる。
	MF_Stop_ContinuitySceneTransition = true;
}

// このクラスが削除された時に処理したい内容はここに
C_MainGameScene::~C_MainGameScene()
{
	
}

// 初期化したい内容はここに
void C_MainGameScene::Init()
{
	// アップキャストを使って各キャラの実体(インスタンス)を生成
	// アップキャストという技術を使えば子クラスをまとめて親クラスで管理できる。
	// std::make_uniqueだとCM_Entityから消えた時自動でメモリが解放される。
	// 登場させるキャラの数だけ行を作る。
	// 行によって扱うキャラを変えていく。
	for (int i = 0; i < C_MainGameScene::E_EntityNumber::ME_Entity_KindNumber; i++) { CM_Entity.push_back({}); }
	// メインキャラクター
		CM_Entity[C_MainGameScene::E_EntityNumber::ME_MainCharacter].push_back(std::make_unique<C_MainCharacter_MainGame>());
	// 初期化
	// CM_Entity配列を最前列から最後尾まで一気に処理してくれる。
		for (auto& Row : CM_Entity) { for (auto& Column : Row) { Column->Init(); } }
}

// 更新前に行いたい更新処理はここに書く。
void C_MainGameScene::PreUpdate()
{
	// エンティティのインスタンスを生成する関数。
	PreUpdate_CreateEntity();

}

// 更新内容はここに(描画に使うMatrix(行列)の作成や画像の指定もここ)
void C_MainGameScene::Update()
{
	// 各キャラの操作系の更新処理
	for (auto& Row : CM_Entity) { for (auto& Column : Row) { Column->Action(); } }

	// 当たり判定の確認をここで行う。
	Update_Entity_HitJudgment();

	// 各キャラの更新処理
	for (auto& Row : CM_Entity)
	{ 
		for (auto& Column : Row)
		{ 
			//Column->Knockback(1, -20);
			Column->Update(); 
		} 
	}

	// 敵１の削除許可が出たら敵１の残りの数を減らす。
	Update_Enemy1_RemainingNumber_Subtract();


}

// 更新後に行いたい更新処理はここに書く。
void C_MainGameScene::PostUpdate()
{

	// リザルトに移る処理。
	PostUpdate_ChangeResultScene();

	// ゲームオーバーに移る処理。
	PostUpdate_ChangeGameOverScene();

	// エンティティのインスタンスを削除する関数。
	PostUpdate_DeleteEntity();


}

// 描画処理はここに
void C_MainGameScene::DrawSprite()
{
	// 各キャラの描画処理
	for (auto& Row : CM_Entity) { for (auto& Column : Row) { Column->Draw(); } }
}

// デバッグ画面に表示させたいものはここに
void C_MainGameScene::ImGuiUpdate()
{
	// エンティティの数や種類を表示する関数。
	ImGui_EntityNumber();

	// 各キャラのデバッグ表示
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

// 当たり判定の処理。
void C_MainGameScene::Update_Entity_HitJudgment()
{
	// 接触しているかどうか調べる
	// メインキャラと敵１
	Update_Entity_HitJudgment_MainCharacter＆Enemy1();

	// メインキャラと敵１の弾
	Update_Entity_HitJudgment_MainCharacter＆Bullet_Enemy1();
	
	// 敵１とメインキャラの弾
	Update_Entity_HitJudgment_Enemy1＆Bullet_MainCharacter();

	// メインキャラの弾と敵１の弾
	Update_Entity_HitJudgment_Bullet_MainCharacter＆Bullet_Enemy1();

	

}

// メインキャラと敵１の接触時の処理
void C_MainGameScene::Update_Entity_HitJudgment_MainCharacter＆Enemy1()
{
	// メインキャラと敵１の行から列を一つずつ取り出し、全通り見ていく。
	// 座標と半径を渡し、接触しているか確認する。
	// 接触している(戻り値がtrue)場合はお互いの生存フラグを折る(やられた判定にさせる)。
	for (auto& Column1 : CM_Entity[C_MainGameScene::E_EntityNumber::ME_MainCharacter])
	{
		for (auto& Column2 : CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1])
		{
			// もし既にやられた判定だったら当たり判定の確認をさせない。
			if (!Column1->Getter_AliveFlag() || !Column2->Getter_AliveFlag()) continue;
			if (C_HitJudgment::Instance().HitJudgment(Column1->Getter_MyPosition(), Column1->Getter_Radius(), Column2->Getter_MyPosition(), Column2->Getter_Radius()) == true)
			{
				// 攻撃力分体力を削る
				Column1->Damage(Column2->Getter_Power());
				Column2->Damage(Column1->Getter_Power());

				// ノックバック処理
				Column1->Setter_KnockbackFlag(true);
				Column2->Setter_KnockbackFlag(true);
			}
		}
	}
}

// メインキャラと敵１の弾の接触時の処理
void C_MainGameScene::Update_Entity_HitJudgment_MainCharacter＆Bullet_Enemy1()
{
	// メインキャラと敵１の弾の行から列を一つずつ取り出し、全通り見ていく。
	// 座標と半径を渡し、接触しているか確認する。
	// 接触している(戻り値がtrue)場合はお互いの生存フラグを折る(やられた判定にさせる)。
	for (auto& Column1 : CM_Entity[C_MainGameScene::E_EntityNumber::ME_MainCharacter])
	{
		for (auto& Column2 : CM_Entity[C_MainGameScene::E_EntityNumber::ME_Bullet_Enemy1])
		{
			// もし既にやられた判定だったら当たり判定の確認をさせない。
			if (!Column1->Getter_AliveFlag() || !Column2->Getter_AliveFlag()) continue;
			if (C_HitJudgment::Instance().HitJudgment(Column1->Getter_MyPosition(), Column1->Getter_Radius(), Column2->Getter_MyPosition(), Column2->Getter_Radius()) == true)
			{
				// 攻撃力分体力を削る
				Column1->Damage(Column2->Getter_Power());
				Column2->Damage(Column1->Getter_Power());

				// ノックバック処理
				Column1->Setter_KnockbackFlag(true);
			}
		}
	}
}

// 敵１とメインキャラの弾の接触処理
void C_MainGameScene::Update_Entity_HitJudgment_Enemy1＆Bullet_MainCharacter()
{
	// 敵１と弾の行から列を一つずつ取り出し、全通り見ていく。
	// 座標と半径を渡し、接触しているか確認する。
	// 接触している(戻り値がtrue)場合はお互いの生存フラグを折る(やられた判定にさせる)。
	for (auto& Column1 : CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1])
	{
		for (auto& Column2 : CM_Entity[C_MainGameScene::E_EntityNumber::ME_Bullet_MainCharacter])
		{
			// もし既にやられた判定だったら当たり判定の確認をさせない。
			if (!Column1->Getter_AliveFlag() || !Column2->Getter_AliveFlag()) continue;
			// 当たり判定を行う関数に座標や半径を渡す。
			if (C_HitJudgment::Instance().HitJudgment(Column1->Getter_MyPosition(), Column1->Getter_Radius(), Column2->Getter_MyPosition(), Column2->Getter_Radius()) == true)
			{
				// 攻撃力分体力を削る
				Column1->Damage(Column2->Getter_Power());
				Column2->Damage(Column1->Getter_Power());

				// ノックバック処理
				Column1->Setter_KnockbackFlag(true);

			}
		}
	}
}

// メインキャラの弾と敵１の弾の接触処理
void C_MainGameScene::Update_Entity_HitJudgment_Bullet_MainCharacter＆Bullet_Enemy1()
{
	// メインキャラの弾と敵１の弾の行から列を一つずつ取り出し、全通り見ていく。
	// 座標と半径を渡し、接触しているか確認する。
	// 接触している(戻り値がtrue)場合はお互いの生存フラグを折る(やられた判定にさせる)。
	for (auto& Column1 : CM_Entity[C_MainGameScene::E_EntityNumber::ME_Bullet_MainCharacter])
	{
		for (auto& Column2 : CM_Entity[C_MainGameScene::E_EntityNumber::ME_Bullet_Enemy1])
		{
			// もし既にやられた判定だったら当たり判定の確認をさせない。
			if (!Column1->Getter_AliveFlag() || !Column2->Getter_AliveFlag()) continue;
			// 当たり判定を行う関数に座標や半径を渡す。
			if (C_HitJudgment::Instance().HitJudgment(Column1->Getter_MyPosition(), Column1->Getter_Radius(), Column2->Getter_MyPosition(), Column2->Getter_Radius()) == true)
			{
				// 攻撃力分体力を削る
				Column1->Damage(Column2->Getter_Power());
				Column2->Damage(Column1->Getter_Power());

			}
		}
	}
}

// 敵１がやられた時に敵１の残りの数を減らしていく
void C_MainGameScene::Update_Enemy1_RemainingNumber_Subtract()
{
	// 敵１の行を全て確認する
	for (auto& Column : CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1])
	{
		// 削除許可が出た時に敵１の残りの数を減らしていく。
		if (Column->Getter_DeleteFlag())
		{
			M_Enemy1_RemainingNumber--;
		}
	}
}

// 削除許可が出されたエンティティのインスタンスを削除する。
void C_MainGameScene::PostUpdate_DeleteEntity()
{
	// 削除していい実体を消す処理
	for (auto& Row : CM_Entity)
	{
		// 確認する範囲を始めの列(.begin())と終わりの列(.end())と設定する。
		// ラムダ式で削除していい列を探す(戻り値はbool型)。
		// 削除していい列を除いてその後ろの列達を前にずらしていく。
		// std::remove_if()は最後に前にずらした列を戻り値とする。
		// erase()はその戻り値から最後の列までを削除する。
		Row.erase(std::remove_if(Row.begin(), Row.end(), [](const std::unique_ptr<C_EntityBase_MainGame>& A_Entity) {return A_Entity && A_Entity->Getter_DeleteFlag() == true; }), Row.end());
	}
}

// エンティティのインスタンスを生成する関数をここにまとめる。
void C_MainGameScene::PreUpdate_CreateEntity()
{
	// 敵１のインスタンスを生成。
	PreUpdate_CreateEnemy1();
	// 弾のインスタンスを生成。
	PreUpdate_CreateBullet();
}	

// 敵１のインスタンスを生成する関数。
void C_MainGameScene::PreUpdate_CreateEnemy1()
{
	// 条件１：ランダム値が出現可能な数値の場合
	// 条件２：敵の数が上限に達していない(.size()だと添え字基準で現在出現している数が1つ少なくカウントされる)
	// 条件３：残りの敵１の数を上回る数を出現させていない
	if ((C_RandomNumericalValue::Instance().RandomNumericalValue(50) == 1) && ((CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1].size() + 1) <= M_Enemy1_MaxNumber) && ((CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1].size() + 1) <= M_Enemy1_RemainingNumber))
	{
		// 配列の列を追加し、敵１クラスの実体を生成→初期化する。
		CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1].push_back(std::make_unique<C_Enemy1_MainGame>());
		CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1].back()->Init();

		//for (int i = 0; i < (CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1].size() - 1); i++)
		//{
		//	float Distance    = std::abs(CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1][i]->Getter_MyPosition().y - CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1].back()->Getter_MyPosition().y);
		//	float OutDistance = CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1][i]->Getter_Radius().y     - CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1].back()->Getter_Radius().y;
		//	while (Distance < OutDistance)
		//	{
		//		CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1].back()->Init();
		//		Distance = std::abs(CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1][i]->Getter_MyPosition().y - CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1].back()->Getter_MyPosition().y);
		//		OutDistance = CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1][i]->Getter_Radius().y - CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1].back()->Getter_Radius().y;
		//	}
		//}

	}
}

// 弾のインスタンスを生成する関数。
void C_MainGameScene::PreUpdate_CreateBullet()
{
	// メインキャラの弾発射処理
	// Updateループ処理はCM_Entityの要素の数だけ行うように指示している為、弾を生成するなら一回CM_Entity関連のループを抜ける必要がある。
	for (auto& Column : CM_Entity[C_MainGameScene::E_EntityNumber::ME_MainCharacter])
	{
		if (Column->ShootBullet())
		{
			// 弾の実体を作成し、初期化する。
			CM_Entity[C_MainGameScene::E_EntityNumber::ME_Bullet_MainCharacter].push_back(std::make_unique<C_Bullet_MainCharacter>());
			CM_Entity[C_MainGameScene::E_EntityNumber::ME_Bullet_MainCharacter].back()->Init(Column->Getter_MyPosition());
		}
	}
	// 必要数弾を生成したら放たれた弾の数を０に戻す。
	//M_ShootBulletNumber = 0;

	// 敵１の弾発射処理
	for (auto& Column : CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1])
	{
		if (Column->ShootBullet())
		{
			// 弾の実体を作成し、初期化する。
			CM_Entity[C_MainGameScene::E_EntityNumber::ME_Bullet_Enemy1].push_back(std::make_unique<C_Bullet_Enemy1>());
			CM_Entity[C_MainGameScene::E_EntityNumber::ME_Bullet_Enemy1].back()->Init(Column->Getter_MyPosition());
		}
	}
}

// リザルトに移る処理。
void C_MainGameScene::PostUpdate_ChangeResultScene()
{
	// リザルトシーンに移りたいとSceneManager伝える。
	// 残りの敵１がゼロになったらリザルトに移る。
	if (M_Enemy1_RemainingNumber == 0) { C_SceneManager::Instance().SetterNextScene(C_SceneManager::E_SceneType::ME_Result); }
	if (GetAsyncKeyState('Z') & 0x8000) { C_SceneManager::Instance().SetterNextScene(C_SceneManager::E_SceneType::ME_Result); }
}

// ゲームオーバーに移る処理。
void C_MainGameScene::PostUpdate_ChangeGameOverScene()
{
	// メインキャラに削除許可が出たらゲームオーバーシーンに移りたいとSceneManager伝える。
	if (CM_Entity[C_MainGameScene::E_EntityNumber::ME_MainCharacter][0]->Getter_DeleteFlag()) { C_SceneManager::Instance().SetterNextScene(C_SceneManager::E_SceneType::ME_GameOver); }
	
}

// エンティティの数や種類を表示する関数。
void C_MainGameScene::ImGui_EntityNumber()
{
	// メインキャラの数を表示する。
	ImGui::Text(u8"メインキャラの数　　：%d", CM_Entity[C_MainGameScene::E_EntityNumber::ME_MainCharacter].size());
	// 敵１の数を表示する。
	ImGui::Text(u8"敵の数　　　　　　　：%d", CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1].size());
	// メインキャラクターの弾の数を表示する。
	ImGui::Text(u8"メインキャラの弾の数：%d", CM_Entity[C_MainGameScene::E_EntityNumber::ME_Bullet_MainCharacter].size());
	// 敵１の弾の数を表示する。
	ImGui::Text(u8"敵１の弾の数　　　　：%d", CM_Entity[C_MainGameScene::E_EntityNumber::ME_Bullet_Enemy1].size());
	// エンティティの種類を表示する。
	ImGui::Text(u8"エンティティの種類　：%d", CM_Entity.size());

	// 全てのエンティティの数を表示する関数。
	ImGui_AllEntityNumber();
}

// 全てのエンティティの数を表示する関数。
void C_MainGameScene::ImGui_AllEntityNumber()
{
	// 全エンティティの数を表示する。
	// エンティティの数を持ってもらう変数。
	int AllEntity = 0;
	// それぞれの行の列の数を順番に確認し、変数に伝える。
	for (auto& Row : CM_Entity) { AllEntity += Row.size(); }
	ImGui::Text(u8"エンティティの数　：%d", AllEntity);
}