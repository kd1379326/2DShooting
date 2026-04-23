#pragma once

class C_EntityBase_MainGame
{
public:

	// コンストラクタとデストラクタ
	C_EntityBase_MainGame() {}
	// デストラクタは仮想にしておかないと派生クラスが正しく消えない。
	virtual ~C_EntityBase_MainGame() {}

	// 機能が全派生クラス共通なら通常の関数、派生クラスによって機能が違うなら純粋仮想関数を使う。
	// 初期化
	virtual void Init() = 0;
	// 更新内容
	virtual void Update() = 0;
	// 描画内容
	virtual void Draw() = 0;
	// デバッグに表示するもの
	virtual void ImGuiUpdate() = 0;


	// 当たり判定
	bool HitEntity(Math::Vector2 A_Pos1, Math::Vector2 A_Pos2, Math::Vector2 A_Radius1, Math::Vector2 A_Radius2);

	// エンティティ(画像)を描画するために必要なもの(構造体)
	struct S_EntityCharacter
	{
		// 位置
			Math::Vector2		MS_Position;
		// 移動量
			Math::Vector2		MS_Move;
		// 半径(サイズ)
			Math::Vector2		MS_Radius;
		// 描画用のサイズ情報
			Math::Matrix			MS_ScaleMatrix;
		// 描画用の角度情報
			Math::Matrix			MS_RotateMatrix;
		// 描画用の座標情報
			Math::Matrix			MS_TranslationMatrix;
		// 行列(描画するエンティティの詳細情報)
			Math::Matrix			MS_Matrix;
		// 画像自体のデータ
			KdTexture				MS_Texture;
		// 画像の切り取り範囲
			Math::Rectangle	MS_Rectangle;
		// 画像の通常時の色
			Math::Color			MS_Color_Normal;
		// 角度
			float						MS_Rotate;
		// 移動速度
			float						MS_MoveSpeed_Normal;
		// 当たり判定の真偽を持たせる
			bool						MSF_Hit;
	};
	
private:

};