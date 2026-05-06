// C_・・・クラス
// M_・・・メンバ
// A_・・・引数
// E_・・・列挙体

// それぞれのゲームの大雑把な構成要素(シーン)で最低限必要な関数や変数などを用意する。

#pragma once

class C_State
{
public:

	// このクラスが作成、削除されたときにさせたい機能を書く(インストラクタとデストラクタ)
	C_State() {}
	virtual ~C_State() = 0{};

	// 純粋仮想関数(virtualと=0を付ける)だと派生クラス(ゲームの大雑把な構成要素)で呼び出し忘れることがなくなる。
	// 仮想関数(virtualを付ける)だと派生クラスで呼び出し忘れても動いてしまう。
	// 初期化用
	virtual void Init()					= 0;
	// 更新前に行う更新
	virtual void PreUpdate()			= 0;
	// 更新処理
	virtual void Update()				= 0;
	// 更新後に行う更新
	virtual void PostUpdate()		= 0;
	// 2D描画
	virtual void DrawSprite()		= 0;
	// デバッグ表示
	virtual void ImGuiUpdate()		= 0;

	// エンティティ(画像)を描画するために必要なもの(構造体)
	struct S_Entity
	{
		// 位置
		Math::Vector2	MS_Position;
		// 移動量
		Math::Vector2	MS_Move;
		// サイズ
		Math::Matrix		MS_ScaleMatrix;
		// 角度
		Math::Matrix		MS_RotateMatrix;
		// 座標
		Math::Matrix		MS_TranslationMatrix;
		// 行列(描画するエンティティの詳細情報)
		Math::Matrix		MS_Matrix;
		// 画像自体のデータ
		KdTexture*		MSP_Texture;
	};

	// ENTER押し続けて連続でシーン遷移しないようにフラグで管理する。
	bool MF_Stop_ContinuitySceneTransition;

};