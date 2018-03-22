#pragma once

// �t���[�����[�N
#include <framework\entity.h>

// �V�X�e��
#include <system\direct3d11.h>

// ���b�V��
#include <data\mesh\square3d_normal_uv.h>

// ���f��
#include <data\model\shade_specular_tex_primitive.h>

namespace GameObject
{
	class ShadeSpecularTexPrimitive : public Entity
	{
	private:
		Data::Model::ShadeSpecularTexPrimitive<Data::Mesh::Square3dNormalUv> model_;

	public:
		ShadeSpecularTexPrimitive(Entity * parent) : Entity(parent)
		{
			this->model_.textures_[0] = "test.png";
		}

	private:
		void Update(void) override
		{
			D3DXMATRIX World;
			static float x = 0;
			x += 0.01f;
			D3DXMatrixRotationY(&World, x);
			this->model_.cb_.w_ = World;
		}

		void Always(void) override
		{
			auto d3d = Game::GetSystem<System::Direct3D11>();

			d3d->AddToDrawList(&this->model_);
		}
	};
}