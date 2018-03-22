#pragma once

// システム
#include <system\direct3d11.h>

// データ
#include <data\model.h>

// シェーダ
#include <data\shader\default2d.h>

// ローダー
#include <system\loader\shader.h>
#include <system\loader\mesh.h>

namespace Data
{
	namespace Model
	{
		template<class _Mesh>
		class Primitive2D : public IModel
		{
		public:
			IMesh * mesh_ = nullptr;
			Shader::Default2d * shader_;
			Shader::Default2d::CBUFFER cb_;

		public:
			Primitive2D(void)
			{
				this->shader_ = Game::GetSystem<System::Loader::Shader>()->Get<Shader::Default2d>();
				this->mesh_ = Game::GetSystem<System::Loader::Mesh>()->Get<_Mesh>();
			}

		private:
			void Rendering(void) override
			{
				auto d3d = Game::GetSystem<System::Direct3D11>();
				auto window = Game::GetSystem<System::Window>();

				this->cb_.viewport_ = { window->Width<float>(), window->Height<float>() };

				this->cb_.color_ = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);

				this->shader_->Setup();
				this->shader_->UpdateConstantBuffer(0, &this->cb_);

				d3d->context_->IASetVertexBuffers(0, 1, &this->mesh_->vertex_buffer_, &this->mesh_->stride_, &this->mesh_->offset_);
				//プリミティブ・トポロジーをセット
				d3d->context_->IASetPrimitiveTopology(this->mesh_->topology_);
				//プリミティブをレンダリング
				d3d->context_->Draw(this->mesh_->vtx_num_, 0);
			}
		};
	}
}