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

	// EntityBase(キャラ達の親クラス)型の動的配列
	std::vector<C_EntityBase_MainGame*> CM_Entity;

};