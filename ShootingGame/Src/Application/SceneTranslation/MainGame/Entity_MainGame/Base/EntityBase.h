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
	virtual void Init(Math::Vector2 A_Position = {0, 0})	= 0;
	// 操作の更新
	virtual void Action()													= 0;
	// 更新内容
	virtual void Update()													= 0;
	// 描画内容
	virtual void Draw()														= 0;
	// デバッグに表示するもの
	virtual void ImGuiUpdate()											= 0;

	// 弾を撃つかどうか判断する
	virtual bool ShootBullet()											= 0;

	// 値を知らせるゲッター
	// 自身の現在地(座標)
	Math::Vector2	Getter_MyPosition()	{ return M_Entity.MS_Position; }
	// 自身の半径
	Math::Vector2	Getter_Radius()			{ return M_Entity.MS_Radius; }
	// 生存しているかどうか
	bool					Getter_AliveFlag()		{ return M_Entity.MSF_Alive; }
	// 実体を消していいかどうか(良いtrue：ダメfalse)
	bool					Getter_DeleteFlag()	{ return M_Entity.MSF_Delete; }

	// 値を入れるセッター
	// やられた時にfalseをここに入れる。
	void Setter_AliveFlag(bool A_Alive) { M_Entity.MSF_Alive = A_Alive; }

	// 当たり判定
	bool HitEntity(Math::Vector2 A_Pos1, Math::Vector2 A_Pos2, Math::Vector2 A_Radius1, Math::Vector2 A_Radius2);
	

	// エンティティ(画像)を描画するために必要なもの(構造体)
	struct S_EntityCharacter
	{
		// 位置
			Math::Vector2		MS_Position;
		// 移動量
			Math::Vector2		MS_Move;
		// 移動速度
			Math::Vector2		MS_MoveSpeed;
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
		// 当たり判定の真偽を持たせる(当たったらtrue：当たってなかったらfalse)
			bool						MSF_Hit;
		// 生きているかの真偽を持たせる(生きていたらtrue：やられていたらfalse)
			bool						MSF_Alive;
		// 消去するべきかの真偽を持たせる(もう何も動かさないのならtrue：まだ消去しちゃダメならfalse)
			bool						MSF_Delete;
	};

	// 構造体変数
	S_EntityCharacter M_Entity;
	
private:

};