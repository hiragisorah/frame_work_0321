// �t���[�����[�N
#include <framework\game.h>

// �V�X�e��
#include <system\window.h>
#include <system\direct3d11.h>
#include <system\scene_manager.h>
#include <system\camera.h>

// �V�[��
#include <scene\title.h>

// ���[�_�[
#include <system\loader\shader.h>

// �W�����C�u����
#include <crtdbg.h>

#ifdef _DEBUG
void main(void)
{
	{// �������[���[�N���o
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	}
#else
int __stdcall WinMain(HINSTANCE, HINSTANCE, char*, int)
{
#endif

	{// �V�X�e���̒ǉ�
		Game::AddSystem<System::Window>();
		Game::AddSystem<System::Direct3D11>();
		Game::AddSystem<System::SceneManager>();
		Game::AddSystem<System::Camera>();
		Game::AddSystem<System::Loader::Shader>();
	}

	{// ���[�h
		Game::GetSystem<System::Loader::Shader>()->Load<Data::Shader::Default2d>();
		Game::GetSystem<System::Loader::Shader>()->Load<Data::Shader::Default3d>();
		Game::GetSystem<System::Loader::Shader>()->Load<Data::Shader::Default2d>();
		Game::GetSystem<System::Loader::Shader>()->Load<Data::Shader::Default3d>();
		Game::GetSystem<System::Loader::Shader>()->Load<Data::Shader::Default2d>();
		Game::GetSystem<System::Loader::Shader>()->Load<Data::Shader::Default3d>();
		Game::GetSystem<System::Loader::Shader>()->Load<Data::Shader::Default2d>();
		Game::GetSystem<System::Loader::Shader>()->Load<Data::Shader::Default3d>();
	}

	{// �����ݒ�
		Game::GetSystem<System::SceneManager>()->ChangeScene<Scene::Title>();
	}

	{// �N��
		Game::Run();
	}
}