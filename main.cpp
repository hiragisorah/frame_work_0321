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
#include <system\loader\mesh.h>
#include <system\loader\obj.h>

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
		Game::AddSystem<System::Loader::Mesh>();
		Game::AddSystem<System::Loader::Obj>();
		Game::AddSystem<System::Loader::Texture>();
	}

	{// ���[�h
		Game::GetSystem<System::Loader::Shader>()->Load<Data::Shader::Shade>();
		Game::GetSystem<System::Loader::Shader>()->Load<Data::Shader::Specular>();
		Game::GetSystem<System::Loader::Shader>()->Load<Data::Shader::ShadeSpecular>();
		Game::GetSystem<System::Loader::Shader>()->Load<Data::Shader::ShadeSpecularTex>();
		Game::GetSystem<System::Loader::Mesh>()->Load<Data::Mesh::Square3dNormal>();
		Game::GetSystem<System::Loader::Mesh>()->Load<Data::Mesh::Square3dNormalUv>();
		Game::GetSystem<System::Loader::Texture>()->Load("test.png");
	}

	{// �����ݒ�
		Game::GetSystem<System::SceneManager>()->ChangeScene<Scene::Title>();
	}

	{// �N��
		Game::Run();
	}
}