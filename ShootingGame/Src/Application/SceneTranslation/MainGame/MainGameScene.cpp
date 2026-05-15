#include "MainGameScene.h"
#include "../../Tool/RandomNumericalValue.h"

#include "../../Scene.h"

// シーン遷移を行うクラス
#include "../SceneManager&State/SceneManager.h"

// キャラクターのクラスを取り込む
// メインキャラクター
#include "Entity_MainGame/MainCharacter/MainCharacter.h"
// メインキャラクターの弾
#include "Entity_MainGame/Bullet/MainCharacter/BulletAbove_MainCharacter.h"
// 敵１
#include "Entity_MainGame/Enemy/Enemy1/Enemy1.h"
// 敵１の弾
#include "Entity_MainGame/Bullet/Enemy1/Bullet_Enemy1.h"
#include "Entity_MainGame/Enemy/Boss/Boss.h"

// 当たり判定をするクラス
#include "Entity_MainGame/HitJudgment/HitJudgment.h"

// このクラスが生成された時に処理したい内容はここに
C_MainGameScene::C_MainGameScene()
{
	M_Back.MS_Texture.Load("Texture/背景２.png");
	M_UIUnder1.MS_Texture.Load("Texture/UIUnder1.png");
	M_UIUnder2.MS_Texture.Load("Texture/UIUnder2.png");
	for (int i = 0; i < M_MainCharaMAXHP; i++) { M_UIMainCharaHP[i].MS_Texture.Load("Texture/UIHP1.png"); }
	for (int i = 0; i < M_EnemyMAXNum; i++) { M_UIEnemyNum[i].MS_Texture.Load("Texture/UIHP1.png"); }

	M_Game.MS_Position = { 0,0 };
	M_UIUnder1.MS_Position = { 0, -360 + 64 };
	M_UIUnder2.MS_Position = { 0, -360 + 64 };

	M_UIMainCharaHP[0].MS_Position = { -501, -357 + 64 };
	for (int i = 1; i < M_MainCharaMAXHP; i++)
	{
		M_UIMainCharaHP[i].MS_Position = { M_UIMainCharaHP[0].MS_Position.x + (float)(9 * i), -357 + 64};
	}

	M_UIEnemyNum[0].MS_Position = { 271, -357 + 64 };
	for (int i = 1; i < M_EnemyMAXNum; i++)
	{
		M_UIEnemyNum[i].MS_Position = { M_UIEnemyNum[0].MS_Position.x + (float)(9 * i), -357 + 64 };
	}

	// シーン遷移させないようフラグを立てる。
	MF_Stop_ContinuitySceneTransition = true;

	SCENE.Setter_BossDelete(false);
}

