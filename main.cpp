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
#include <system\loader\mesh.h>
#include <system\loader\obj.h>
#include <system\loader\fbx.h>

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
		Game::AddSystem<System::Loader::Mesh>();
		Game::AddSystem<System::Loader::Obj>();
		Game::AddSystem<System::Loader::Texture>();
		Game::AddSystem<System::Loader::Fbx>();
	}

	{// ロード
		
	}

	{// 初期設定
		Game::GetSystem<System::SceneManager>()->ChangeScene<Scene::Title>();
	}

	{// 起動
		Game::Run();
	}
}