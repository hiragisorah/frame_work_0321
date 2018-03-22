#pragma once

// フレームワーク
#include <framework\entity.h>

// システム
#include <system\direct3d11.h>

// メッシュ
#include <data\mesh\square3d_uv.h>

// モデル
#include <data\model\sprite.h>

namespace GameObject
{
	class Sprite : public Entity
	{
	private:
		Data::Model::Sprite<Data::Mesh::Square3dUv> model_;

	public:
		Sprite(Entity * parent) : Entity(parent)
		{
			this->model_.textures_[0] = "test.png";
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