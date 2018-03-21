// フレームワーク
#include <framework\game.h>

// システム
#include <system\window.h>
#include <system\direct3d11.h>
#include <system\scene_manager.h>
#include <system\camera.h>

// シーン
#include <scene\title.h>

// ローダー
#include <system\loader\shader.h>

// 標準ライブラリ
#include <crtdbg.h>

#ifdef _DEBUG
void main(void)
{
	{// メモリーリーク検出
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	}
#else
int __stdcall WinMain(HINSTANCE, HINSTANCE, char*, int)
{
#endif

	{// システムの追加
		Game::AddSystem<System::Window>();
		Game::AddSystem<System::Direct3D11>();
		Game::AddSystem<System::SceneManager>();
		Game::AddSystem<System::Camera>();
		Game::AddSystem<System::Loader::Shader>();
	}

	{// ロード
		Game::GetSystem<System::Loader::Shader>()->Load<Data::Shader::Default2d>();
		Game::GetSystem<System::Loader::Shader>()->Load<Data::Shader::Default3d>();
		Game::GetSystem<System::Loader::Shader>()->Load<Data::Shader::Default2d>();
		Game::GetSystem<System::Loader::Shader>()->Load<Data::Shader::Default3d>();
		Game::GetSystem<System::Loader::Shader>()->Load<Data::Shader::Default2d>();
		Game::GetSystem<System::Loader::Shader>()->Load<Data::Shader::Default3d>();
		Game::GetSystem<System::Loader::Shader>()->Load<Data::Shader::Default2d>();
		Game::GetSystem<System::Loader::Shader>()->Load<Data::Shader::Default3d>();
	}

	{// 初期設定
		Game::GetSystem<System::SceneManager>()->ChangeScene<Scene::Title>();
	}

	{// 起動
		Game::Run();
	}
}