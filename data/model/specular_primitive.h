#pragma once

// システム
#include <system\direct3d11.h>
#include <system\camera.h>

// データ
#include <data\model.h>

// シェーダ
#include <data\shader\specular.h>

// ローダー
#include <system\loader\shader.h>
#include <system\loader\mesh.h>

namespace Data
{
	namespace Model
	{
		template<class _Mesh>
		class SpecularPrimitive : public IModel
		{
		public:
			IMesh * mesh_;
			Shader::Specular * shader_;
			Shader::Specular::CBUFFER cb_;

		public:
			SpecularPrimitive(void)
			{
				this->shader_ = Game::GetSystem<System::Loader::Shader>()->Get<Shader::Specular>();
				this->mesh_ = Game::GetSystem<System::Loader::Mesh>()->Get<_Mesh>();
			}

		private:
			void Rendering(void) override
			{
				auto d3d = Game::GetSystem<System::Direct3D11>();
				auto camera = Game::GetSystem<System::Camera>();

				this->cb_.v_ = camera->GetView();
				this->cb_.p_ = camera->GetProjection();

				this->cb_.diffuse_ = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

				this->cb_.light_dir_ = { 0.f, 0.f, 1.f, 0.f };
				this->cb_.eye_ = { camera->eye_, 0.f };

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