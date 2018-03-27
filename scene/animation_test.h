#pragma once

// �t���[�����[�N
#include <framework\entity.h>

// �V�X�e��
#include <system\direct3d11.h>
#include <system\camera.h>

// �Q�[���I�u�W�F�N�g
#include <game_object\primitive3d.h>
#include <game_object\bone.h>

// �R���|�[�l���g
#include <component\test_animation.h>

namespace Scene
{
	class AnimationTest : public Entity
	{
	public:
		AnimationTest(Entity * parent) : Entity(parent)
		{
			Game::GetSystem<System::Loader::Shader>()->Load<Data::Shader::Specular>();
			Game::GetSystem<System::Loader::Mesh>()->Load<Data::Mesh::Cube>();
			auto a = this->AddChild<GameObject::Primitive3D>();
			a->AddComponent<Component::TestAnimation>();
		}
	};
}