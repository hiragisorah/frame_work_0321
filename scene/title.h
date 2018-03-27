#pragma once

// �t���[�����[�N
#include <framework\entity.h>

// �V�X�e��
#include <system\direct3d11.h>
#include <system\camera.h>

// �Q�[���I�u�W�F�N�g
#include <game_object\primitive3d.h>
#include <game_object\bone.h>

namespace Scene
{
	class Title : public Entity
	{
	public:
		Title(Entity * parent) : Entity(parent)
		{
			Game::GetSystem<System::Loader::Shader>()->Load<Data::Shader::Specular>();
			Game::GetSystem<System::Loader::Mesh>()->Load<Data::Mesh::Cube>();
			Game::GetSystem<System::Loader::Mesh>()->Load<Data::Mesh::Line3d>();
			auto a = this->AddChild<GameObject::Primitive3D>();
			auto b = this->AddChild<GameObject::Bone>();
			a->transform_->position_.x = 0.f;
			b->transform_->position_.x = 3.f;
		}
	};
}