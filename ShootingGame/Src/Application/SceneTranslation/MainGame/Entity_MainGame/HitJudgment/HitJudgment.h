#pragma once

class C_HitJudgment
{
public:
	// コンストラクタとデストラクタ
	C_HitJudgment() {}
	~C_HitJudgment() {}

	// 接触したか確認する。
	bool HitJudgment(Math::Vector2 A_Position1, Math::Vector2 A_Radius1, Math::Vector2 A_Position2, Math::Vector2 A_Radius2);

	static C_HitJudgment& Instance()
	{
		static C_HitJudgment Instance;
		return Instance;
	}

};