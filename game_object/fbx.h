#pragma once

// �t���[�����[�N
#include <framework\entity.h>

// �V�X�e��
#include <system\direct3d11.h>

// ���f��
#include <data\model\fbx.h>

// �R���|�[�l���g
#include <component\transform.h>
#include <component\test_animation.h>

namespace GameObject
{
	class Fbx : public Entity
	{
	private:
		Data::Model::Fbx model_ = {};

	public:
		Fbx(Entity * parent) : Entity(parent)
		{
			this->model_.Init("swordman.fbx");
			this->AddComponent<Component::Transform>();
			//this->AddComponent<Component::TestAnimation>();
		}

	private:
		void Update(void) override
		{
			this->GetComponent<Component::Transform>()->rotation_.y += 1.f;
			this->model_.cb_.w_ = this->GetComponent<Component::Transform>()->GetParentMatrix();
		}

		void Always(void) override
		{
			this->model_.AddToDrawList();
		}
	};
}