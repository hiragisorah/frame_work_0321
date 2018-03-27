#pragma once

// システム
#include <system\direct3d11.h>
#include <system\camera.h>

// データ
#include <data\model.h>

// シェーダ
#include <data\shader\default3d.h>

// ローダー
#include <system\loader\shader.h>
#include <system\loader\mesh.h>

namespace Data
{
	namespace Model
	{
		template<class _Mesh>
		class Primitive3D : public IModel
		{
		public:
			IMesh * mesh_ = nullptr;
			Shader::Specular * shader_;
			Shader::Specular::CBUFFER cb_;

		public:
			Primitive3D(void)
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
				this->cb_.eye_ = { camera->eye_, 0.f };
				this->cb_.light_dir_ = { 0.f, .1f, -.1f, 1.f };
				this->cb_.diffuse_ = { .1f, .5f, .5f, 1.f };

				this->shader_->Setup();
				this->shader_->UpdateConstantBuffer(0, &this->cb_);

				//プリミティブ・トポロジーをセット
				d3d->context_->IASetPrimitiveTopology(this->mesh_->topology_);

				d3d->context_->IASetVertexBuffers(0, 1, &this->mesh_->vertex_buffer_, &this->mesh_->stride_, &this->mesh_->offset_);

				if (this->mesh_->index_buffer_)
				{
					d3d->context_->IASetIndexBuffer(this->mesh_->index_buffer_, DXGI_FORMAT_R32_UINT, 0);
					//プリミティブをレンダリング
					d3d->context_->DrawIndexed(this->mesh_->index_num_, 0, 0);
				}
				else
				{
					//プリミティブをレンダリング
					d3d->context_->Draw(this->mesh_->vtx_num_, 0);
				}
			}
		};
	}
}