// このクラスが削除された時に処理したい内容はここに
C_MainGameScene::~C_MainGameScene()
{
	Release();
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
	SCENE.Setter_EnemyAliveNum(M_Enemy1_RemainingNumber);

	if (GetAsyncKeyState('H') & 0x8000) { M_Enemy1_RemainingNumber = 1; }

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

	if ((CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1].size() != 0) && (M_Enemy1_RemainingNumber == 1))
	{
		CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1][0]->Setter_LastEnemy(true);
	}

	if ((CM_Entity[C_MainGameScene::E_EntityNumber::ME_MainCharacter].size() != 0) && (CM_Entity[C_MainGameScene::E_EntityNumber::ME_Boss].size() != 0))
	{
		if ((CM_Entity[C_MainGameScene::E_EntityNumber::ME_MainCharacter][0]->Getter_MyPosition().y - 15) > CM_Entity[C_MainGameScene::E_EntityNumber::ME_Boss][0]->Getter_MyPosition().y)
		{
			CM_Entity[C_MainGameScene::E_EntityNumber::ME_Boss][0]->MoveSpeedAlenge(3);
		}
		else if ((CM_Entity[C_MainGameScene::E_EntityNumber::ME_MainCharacter][0]->Getter_MyPosition().y + 15) < CM_Entity[C_MainGameScene::E_EntityNumber::ME_Boss][0]->Getter_MyPosition().y)
		{
			CM_Entity[C_MainGameScene::E_EntityNumber::ME_Boss][0]->MoveSpeedAlenge(-3);
		}
		else
		{
			CM_Entity[C_MainGameScene::E_EntityNumber::ME_Boss][0]->MoveSpeedAlenge(0);
		}
	}

	if (SCENE.Getter_BossDelete()) { M_ChangeResultTime--; }

	if (SCENE.Getter_MainCharaDelete() || SCENE.Getter_BossDelete())
	{ 
		M_UIAlpha -= M_UIDelta;
		if (M_UIAlpha < 0) { M_UIAlpha = 0; }
		M_FinishSlide = -15; 
	}
	else
	{
		M_UIAlpha += M_UIDelta;
		if (M_UIAlpha > 1) { M_UIAlpha = 1; }
	}

	if (SCENE.Getter_MainCharaDelete())
	{
		M_ChangeGameOverTime--;
	}

	//M_UIUnder.MS_Position.x += M_FinishSlide;
	//if (CM_Entity[C_MainGameScene::E_EntityNumber::ME_MainCharacter].size() != 0)
	//{
	//	for (int i = 0; i < CM_Entity[C_MainGameScene::E_EntityNumber::ME_MainCharacter][0]->Getter_HP(); i++)
	//	{
	//		M_UIMainCharaHP[i].MS_Position.x += M_FinishSlide;
	//	}
	//}
	//for (int i = 0; i < M_Enemy1_RemainingNumber; i++)
	//{
	//	M_UIEnemyNum[i].MS_Position.x += M_FinishSlide;
	//}

	// 敵１の削除許可が出たら敵１の残りの数を減らす。
	Update_Enemy1_RemainingNumber_Subtract();
	M_Back.MS_Matrix = Math::Matrix::CreateTranslation(0, 0, 0);
	M_UIUnder1.MS_Matrix = Math::Matrix::CreateTranslation(M_UIUnder1.MS_Position.x, M_UIUnder1.MS_Position.y, 0);
	M_UIUnder2.MS_Matrix = Math::Matrix::CreateTranslation(M_UIUnder2.MS_Position.x, M_UIUnder2.MS_Position.y, 0);

	if (CM_Entity[C_MainGameScene::E_EntityNumber::ME_MainCharacter].size() != 0)
	{
		for (int i = 0; i < CM_Entity[C_MainGameScene::E_EntityNumber::ME_MainCharacter][0]->Getter_HP(); i++)
		{
			M_UIMainCharaHP[i].MS_Matrix = Math::Matrix::CreateTranslation(M_UIMainCharaHP[i].MS_Position.x, M_UIMainCharaHP[i].MS_Position.y, 0);
		}
	}
	for (int i = 0; i < M_Enemy1_RemainingNumber; i++)
	{
		M_UIEnemyNum[i].MS_Matrix = Math::Matrix::CreateTranslation(M_UIEnemyNum[i].MS_Position.x, M_UIEnemyNum[i].MS_Position.y, 0);
	}

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

	M_SpownEnemy1Count -= 1;
	if (M_SpownEnemy1Count < 0) { M_SpownEnemy1Count = (2.5f * 60); }

}

