#pragma once

// シーンの基底クラス
#include "../SceneManager&State/State.h"

class C_GameOverScene : public C_State
{
public:
	// コンストラクタとデストラクタ
	C_GameOverScene();
	~C_GameOverScene()  override;

	// 初期化用
	void Init()						override;
	// 更新前に行う更新
	void PreUpdate()			override;
	// 更新処理
	void Update()				override;
	// 更新後に行う更新
	void PostUpdate()			override;
	// 2D描画
	void DrawSprite()			override;
	// デバッグ表示
	void ImGuiUpdate()		override;


private:

	// 解放処理
	void Release();

	S_Entity M_GameOver;


};