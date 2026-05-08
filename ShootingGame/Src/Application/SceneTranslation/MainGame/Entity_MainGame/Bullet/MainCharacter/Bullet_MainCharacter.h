#pragma once

// 基底クラス
#include "../../Base/EntityBase.h"

class C_Bullet_MainCharacter : public C_EntityBase_MainGame
{
public:

	// コンストラクタとデストラクタ
	C_Bullet_MainCharacter();
	~C_Bullet_MainCharacter()					override;

	// 初期化内容
	void Init(Math::Vector2 A_Position)	override;
	// 操作の更新
	void Action()									override;
	// 更新内容
	void Update()								override;
	// 描画処理
	void Draw()									override;
	// デバッグ画面に表示するもの
	void ImGuiUpdate()						override;

	// 弾を撃つかどうか判断する
	bool ShootBullet()							override { return false; }


private:

	// 領域解放処理はこの実体が削除された時にデストラクタで自動で呼び出されるためprivateに置く。
	void Release();


};