// 描画処理はここに
void C_MainGameScene::DrawSprite()
{
	//SHADER.m_spriteShader.SetMatrix(M_Back.MS_Matrix);
	//SHADER.m_spriteShader.DrawColorTex(&M_Back.MS_Texture, Math::Rectangle{ 0, 0, 1280, 720 }, Math::Color{ 1, 1, 1, 1 });

	// 各キャラの描画処理
	for (auto& Row : CM_Entity) { for (auto& Column : Row) { Column->Draw(); } }

	if (!M_SpownBoss)
	{
		SHADER.m_spriteShader.SetMatrix(M_UIUnder1.MS_Matrix);
		SHADER.m_spriteShader.DrawTex(&M_UIUnder1.MS_Texture, Math::Rectangle{ 0, 0, 1280, 128 }, M_UIAlpha);
	}

	if (M_SpownBoss)
	{
		SHADER.m_spriteShader.SetMatrix(M_UIUnder2.MS_Matrix);
		SHADER.m_spriteShader.DrawTex(&M_UIUnder2.MS_Texture, Math::Rectangle{ 0, 0, 1280, 128 }, M_UIAlpha);
	}

	if (CM_Entity[C_MainGameScene::E_EntityNumber::ME_MainCharacter].size() != 0)
	{
		for (int i = 0; i < CM_Entity[C_MainGameScene::E_EntityNumber::ME_MainCharacter][0]->Getter_HP(); i++)
		{
			SHADER.m_spriteShader.SetMatrix(M_UIMainCharaHP[i].MS_Matrix);
			SHADER.m_spriteShader.DrawColorTex(&M_UIMainCharaHP[i].MS_Texture, Math::Rectangle{ 0, 0, 6, 58 }, Math::Color{ 1, 1, 1, M_UIAlpha });
		}
	}

	if (!M_SpownBoss)
	{
		for (int i = 0; i < M_Enemy1_RemainingNumber; i++)
		{
			SHADER.m_spriteShader.SetMatrix(M_UIEnemyNum[i].MS_Matrix);
			SHADER.m_spriteShader.DrawColorTex(&M_UIEnemyNum[i].MS_Texture, Math::Rectangle{ 0, 0, 6, 58 }, Math::Color{ 1, 1, 1, M_UIAlpha });
		}
	}
	if (M_SpownBoss)
	{
		if (CM_Entity[C_MainGameScene::E_EntityNumber::ME_Boss].size() != 0)
		{
			for (int i = 0; i < CM_Entity[C_MainGameScene::E_EntityNumber::ME_Boss][0]->Getter_HP(); i++)
			{
				SHADER.m_spriteShader.SetMatrix(M_UIEnemyNum[i].MS_Matrix);
				SHADER.m_spriteShader.DrawColorTex(&M_UIEnemyNum[i].MS_Texture, Math::Rectangle{ 0, 0, 6, 58 }, Math::Color{ 1, 1, 1, M_UIAlpha });
			}
		}
	}
}

// デバッグ画面に表示させたいものはここに
void C_MainGameScene::ImGuiUpdate()
{
	//ImGui::SliderFloat(u8"太陽の数", &M_UIEnemyNum[0].MS_Position.x, -640, 640);
	//ImGui::SliderFloat(u8"太陽の数", &M_UIMainCharaHP[0].MS_Position.y, -640, 640);
	// エンティティの数や種類を表示する関数。
	ImGui_EntityNumber();

	// 各キャラのデバッグ表示
	for (auto& Row : CM_Entity) { for (auto& Column : Row) { Column->ImGuiUpdate(); } }

}

// このクラスの実体が削除された時に行う領域解放処理。
void C_MainGameScene::Release()
{

	M_Back.MS_Texture.Release();
	M_UIUnder1.MS_Texture.Release();
	M_UIUnder2.MS_Texture.Release();
	for (int i = 0; i < M_MainCharaMAXHP; i++) { M_UIMainCharaHP[i].MS_Texture.Release(); }
	for (int i = 0; i < M_EnemyMAXNum; i++) { M_UIEnemyNum[i].MS_Texture.Release(); }
}

// 当たり判定の処理。
void C_MainGameScene::Update_Entity_HitJudgment()
{
	if (!SCENE.Getter_MainCharaAlive() || SCENE.Getter_BossDelete()) return;

	// 接触しているかどうか調べる
	// メインキャラと敵１
	Update_Entity_HitJudgment_MainCharacter＆Enemy1();
	Update_Entity_HitJudgment_MainCharacter＆Boss();

	// メインキャラと敵１の弾
	Update_Entity_HitJudgment_MainCharacter＆Bullet_Enemy1();
	
	// 敵１とメインキャラの弾
	Update_Entity_HitJudgment_Enemy1＆Bullet_MainCharacter();
	Update_Entity_HitJudgment_Boss＆Bullet_MainCharacter();

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

				Math::Vector2 KnockDir = Column2->Getter_MyPosition() - Column1->Getter_MyPosition();
				float Length = KnockDir.Length();

				if (Length > 0.0f)
				{
					KnockDir.Normalize();
					Column2->ApplyKnockback(KnockDir, 25.0f);
				}

				KnockDir = Column1->Getter_MyPosition() - Column2->Getter_MyPosition();
				Length = KnockDir.Length();

				if (Length > 0.0f)
				{
					KnockDir.Normalize();
					Column1->ApplyKnockback(KnockDir, 25.0f);
				}
				break;

			}
		}
	}
}

