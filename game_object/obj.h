#pragma once

// フレームワーク
#include <framework\entity.h>

// システム
#include <system\direct3d11.h>

// モデル
#include <data\model\obj.h>

namespace GameObject
{
	class Obj : public Entity
	{
	private:
		Data::Model::Obj model_;

	public:
		Obj(Entity * parent) : Entity(parent)
		{
			this->model_.Init("hand");
		}

	private:
		void Update(void) override
		{
			D3DXMATRIX World, scale;
			static float x = 0;
			x += 0.01f;
			D3DXMatrixScaling(&scale, .3f, .3f, .3f);
			D3DXMatrixRotationY(&World, x);

			this->model_.cb_.w_ = scale * World;
		}

		void Always(void) override
		{
			auto d3d = Game::GetSystem<System::Direct3D11>();

			d3d->AddToDrawList(&this->model_);
		}
	};
}