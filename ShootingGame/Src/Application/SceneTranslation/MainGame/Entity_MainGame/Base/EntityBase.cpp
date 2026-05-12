#include "EntityBase.h"

// 初期化内容はここに
void C_EntityBase_MainGame::Init(Math::Vector2 A_Position, bool AF_Turning)
{

}

// 操作関連の更新内容はここに
void C_EntityBase_MainGame::Action()
{

}

// 更新内容はここに(描画に使うMatrix(行列)や画像の指定もここ)
void C_EntityBase_MainGame::Update()
{

}

// 描画内容はここに
void C_EntityBase_MainGame::Draw()
{

}

// デバッグ画面に表示させるならここに
void C_EntityBase_MainGame::ImGuiUpdate()
{

}

// Updateに導入する関数
// 当たり判定のチェック(一対一用)
bool C_EntityBase_MainGame::HitEntity(Math::Vector2 A_Position1, Math::Vector2 A_Position2, Math::Vector2 A_Radius1, Math::Vector2 A_Radius2)
{
	// それぞれのキャラが直線状でどのくらい離れているか求める。(.Length()で離れている距離を算出できる)
	float Distance = (A_Position1 - A_Position2).Length();

	// 求めた直線状の距離とそれぞれの半径を足した値を比較し、数値から接触しているかどうか調べる。
	// 接触しているようならtrue、接触していないのならfalseを返す。
	if (Distance < A_Radius1.x + A_Radius2.x) { return true; }
	else { return false; }
}

// ダメージ処理(体力を減らす)
void C_EntityBase_MainGame::Damage(int A_DamageNumber)
{
	// 体力をダメージ分引いた値に置き換える。
	M_Entity.MS_HP -= A_DamageNumber;
	M_Entity.MSF_Damage = true;
	// 体力が0未満にならないよう固定する。
	if (M_Entity.MS_HP < 0) { M_Entity.MS_HP = 0; }
}

// ダメージを受けた時に後退する処理
void C_EntityBase_MainGame::Knockback(float A_BackDirection, float A_KnockbackPower)
{
	if (!M_Entity.MSF_Knockback) return;
	// どの方向に動くか決める。
	M_Entity.MS_Move.x = A_BackDirection;
	// どのくらい飛ばされるか決める。
	M_Entity.MS_MoveSpeed.x = A_KnockbackPower;
	M_Entity.MS_Position.x += M_Entity.MS_Move.x * M_Entity.MS_MoveSpeed.x;
	A_KnockbackPower--;
	if (A_KnockbackPower <= 0) { M_Entity.MSF_Knockback = false; }
}

void C_EntityBase_MainGame::ApplyKnockback(Math::Vector2 A_Dir, float A_Power)
{
	M_Entity.MS_KnockbackVector.x = A_Dir.x * A_Power;
	M_Entity.MS_KnockbackVector.y = A_Dir.y * A_Power;
}

void C_EntityBase_MainGame::ApplyKnockbackBullet(Math::Vector2 A_Dir, float A_Power)
{
	M_Entity.MS_KnockbackVector.x = A_Dir.x * A_Power;
}
