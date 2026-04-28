#pragma once

#include "../Title/TitleScene.h"
#include "../MainGame/MainGameScene.h"
#include "../Result/ResultScene.h"
#include "../GameOver/GameOverScene.h"

class C_SceneManager
{
public:

	static C_SceneManager& GetInstance()
	{
		static C_SceneManager Instance;
		return Instance;
	}

	void  ChangeState(std::shared_ptr<C_State>A_NewState)
	{
		CurrentState = A_NewState;
	}

	void Init()
	{
		CurrentState->Init();
	}

	void Update()
	{
		CurrentState->Update();
	}

	void Draw()
	{
		CurrentState->Draw();
	}

	void ImGuiUpdate()
	{
		CurrentState->ImGuiUpdate();
	}

private:

	C_SceneManager(){}

	std::shared_ptr<C_State>CurrentState = nullptr;
};

#define SCENEMANAGER C_SceneManager::GetInstance() // インスタンスがなくてもSCENEMANAGERで呼び出せる(シングルトンってやつ)