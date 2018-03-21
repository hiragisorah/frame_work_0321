#pragma once

// フレームワーク
#include <framework\entity.h>

// システム
#include <system\direct3d11.h>

// モデル
#include <data\model\square3d.h>

namespace GameObject
{
	class Square3d : public Entity
	{
	private:
		Data::Model::Square3d model;

	public:
		Square3d(Entity * parent) : Entity(parent)
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