#pragma once

// �t���[�����[�N
#include <framework\entity.h>

// �V�X�e��
#include <system\direct3d11.h>

// ���f��
#include <data\model\line3d.h>

namespace GameObject
{
	class Line3d : public Entity
	{
	private:
		Data::Model::Line3d model;

	public:
		Line3d(Entity * parent) : Entity(parent)
		{

		}

	private:
		void Update(void) override
		{
			D3DXMATRIX World;
			static float x = 0;
			x += 0.01f;
			D3DXMatrixTranslation(&World, x, 0.f, 0.f);

			this->model.cb_.w_ = World;
		}

		void Always(void) override
		{
			auto d3d = Game::GetSystem<System::Direct3D11>();

			d3d->AddToDrawList(&model);
		}
	};
}