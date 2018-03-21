#pragma once

// システム
#include <system\direct3d11.h>

// データ
#include <data\model.h>

// メッシュ
#include <data\mesh\point3d.h>

// シェーダ
#include <data\shader\default3d.h>

// ローダー
#include <system\loader\shader.h>
#include <system\loader\mesh.h>

namespace Data
{
	namespace Model
	{
		class Point3d : public IModel
		{
		public:
			Mesh::Point3d * mesh_;
			Shader::Default3d * shader_;
			Shader::Default3d::CBUFFER cb_;

		public:
			Point3d(void)
			{
				this->shader_ = Game::GetSystem<System::Loader::Shader>()->Get<Shader::Default3d>();
				this->mesh_ = Game::GetSystem<System::Loader::Mesh>()->Get<Mesh::Point3d>();
			}

		private:
			void Rendering(void) override
			{
				auto d3d = Game::GetSystem<System::Direct3D11>();
				auto camera = Game::GetSystem<System::Camera>();

				this->cb_.v_ = camera->GetView();
				this->cb_.p_ = camera->GetProjection();

				this->cb_.color_ = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);

				this->shader_->Setup();
				this->shader_->UpdateConstantBuffer(0, &this->cb_);

				d3d->context_->IASetVertexBuffers(0, 1, &this->mesh_->vertex_buffer_, &this->mesh_->stride_, &this->mesh_->offset_);
				//プリミティブ・トポロジーをセット
				d3d->context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
				//プリミティブをレンダリング
				d3d->context_->Draw(this->mesh_->vtx_num_, 0);
			}
		};
	}
}