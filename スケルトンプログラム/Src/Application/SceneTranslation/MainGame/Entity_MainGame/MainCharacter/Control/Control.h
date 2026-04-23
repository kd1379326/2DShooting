#pragma once

// 前方宣言
class C_MainCharacter_MainGame;

class C_MainCharacterControl
{
public:

	// コンストラクタとデストラクタ
	C_MainCharacterControl();
	~C_MainCharacterControl();

	// 様々な変数の計算をここで行う。
	void Update();

	// キー操作
	void MoveKeyControl(Math::Vector2& A_Position, Math::Vector2& A_Move);

	// エンターキーが押されたときに弾を放って良いと合図する
	bool ShootingPermission();



private:

	// 現在のクールタイムが入っている。
	int M_NowCoolTime = 0;
	// クールタイムの長さが入っている。
	int M_CoolTime = 3 * 60;

};