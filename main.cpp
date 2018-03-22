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
	}

	{// ロード
		Game::GetSystem<System::Loader::Shader>()->Load<Data::Shader::Shade>();
		Game::GetSystem<System::Loader::Shader>()->Load<Data::Shader::Specular>();
		Game::GetSystem<System::Loader::Shader>()->Load<Data::Shader::ShadeSpecular>();
		Game::GetSystem<System::Loader::Shader>()->Load<Data::Shader::ShadeSpecularTex>();
		Game::GetSystem<System::Loader::Mesh>()->Load<Data::Mesh::Square3dNormal>();
		Game::GetSystem<System::Loader::Mesh>()->Load<Data::Mesh::Square3dNormalUv>();
		Game::GetSystem<System::Loader::Texture>()->Load("test.png");
	}

	{// 初期設定
		Game::GetSystem<System::SceneManager>()->ChangeScene<Scene::Title>();
	}

	{// 起動
		Game::Run();
	}
}