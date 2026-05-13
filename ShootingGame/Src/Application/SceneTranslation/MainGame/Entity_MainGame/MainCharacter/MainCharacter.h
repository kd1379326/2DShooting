#pragma once

// 親クラス
#include "../Base/EntityBase.h"

// キー操作の機能
class C_MainCharacter_KeyControl;

class C_MainCharacter_MainGame :public C_EntityBase_MainGame
{
public:

	// コンストラクタとデストラクタ
	C_MainCharacter_MainGame();
	~C_MainCharacter_MainGame()		override;

	// 初期化内容
	void Init(Math::Vector2 A_Position, bool AF_Turning)	override;
	// 操作の更新
	void Action()									override;
	// 更新内容
	void Update()								override;
	// 描画内容
	void Draw()									override;
	// デバッグ画面に表示する内容
	void ImGuiUpdate()						override;

	// 弾を撃つかどうか判断する
	int ShootBullet()							override;

	// ゲッター
	// 現在の座標を返す。
	Math::Vector2 Getter_Position() { return M_Entity.MS_Position; }
	
private:

	// 領域解放処理はこの実体が削除された時にデストラクタで自動で呼び出されるためprivateに置く。
	void Release();

	// 操作機能関連のクラス
	std::shared_ptr<C_MainCharacter_KeyControl> CM_Control;

	// ノックバックする距離
	int M_KnockbackDistance = -30;

	// 現在ノックバックさせたい距離
	int M_NowKnockback = 0;

	// ノックバックの距離を小さくしていく数値
	const float M_Knockback_Subtract = 0.85f;

	// ノックバックさせたい距離の最小値
	const float M_Knockback_Minimum_Left = -1.0f;

	// ノックバックさせたい距離の最小値
	const float M_Knockback_Minimum_Right = 1.0f;

	float M_MainCharaEnd = (3 * 60);

	bool M_NotDeath = false;

};