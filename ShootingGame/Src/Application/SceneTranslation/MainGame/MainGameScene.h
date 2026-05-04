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
// メインキャラクター
class C_MainCharacter_MainGame;
// 敵１
class C_Enemy1_MainGame;

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

	// 誰が弾を撃ったのかチェックする。
	void PostUpdate_Check_WhoShootBullet();

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

	// それぞれのキャラの格納場所(行)
	enum E_EntityNumber
	{
		ME_MainCharacter,
		ME_Enemy1,
		ME_Bullet,
		ME_Entity_KindNumber,
	};

};