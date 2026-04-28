#include "MainCharacter.h"

// 操作関連のクラス
#include "Control/KeyControl.h"

// このクラスが生成された時に動かしたいものをここに(コンストラクタ)
C_MainCharacter_MainGame::C_MainCharacter_MainGame()
{
	M_Entity.MS_Texture.Load("Texture/MainCharacter/MainCharacter.png");
}

// このクラスが削除される時に動かしたいものをここに(デストラクタ)
C_MainCharacter_MainGame::~C_MainCharacter_MainGame()
{
	// 自動で領域解放処理を行う。
	Release();
}

// 初期化内容はここに
void C_MainCharacter_MainGame::Init(Math::Vector2 A_Position)
{
	// 座標
		M_Entity.MS_Position = { -500, 0 };
	// 移動速度
		M_Entity.MS_MoveSpeed = { 20, 20 };
	// 移動量
		M_Entity.MS_Move = { 0, 0 };
	// 半径
		M_Entity.MS_Radius = { 32, 32 };
	// 画像の切り取り範囲
		M_Entity.MS_Rectangle = { 0, 0, 64, 64 };
	// 通常時の色
		M_Entity.MS_Color_Normal = { 1, 1, 1, 1.0f };
	// 生存している状態にする
		M_Entity.MSF_Alive = true;
	// まだ処理が残っているという情報を持たせる
		M_Entity.MSF_Delete = false;

	// キー操作の機能が入ったクラスの実体を作成
	CM_Control = std::make_shared<C_MainCharacter_KeyControl>();
	
}

// 操作関連の更新内容はここに
void C_MainCharacter_MainGame::Action()
{
	// キー操作による移動機能
	CM_Control->MoveKeyControl(M_Entity.MS_Position, M_Entity.MS_Move, M_Entity.MS_MoveSpeed, M_Entity.MS_Radius);
}

// 更新内容はここに
void C_MainCharacter_MainGame::Update()
{
	// キー操作クラスの更新処理
	CM_Control->Update();

	// やられた場合、削除フラグを立てる。
	if (!M_Entity.MSF_Alive) { M_Entity.MSF_Delete = true; }

	// 表示したい座標を設定する
	M_Entity.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_Entity.MS_Position.x, M_Entity.MS_Position.y, 0);

	// 描画の詳細をまとめる
	M_Entity.MS_Matrix = M_Entity.MS_TranslationMatrix;
}

// 描画内容はここに(行列(Matrix等)はUpdateに含まれる)
void C_MainCharacter_MainGame::Draw()
{
	SHADER.m_spriteShader.SetMatrix(M_Entity.MS_Matrix);
	SHADER.m_spriteShader.DrawColorTex(&M_Entity.MS_Texture, M_Entity.MS_Rectangle, M_Entity.MS_Color_Normal);
}

// デバッグ画面に出したい内容はここに
void C_MainCharacter_MainGame::ImGuiUpdate()
{

}

// 弾を撃つかどうか判断する
bool C_MainCharacter_MainGame::ShootBullet()
{
	// 射撃用のクールタイムが無い且つエンターキーが押されたらtrueが返される。
	return CM_Control->ShootingPermission();
}

// このクラスの実体が削除された時に行う領域解放処理。
void C_MainCharacter_MainGame::Release()
{
	// 画像を入れている領域を解放する。
	M_Entity.MS_Texture.Release();
}