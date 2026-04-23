#pragma once

// 基底クラス
#include "../Base/EntityBase.h"

class C_Bullet_MainGame : public C_EntityBase_MainGame
{
public:

	// コンストラクタとデストラクタ
	C_Bullet_MainGame();
	~C_Bullet_MainGame()	override;

	// 初期化内容
	void Init()						override;
	// 更新内容
	void Update()				override;
	// 描画処理
	void Draw()					override;
	// デバッグ画面に表示するもの
	void ImGuiUpdate()		override;


private:

	// 領域解放処理はこの実体が削除された時にデストラクタで自動で呼び出されるためprivateに置く。
	void Release();

	// 構造体変数
	S_EntityCharacter	M_Bullet;

};