void C_MainGameScene::Update_Entity_HitJudgment_MainCharacter＆Boss()
{
	// メインキャラと敵１の行から列を一つずつ取り出し、全通り見ていく。
	// 座標と半径を渡し、接触しているか確認する。
	// 接触している(戻り値がtrue)場合はお互いの生存フラグを折る(やられた判定にさせる)。
	for (auto& Column1 : CM_Entity[C_MainGameScene::E_EntityNumber::ME_MainCharacter])
	{
		for (auto& Column2 : CM_Entity[C_MainGameScene::E_EntityNumber::ME_Boss])
		{
			// もし既にやられた判定だったら当たり判定の確認をさせない。
			if (!Column1->Getter_AliveFlag() || !Column2->Getter_AliveFlag()) continue;
			if (C_HitJudgment::Instance().HitJudgment(Column1->Getter_MyPosition(), Column1->Getter_Radius(), Column2->Getter_MyPosition(), Column2->Getter_Radius()) == true)
			{
				// 攻撃力分体力を削る
				Column1->Damage(Column2->Getter_Power());
				Column2->Damage(Column1->Getter_Power());

				Math::Vector2 KnockDir = Column2->Getter_MyPosition() - Column1->Getter_MyPosition();
				float Length = KnockDir.Length();

				if (Length > 0.0f)
				{
					KnockDir.Normalize();
					Column2->ApplyKnockback(KnockDir, 2.0f);
				}

				KnockDir = Column1->Getter_MyPosition() - Column2->Getter_MyPosition();
				Length = KnockDir.Length();

				if (Length > 0.0f)
				{
					KnockDir.Normalize();
					Column1->ApplyKnockback(KnockDir, 30.0f);
				}
				break;

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
				Math::Vector2 KnockDir = Column2->Getter_MyPosition() - Column1->Getter_MyPosition();
				float Length = KnockDir.Length();

				if (Length > 0.0f)
				{
					KnockDir.Normalize();
					Column2->ApplyKnockbackBullet(KnockDir, 20.0f);
				}

				KnockDir = Column1->Getter_MyPosition() - Column2->Getter_MyPosition();
				Length = KnockDir.Length();

				if (Length > 0.0f)
				{
					KnockDir.Normalize();
					Column1->ApplyKnockbackBullet(KnockDir, 20.0f);
				}
				break;

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
	for (auto& Column1 : CM_Entity[C_MainGameScene::E_EntityNumber::ME_Bullet_MainCharacter])
	{
		for (auto& Column2 : CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1])
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
				Math::Vector2 KnockDir = Column2->Getter_MyPosition() - Column1->Getter_MyPosition();
				float Length = KnockDir.Length();

				if (Length > 0.0f)
				{
					KnockDir.Normalize();
					Column2->ApplyKnockbackBullet(KnockDir, 20.0f);
				}

				KnockDir = Column1->Getter_MyPosition() - Column2->Getter_MyPosition();
				Length = KnockDir.Length();

				if (Length > 0.0f)
				{
					KnockDir.Normalize();
					Column1->ApplyKnockbackBullet(KnockDir, 20.0f);
				}

				break;
			}
		}
	}
}

void C_MainGameScene::Update_Entity_HitJudgment_Boss＆Bullet_MainCharacter()
{
	// 敵１と弾の行から列を一つずつ取り出し、全通り見ていく。
	// 座標と半径を渡し、接触しているか確認する。
	// 接触している(戻り値がtrue)場合はお互いの生存フラグを折る(やられた判定にさせる)。
	for (auto& Column1 : CM_Entity[C_MainGameScene::E_EntityNumber::ME_Bullet_MainCharacter])
	{
		for (auto& Column2 : CM_Entity[C_MainGameScene::E_EntityNumber::ME_Boss])
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
				Math::Vector2 KnockDir = Column2->Getter_MyPosition() - Column1->Getter_MyPosition();
				float Length = KnockDir.Length();

				if (Length > 0.0f)
				{
					KnockDir.Normalize();
					Column2->ApplyKnockbackBullet(KnockDir, 5.0f);
				}

				KnockDir = Column1->Getter_MyPosition() - Column2->Getter_MyPosition();
				Length = KnockDir.Length();

				if (Length > 0.0f)
				{
					KnockDir.Normalize();
					Column1->ApplyKnockbackBullet(KnockDir, 20.0f);
				}

				break;
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
				
				// ノックバックの方向を知る為旋回しているか教える
				Math::Vector2 KnockDir = Column2->Getter_MyPosition() - Column1->Getter_MyPosition();
				float Length = KnockDir.Length();

				if (Length > 0.0f)
				{
					KnockDir.Normalize();
					Column2->ApplyKnockbackBullet(KnockDir, 40.0f);
				}

				KnockDir = Column1->Getter_MyPosition() - Column2->Getter_MyPosition();
				Length = KnockDir.Length();

				if (Length > 0.0f)
				{
					KnockDir.Normalize();
					Column1->ApplyKnockbackBullet(KnockDir, 40.0f);
				}
				// 攻撃力分体力を削る
				Column1->Damage(Column2->Getter_Power());
				Column2->Damage(Column1->Getter_Power());

				break;
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
			if (M_Enemy1_RemainingNumber > 0)
			{
				M_Enemy1_RemainingNumber--;
				SCENE.Setter_EnemyAliveNum(M_Enemy1_RemainingNumber);
			}
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

	if ((CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1].size() <= 0) && (M_Enemy1_RemainingNumber <= 0) && !M_SpownBoss)
	{
		CM_Entity[C_MainGameScene::E_EntityNumber::ME_Boss].push_back(std::make_unique<C_Boss_MainGame>());
		CM_Entity[C_MainGameScene::E_EntityNumber::ME_Boss].back()->Init();
		M_SpownBoss = true;
	}
}	

