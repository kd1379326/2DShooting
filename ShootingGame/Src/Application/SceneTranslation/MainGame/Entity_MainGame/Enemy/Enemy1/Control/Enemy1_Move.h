#pragma once

#include "../../../Base/EntityBase.h"

class C_Enemy1_Move
{
public:

	// コンストラクタとデストラクタ
	C_Enemy1_Move();
	~C_Enemy1_Move();

	// 初期化
	void Init(C_EntityBase_MainGame::S_EntityCharacter& A_Entity);
	// 更新処理
	void Action(C_EntityBase_MainGame::S_EntityCharacter& A_Entity);
	// 弾発射確認
	bool ShootingPermission();

	// ゲッター
	// 旋回フラグ
	bool Getter_TurningFlag() { return MF_TurningFlag; }

private:

	// 解放処理
	void Release();

	// 移動処理
	void Move(C_EntityBase_MainGame::S_EntityCharacter& A_Entity);


	// 弾を撃つかどうかのフラグ(撃つ：true　撃たない：false)
	bool MF_ShootingFlag = false;

	// 出現後、前に出てきて止まる位置。
	int M_StopPosition;

	// 弾を撃つまでのクールタイム
	float M_NowShootingCoolTime = M_ShootingCoolTime;

	// クールタイムの長さが入っている。
	float M_ShootingCoolTime = 5.0f * 60;

	// 旋回フラグ(する：true　しない：false)
	bool MF_TurningFlag = false;

};