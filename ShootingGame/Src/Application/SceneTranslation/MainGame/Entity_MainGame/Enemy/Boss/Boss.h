#pragma once

// 基底クラスを取り込む
#include "../../Base/EntityBase.h"

// 動作処理を行うクラス
class C_Boss_Move;


class C_Boss_MainGame :public C_EntityBase_MainGame
{
public:

	// コンストラクタとデストラクタ
	C_Boss_MainGame();
	~C_Boss_MainGame()					override;

	// 初期化内容
		void Init(Math::Vector2 A_Position, bool AF_Turning)	override;
	// 操作の更新
		void Action()									override;
	// 更新内容
		void Update()								override;
	// 描画処理
		void Draw()									override;
	// デバッグ画面に表示するもの
		void ImGuiUpdate()						override;

	// 弾を撃つかどうか判断する
		int ShootBullet()							override;

	// ゲッター
	// 旋回フラグ
		bool Getter_TurningFlag();


private:

	// 領域解放処理はこの実体が削除された時にデストラクタで自動で呼び出されるためprivateに置く。
	void Release();

	std::shared_ptr<C_Boss_Move> CMP_Control = nullptr;

	float M_Anime = 0;

};