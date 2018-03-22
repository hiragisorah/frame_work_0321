#pragma once

// フレームワーク
#include <framework\entity.h>

// システム
#include <system\direct3d11.h>

// メッシュ
#include <data\mesh\square3d_normal.h>

// モデル
#include <data\model\common_primitive3d.h>

namespace GameObject
{
	class CommonPrimitive3d : public Entity
	{
	private:
		Data::Model::CommonPrimitive3D<Data::Mesh::Square3dNormal> model_;

	public:
		CommonPrimitive3d(Entity * parent) : Entity(parent)
		{

		}

	private:
		void Update(void) override
		{
			D3DXMATRIX World;
			static float x = 0;
			x += 0.01f;
			D3DXMatrixRotationY(&World, x);
			D3DXMatrixTranspose(&World, &World);
			this->model_.cb_.w_ = World;
		}

		void Always(void) override
		{
			auto d3d = Game::GetSystem<System::Direct3D11>();

			d3d->AddToDrawList(&this->model_);
		}
	};
}