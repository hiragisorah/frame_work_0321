#pragma once

// �t���[�����[�N
#include <framework\entity.h>

// �V�X�e��
#include <system\direct3d11.h>

// ���b�V��
#include <data\mesh\line3d.h>
#include <data\mesh\cube.h>

// ���f��
#include <data\model\primitive3d.h>

// �R���|�[�l���g
#include <component\transform.h>

namespace GameObject
{
	class Bone: public Entity
	{
	private:
		Data::Model::Primitive3D<Data::Mesh::Line3d> model_;

	public:
		Component::Transform * transform_;

	public:
		Bone(Entity * parent) : Entity(parent)
		{
			this->transform_ = this->AddComponent<Component::Transform>();
		}

	private:
		void Update(void) override
		{
			this->model_.cb_.w_ = this->transform_->GetParentMatrix();
		}

		void Always(void) override
		{
			auto d3d = Game::GetSystem<System::Direct3D11>();

			d3d->AddToDrawList(&this->model_);
		}
	};
}