// 敵１のインスタンスを生成する関数。
void C_MainGameScene::PreUpdate_CreateEnemy1()
{
	if (!SCENE.Getter_MainCharaAlive()) return;
	// 条件１：ランダム値が出現可能な数値の場合
	// 条件２：敵の数が上限に達していない(.size()だと添え字基準で現在出現している数が1つ少なくカウントされる)
	// 条件３：残りの敵１の数を上回る数を出現させていない
	if ((C_RandomNumericalValue::Instance().RandomNumericalValue(30) == 1) && ((CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1].size() + 1) <= M_Enemy1_MaxNumber) && ((CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1].size() + 1) <= M_Enemy1_RemainingNumber))
	{
		if (M_SpownEnemy1Count <= (1.8f * 60))
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
			M_SpownEnemy1Count = (2.8f * 60);
		}
	}
	if ((M_SpownEnemy1Count == 0) && ((CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1].size() + 1) <= M_Enemy1_MaxNumber) && ((CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1].size() + 1) <= M_Enemy1_RemainingNumber))
	{
		// 配列の列を追加し、敵１クラスの実体を生成→初期化する。
		CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1].push_back(std::make_unique<C_Enemy1_MainGame>());
		CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1].back()->Init();

		M_SpownEnemy1Count = (2.8f * 60);
	}
	if ((CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1].size() + 1) > M_Enemy1_MaxNumber)
	{
		M_SpownEnemy1Count = (5 * 60);
	}
}

