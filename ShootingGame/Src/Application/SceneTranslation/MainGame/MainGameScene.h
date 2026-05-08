#pragma once

// シーンの基礎となるクラス(基底クラス)を取り込む
#include "../SceneManager&State/State.h"
#include "vector"
// 自動で解放処理をしてくれるスマートポインタを使うのに必要。
#include "memory"

// キャラクターのクラスを前方宣言(どんなクラスがあるのか教える)
// ヘッダーファイルには基本的にヘッダーは取り込まない。
// Entityクラス(キャラの親クラス)
class C_EntityBase_MainGame;

class C_MainGameScene :public C_State
{
public:

	// コンストラクタ
	C_MainGameScene();
	// デストラクタ
	~C_MainGameScene() override;

	// 初期化用
	void Init()						override;
	// 更新前に行う更新
	void PreUpdate()			override;
	// 更新処理
	void Update()				override;
	// 更新後に行う更新
	void PostUpdate()			override;
	// 2D描画
	void DrawSprite()			override;
	// デバッグ表示
	void ImGuiUpdate()		override;

private:

	// 領域解放処理はこの実体が削除された時にデストラクタで自動で呼び出されるためprivateに置く。
	void Release();

	// エンティティの数を表示する関数。
	void ImGui_EntityNumber();

	// 全てのエンティティの数や種類を表示する関数。
	void ImGui_AllEntityNumber();

	// 当たり判定の処理。
	void Update_Entity_HitJudgment();

	// メインキャラと敵１の接触時の処理
	void Update_Entity_HitJudgment_MainCharacter＆Enemy1();

	// メインキャラと敵１の弾の接触時の処理
	void Update_Entity_HitJudgment_MainCharacter＆Bullet_Enemy1();

	// 敵１とメインキャラの弾の接触時の処理
	void Update_Entity_HitJudgment_Enemy1＆Bullet_MainCharacter();

	// メインキャラの弾と敵１の弾の接触時の処理
	void Update_Entity_HitJudgment_Bullet_MainCharacter＆Bullet_Enemy1();

	// 敵１がやられた時に敵１の残りの数を減らしていく
	void Update_Enemy1_RemainingNumber_Subtract();

	// 削除許可が出されたエンティティのインスタンスを削除する。
	void PostUpdate_DeleteEntity();

	// エンティティのインスタンスを生成する関数をここにまとめる。
	void PreUpdate_CreateEntity();

	// 敵１のインスタンスを生成する関数。
	void PreUpdate_CreateEnemy1();

	// 弾のインスタンスを生成する関数。
	void PreUpdate_CreateBullet();

	// リザルトに移る処理。
	void PostUpdate_ChangeResultScene();

	// ゲームオーバーに移る処理。
	void PostUpdate_ChangeGameOverScene();

	// 「Game」の文字用の構造体変数
	S_Entity M_Game;

	// EntityBase(キャラ達の親クラス)型の動的二次元配列
	std::vector<std::vector<std::unique_ptr<C_EntityBase_MainGame>>> CM_Entity;

	// 放たれた弾の数の一時保存場所。
	int M_ShootBulletNumber = 0;

	// 敵１の数の上限
	const int M_Enemy1_MaxNumber = 10;

	// 残りの敵１の数
	int M_Enemy1_RemainingNumber = 30;

	// それぞれのキャラの格納場所(行)
	enum E_EntityNumber
	{
		ME_MainCharacter,
		ME_Enemy1,
		ME_Bullet_MainCharacter,
		ME_Bullet_Enemy1,
		ME_Entity_KindNumber,
	};

};