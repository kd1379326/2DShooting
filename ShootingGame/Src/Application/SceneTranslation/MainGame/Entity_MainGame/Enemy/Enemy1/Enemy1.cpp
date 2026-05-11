#include "Enemy1.h"

// Sceneクラスのヘッダー
#include "../../../../../Scene.h"

// ランダム値をくれるヘッダー
#include "../../../../../Tool/RandomNumericalValue.h"

// 動作処理を行うクラス
#include "Control/Enemy1_Move.h"


// このクラスが生成された時に動かしたいものをここに(コンストラクタ)
C_Enemy1_MainGame::C_Enemy1_MainGame()
{
}

// このクラスが削除される時に動かしたいものをここに(デストラクタ)
C_Enemy1_MainGame::~C_Enemy1_MainGame()
{
	// 自動で領域解放処理を行う。
	Release();
}

// 初期化内容はここに
void C_Enemy1_MainGame::Init(Math::Vector2 A_Position, bool AF_Turning)
{
	// 画像のパス(在処)を伝える
		M_Entity.MS_Texture.Load("Texture/MainCharacter/MainCharacter仮.png");
	// 半径のサイズ
		M_Entity.MS_Radius = { 32, 32 };

	// 座標(1280×720の範囲で出現させる)
	// 画面サイズをSceneクラスから引っ張ってきて、半径分をも含めた値をランダム値を返す関数の引数に置く。
	// 画面右端の見えない位置で上下は画面内に納まる座標をランダムに取り出す。
		M_Entity.MS_Position.x = ((float)Scene::Instance().Getter_ScreenSize_Right() + M_Entity.MS_Radius.x);
		M_Entity.MS_Position.y = (float)C_RandomNumericalValue::Instance().RandomNumericalValue((Scene::Instance().Getter_ScreenSize_Top()    - M_Entity.MS_Radius.y), (Scene::Instance().Getter_ScreenSize_Bottom() + M_Entity.MS_Radius.y));
	// 移動量
		M_Entity.MS_Move = { 0, 0 };
	// 移動スピード
		M_Entity.MS_MoveSpeed = { 3, 3 };
	// 画像の切り取り範囲
		M_Entity.MS_Rectangle = { 0, 0, 50, 50 };
	// 画像の通常時の色(設定なし)
		M_Entity.MS_Color_Normal = { 1, 0, 0, 1 };
	// 残りの硬直時間
		M_Entity.MS_DamageStiffness_RemainingTime = 0;
	// 硬直時間(秒×フレーム)
		M_Entity.MS_DamageStiffness_Time = 1 * 60;
	// 攻撃の吹っ飛ばし力
		M_Entity.MS_KnockbackPower = 20;
	// 体力
		M_Entity.MS_HP = 3;
	// 角度
		M_Entity.MS_Rotate = 90;
	// 攻撃力
		M_Entity.MS_Power = 1;
	// 生存している状態にする
		M_Entity.MSF_Alive = true;
	// まだ処理が残っているという情報を持たせる
		M_Entity.MSF_Delete = false;
	// 何もされていないので硬直無しにする
		M_Entity.MSF_DamageStiffness = false;
	// 最初は誰とも接触していないのでノックバックも無し
		M_Entity.MSF_Knockback = false;
	// 始めは旋回しない
		M_Entity.MSF_TurningFlag = false;
	// 操作処理を行うクラスのインスタンスを作成
		if (!CMP_Control) { CMP_Control = std::make_shared<C_Enemy1_Move>(); }
	// C_Enemy1_Moveの初期化
		CMP_Control->Init(M_Entity);
}

// 操作関連の更新内容はここに
void C_Enemy1_MainGame::Action()
{
	// ノックバック中は操作不能にする。
	//if (!M_Entity.MSF_Knockback)
	{
		CMP_Control->Action(M_Entity);
	}
}

// 更新内容はここに(描画に使うMatrix(行列)の作成や画像の指定もここ)
void C_Enemy1_MainGame::Update()
{
	// 左端を超えたらもう画面内には戻らないので削除許可を出す。
	//if (M_Entity.MS_Position.x < (Scene::Instance().Getter_ScreenSize_Left() - M_Entity.MS_Radius.x)) { M_Entity.MSF_Delete = true; }

	// 現在座標にベクトルを足して弾くように移動させる。
	M_Entity.MS_Position += M_Entity.MS_KnockbackVector;

	// 常にベクトルを足し続けると止まらない為、徐々にベクトルを小さくしていく。
	M_Entity.MS_KnockbackVector *= 0.85f;

	// ベクトルが0になるのにかなり時間が掛かる為、一定の数値まで下がったら強制的に0にする。
	if (std::abs(M_Entity.MS_KnockbackVector.x) < 1.0f) M_Entity.MS_KnockbackVector.x = 0.0f;
	if (std::abs(M_Entity.MS_KnockbackVector.y) < 1.0f) M_Entity.MS_KnockbackVector.y = 0.0f;

	// 体力が0になったらやられた判定にする。
	if (M_Entity.MS_HP <= 0) { M_Entity.MSF_Alive = false; }

	// やられた場合、削除フラグを立てる。
	if (!M_Entity.MSF_Alive) { M_Entity.MSF_Delete = true; }

	// 旋回する場合は反転させる
	if (M_Entity.MSF_TurningFlag) { M_Entity.MS_Rotate = -90; }


	// どこに描画するか座標情報を設定する。
	M_Entity.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_Entity.MS_Position.x, M_Entity.MS_Position.y, 0);
	M_Entity.MS_RotateMatrix = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(M_Entity.MS_Rotate));

	// 描画の詳細をまとめる
	M_Entity.MS_Matrix = M_Entity.MS_RotateMatrix * M_Entity.MS_TranslationMatrix;


}

// 描画処理はここに
void C_Enemy1_MainGame::Draw()
{
	// 描画情報を伝える
	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(M_Entity.MS_Matrix);
	// 描画処理
	KdShaderManager::GetInstance().m_spriteShader.DrawColorTex(&M_Entity.MS_Texture, M_Entity.MS_Rectangle, M_Entity.MS_Color_Normal);
}

// デバッグ画面に表示させたいものはここに
void C_Enemy1_MainGame::ImGuiUpdate()
{
	ImGui::Text(u8"敵の座標：X-%.0f｜Y-%.0f", M_Entity.MS_Position.x, M_Entity.MS_Position.y);
}

// 弾を撃つかどうか判断する
bool C_Enemy1_MainGame::ShootBullet()
{
	// 射撃用のクールタイムが無い且つエンターキーが押されたらtrueが返される。
	return CMP_Control->ShootingPermission();
}

// このクラスの実体が削除された時に行う領域解放処理。
void C_Enemy1_MainGame::Release()
{
	// 画像を入れている領域を解放する。
	M_Entity.MS_Texture.Release();
}

// 旋回フラグ
bool C_Enemy1_MainGame::Getter_TurningFlag() { return CMP_Control->Getter_TurningFlag(); }