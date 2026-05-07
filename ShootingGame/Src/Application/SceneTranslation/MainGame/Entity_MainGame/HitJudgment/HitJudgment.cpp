#include "HitJudgment.h"

bool C_HitJudgment::HitJudgment(Math::Vector2 A_Position1, Math::Vector2 A_Radius1, Math::Vector2 A_Position2, Math::Vector2 A_Radius2)
{
	// それぞれのキャラが直線状でどのくらい離れているか求める。
	Math::Vector2 Distance = A_Position1 - A_Position2;

	// 求めた直線状の距離とそれぞれの半径を足した値を比較し、数値から接触しているかどうか調べる。
	// 接触しているようならtrue、接触していないのならfalseを返す。
	if (Distance.Length() < A_Radius1.x + A_Radius2.x)	{ return true; }
	else												{ return false; }
}