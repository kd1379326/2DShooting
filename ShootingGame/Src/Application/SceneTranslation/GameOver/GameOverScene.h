#pragma once

// シーンの基底クラス
#include "../SceneManager&State/State.h"

class C_GameOverScene : public C_State
{
public:
	// コンストラクタとデストラクタ
	C_GameOverScene();
	~C_GameOverScene()  override;

	// 初期化処理
	void Init()					override;
	// 更新処理
	void Update()			override;
	// 描画処理
	void Draw()				override;
	// デバッグ表示
	void ImGuiUpdate()	override;


private:

	// 解放処理
	void Release();

	S_Entity M_GameOver;


};