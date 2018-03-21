#pragma once

// システム
#include <system\direct3d11.h>

// データ
#include <data\model.h>

// シェーダ
#include <data\shader\point3d.h>

// ローダー
#include <system\loader\shader.h>

namespace Data
{
	namespace Model
	{
		class Point3d : public IModel
		{
		public:
			Shader::Point3d * shader_;
			Shader::Point3d::CBUFFER cb_;

		public:
			Point3d(void)
			{
				this->shader_ = Game::GetSystem<System::Loader::Shader>()->Get<Shader::Point3d>();
			}

		private:
			void Rendering(void) override
			{
				auto d3d = Game::GetSystem<System::Direct3D11>();
				auto window = Game::GetSystem<System::Window>();
				auto camera = Game::GetSystem<System::Camera>();

				this->cb_.v_ = camera->GetView();
				this->cb_.p_ = camera->GetProjection();

				this->cb_.color_ = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);

				this->shader_->Setup();
				this->shader_->UpdateConstantBuffer(0, &this->cb_);

				//バーテックスバッファーをセット
				UINT stride = sizeof(Shader::Point3d::Vertex);
				UINT offset = 0;
				
				d3d->context_->IASetVertexBuffers(0, 1, &this->shader_->vertex_buffer_, &stride, &offset);
				//プリミティブ・トポロジーをセット
				d3d->context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
				//プリミティブをレンダリング
				d3d->context_->Draw(1, 0);
			}
		};
	}
}