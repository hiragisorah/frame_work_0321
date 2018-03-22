#pragma once

// �t���[�����[�N
#include <framework\entity.h>

// �V�X�e��
#include <system\direct3d11.h>

// ���b�V��
#include <data\mesh\line3d.h>
#include <data\mesh\line2d.h>

// ���f��
#include <data\model\primitive3d.h>
#include <data\model\primitive2d.h>

namespace GameObject
{
	class Primitive3D : public Entity
	{
	private:
		Data::Model::Primitive3D<Data::Mesh::Line3d> model_;

	public:
		Primitive3D(Entity * parent) : Entity(parent)
		{

		}

	private:
		void Update(void) override
		{
			D3DXMATRIX World;
			static float x = 0;
			x += 0.1f;
			D3DXMatrixTranslation(&World, x, 0.f, 0.f);

			this->model_.cb_.w_ = World;
		}

		void Always(void) override
		{
			auto d3d = Game::GetSystem<System::Direct3D11>();

			d3d->AddToDrawList(&this->model_);
		}
	};
}