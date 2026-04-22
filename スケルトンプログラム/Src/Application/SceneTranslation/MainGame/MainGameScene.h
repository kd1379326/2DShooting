#pragma once

// シーンの基礎となるクラス(基底クラス)を取り込む
#include "../SceneManager&State/State.h"

// キャラクターのクラスを前方宣言(どんなクラスがあるのか教える)
// ヘッダーファイルには基本的にヘッダーは取り込まない。
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

	// 領域解放処理はこの実体が削除された時にデストラクタで自動で呼び出されるためprivateに置く。
	void Release();

	// 「Game」の文字用の構造体変数
	S_Entity M_Game;

	// メインキャラクターのクラスのアドレス
	C_MainCharacter_MainGame* CM_MainCharacter = nullptr;

	// 敵１のクラスのアドレス
	C_Enemy1_MainGame*	CM_Enemy1 = nullptr;

};