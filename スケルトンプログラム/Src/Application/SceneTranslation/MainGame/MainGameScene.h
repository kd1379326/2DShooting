#pragma once

// シーンの基礎となるクラス(基底クラス)を取り込む
#include "../SceneManager&State/State.h"

// キャラクターのクラスを取り込む
// メインキャラクター
#include "Entity_MainGame/MainCharacter/MainCharacter.h"

class C_MainGameScene :public C_State
{
public:

	// コンストラクタ
	C_MainGameScene();
	// デストラクタ
	~C_MainGameScene();

	// 初期化
	void Init()override;
	// 更新内容
	void Update()override;
	// 描画内容
	void Draw()override;
	// デバッグ画面に表示するもの
	void ImGuiUpdate()override;

private:

	// 「Game」の文字用の構造体変数
	S_Entity M_Game;

	// メインキャラクターのクラスのアドレス
	C_MainCharacter CM_MainCharacter;

};