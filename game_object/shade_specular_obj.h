#pragma once

// �t���[�����[�N
#include <framework\entity.h>

// �V�X�e��
#include <system\direct3d11.h>

// ���f��
#include <data\model\shade_specular_obj.h>

// �R���|�[�l���g
#include <component\transform.h>

namespace GameObject
{
	class ShadeSpecularObj : public Entity
	{
	private:
		Data::Model::ShadeSpecularObj model_;

	public:
		ShadeSpecularObj(Entity * parent) : Entity(parent)
		{
			this->model_.Init("swordman");
			this->AddComponent<Component::Transform>();
			auto transform = this->GetComponent<Component::Transform>();
			transform->scale_ = { .4f, .4f, .4f };
		}

	private:
		void Update(void) override
		{
			//auto transform = this->GetComponent<Component::Transform>();
			//transform->rotation_.y += 0.3f;
			this->model_.cb_.w_ = this->GetComponent<Component::Transform>()->GetParentMatrix();
		}

		void Always(void) override
		{
			auto d3d = Game::GetSystem<System::Direct3D11>();

			d3d->AddToDrawList(&this->model_);
		}
	};
}