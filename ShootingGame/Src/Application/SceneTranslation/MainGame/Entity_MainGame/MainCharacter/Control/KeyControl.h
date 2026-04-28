#pragma once

// 前方宣言
class C_MainCharacter_MainGame;

class C_MainCharacter_KeyControl
{
public:

	// コンストラクタとデストラクタ
	C_MainCharacter_KeyControl();
	~C_MainCharacter_KeyControl();

	// 様々な変数の計算をここで行う。
	void Update();

	// キー操作
	void MoveKeyControl(Math::Vector2& A_Position, Math::Vector2& A_Move, Math::Vector2& A_MoveSpeed, Math::Vector2& A_Radius);

	// エンターキーが押されたときに弾を放って良いと合図する
	bool ShootingPermission();



private:

	// 現在のクールタイムが入っている。
	int M_NowCoolTime = 0;
	// クールタイムの長さが入っている。
	float M_CoolTime = 0.05f * 60;

};