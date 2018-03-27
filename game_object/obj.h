#pragma once

// �t���[�����[�N
#include <framework\entity.h>

// �V�X�e��
#include <system\direct3d11.h>

// ���f��
#include <data\model\obj.h>

// �R���|�[�l���g
#include <component\transform.h>
#include <component\test_animation.h>

namespace GameObject
{
	class Obj : public Entity
	{
	private:
		Data::Model::Obj model_ = {};

	public:
		Obj(Entity * parent) : Entity(parent)
		{
			this->model_.Init("cube");
			this->AddComponent<Component::Transform>();
			this->AddComponent<Component::TestAnimation>();
		}

	private:
		void Update(void) override
		{
			this->model_.cb_.w_ = this->GetComponent<Component::Transform>()->GetParentMatrix();
		}

		void Always(void) override
		{
			auto d3d = Game::GetSystem<System::Direct3D11>();

			d3d->AddToDrawList(&this->model_);
		}
	};
}