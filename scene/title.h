#pragma once

// �t���[�����[�N
#include <framework\entity.h>

// �V�X�e��
#include <system\direct3d11.h>

// �Q�[���I�u�W�F�N�g
#include <game_object\point3d.h>

namespace Scene
{
	class Title : public Entity
	{
	public:
		Title(Entity * parent) : Entity(parent)
		{
			this->AddChild<GameObject::Point3d>();
		}
	};
}