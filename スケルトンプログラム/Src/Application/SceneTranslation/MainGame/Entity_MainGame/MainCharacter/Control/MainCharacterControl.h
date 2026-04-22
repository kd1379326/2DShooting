#pragma once

// 前方宣言
class C_MainCharacter_MainGame;

class C_MainCharacterControl
{
public:

	// コンストラクタとデストラクタ
	C_MainCharacterControl();
	~C_MainCharacterControl();

	// キー操作
	void MoveKeyControl(Math::Vector2& A_Position, Math::Vector2& A_Move);


private:


};