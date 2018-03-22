#pragma once

// �t���[�����[�N
#include <framework\entity.h>

// �V�X�e��
#include <system\direct3d11.h>
#include <system\camera.h>

// �Q�[���I�u�W�F�N�g
#include <game_object\shade_specular_tex_primitive.h>
#include <game_object\specular_primitive.h>
#include <game_object\shade_primitive.h>
#include <game_object\shade_specular_primitive.h>

namespace Scene
{
	class Title : public Entity
	{
	public:
		Title(Entity * parent) : Entity(parent)
		{
			this->AddChild<GameObject::ShadeSpecularTexPrimitive>();
			//this->AddChild<GameObject::ShadeSpecularPrimitive>();
			//this->AddChild<GameObject::ShadePrimitive>();
			//this->AddChild<GameObject::SpecularPrimitive>();
		}
	};
}