// 弾のインスタンスを生成する関数。
void C_MainGameScene::PreUpdate_CreateBullet()
{
	if (!SCENE.Getter_MainCharaAlive()) return;
	// メインキャラの弾発射処理
	// Updateループ処理はCM_Entityの要素の数だけ行うように指示している為、弾を生成するなら一回CM_Entity関連のループを抜ける必要がある。
	for (auto& Column : CM_Entity[C_MainGameScene::E_EntityNumber::ME_MainCharacter])
	{
		if (Column->ShootBullet() == C_EntityBase_MainGame::E_BulletKind::ME_Above)
		{
			// 弾の実体を作成し、初期化する。
			CM_Entity[C_MainGameScene::E_EntityNumber::ME_Bullet_MainCharacter].push_back(std::make_unique<C_BulletAbove_MainCharacter>());
			CM_Entity[C_MainGameScene::E_EntityNumber::ME_Bullet_MainCharacter].back()->Init((Column->Getter_MyPosition() + BulletUP), Column->Getter_TurningFlag());

		}
		//if (Column->ShootBullet() == C_EntityBase_MainGame::E_BulletKind::ME_Back)
		//{
		//	// 弾の実体を作成し、初期化する。
		//	CM_Entity[C_MainGameScene::E_EntityNumber::ME_Bullet_MainCharacter].push_back(std::make_unique<C_BulletAbove_MainCharacter>());
		//	CM_Entity[C_MainGameScene::E_EntityNumber::ME_Bullet_MainCharacter].back()->Init(Column->Getter_MyPosition(), true);
		//}
	}
	// 必要数弾を生成したら放たれた弾の数を０に戻す。
	//M_ShootBulletNumber = 0;

	// 敵１の弾発射処理
	for (auto& Column : CM_Entity[C_MainGameScene::E_EntityNumber::ME_Enemy1])
	{
		if (Column->ShootBullet() == C_EntityBase_MainGame::E_BulletKind::ME_Above)
		{
			if (!Column->Getter_TurningFlag() && Column->Getter_MyPosition().x < (CM_Entity[C_MainGameScene::E_EntityNumber::ME_MainCharacter][0]->Getter_MyPosition().x + CM_Entity[C_MainGameScene::E_EntityNumber::ME_MainCharacter][0]->Getter_Radius().x)) { continue; }
			// 弾の実体を作成し、初期化する。
			CM_Entity[C_MainGameScene::E_EntityNumber::ME_Bullet_Enemy1].push_back(std::make_unique<C_Bullet_Enemy1>());
			CM_Entity[C_MainGameScene::E_EntityNumber::ME_Bullet_Enemy1].back()->Init((Column->Getter_MyPosition() + BulletUP), Column->Getter_TurningFlag());

		}
	}

	for (auto& Column : CM_Entity[C_MainGameScene::E_EntityNumber::ME_Boss])
	{
		if (Column->ShootBullet() == C_EntityBase_MainGame::E_BulletKind::ME_Above)
		{
			if (!Column->Getter_TurningFlag() && Column->Getter_MyPosition().x < (CM_Entity[C_MainGameScene::E_EntityNumber::ME_MainCharacter][0]->Getter_MyPosition().x + CM_Entity[C_MainGameScene::E_EntityNumber::ME_MainCharacter][0]->Getter_Radius().x)) { continue; }

			Math::Vector2 One;

			if (!CM_Entity[C_MainGameScene::E_EntityNumber::ME_Boss][0]->Getter_TurningFlag()) { One = { Column->Getter_MyPosition().x - 50 , Column->Getter_MyPosition().y }; }
			if (CM_Entity[C_MainGameScene::E_EntityNumber::ME_Boss][0]->Getter_TurningFlag()) { One = { Column->Getter_MyPosition().x + 50 , Column->Getter_MyPosition().y }; }
			Math::Vector2 Tow = { Column->Getter_MyPosition().x , Column->Getter_MyPosition().y + 50 };
			Math::Vector2 Three = { Column->Getter_MyPosition().x , Column->Getter_MyPosition().y - 50 };

			// 弾の実体を作成し、初期化する。
			CM_Entity[C_MainGameScene::E_EntityNumber::ME_Bullet_Enemy1].push_back(std::make_unique<C_Bullet_Enemy1>());
			CM_Entity[C_MainGameScene::E_EntityNumber::ME_Bullet_Enemy1].back()->Init((One + BulletUP), Column->Getter_TurningFlag());
			CM_Entity[C_MainGameScene::E_EntityNumber::ME_Bullet_Enemy1].push_back(std::make_unique<C_Bullet_Enemy1>());
			CM_Entity[C_MainGameScene::E_EntityNumber::ME_Bullet_Enemy1].back()->Init((Tow + BulletUP), Column->Getter_TurningFlag());
			CM_Entity[C_MainGameScene::E_EntityNumber::ME_Bullet_Enemy1].push_back(std::make_unique<C_Bullet_Enemy1>());
			CM_Entity[C_MainGameScene::E_EntityNumber::ME_Bullet_Enemy1].back()->Init((Three + BulletUP), Column->Getter_TurningFlag());

		}
	}
}

// リザルトに移る処理。
void C_MainGameScene::PostUpdate_ChangeResultScene()
{
	// リザルトシーンに移りたいとSceneManager伝える。
	// 残りの敵１がゼロになったらリザルトに移る。
	if (M_ChangeResultTime == 0) { C_SceneManager::Instance().SetterNextScene(C_SceneManager::E_SceneType::ME_Result); }
	
}

// ゲームオーバーに移る処理。
void C_MainGameScene::PostUpdate_ChangeGameOverScene()
{
	// メインキャラに削除許可が出たらゲームオーバーシーンに移りたいとSceneManager伝える。
	if (M_ChangeGameOverTime <= 0) { C_SceneManager::Instance().SetterNextScene(C_SceneManager::E_SceneType::ME_GameOver); }
	
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