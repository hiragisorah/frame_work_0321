#pragma once

// システム
#include <system\direct3d11.h>

// データ
#include <data\model.h>

// シェーダ
#include <data\shader\line2d.h>

// ローダー
#include <system\loader\shader.h>

namespace Data
{
	namespace Model
	{
		class Line2d : public IModel
		{
		public:
			Shader::Line2d * shader_;
			Shader::Line2d::CBUFFER cb_;

		public:
			Line2d(void)
			{
				this->shader_ = Game::GetSystem<System::Loader::Shader>()->Get<Shader::Line2d>();
			}

		private:
			void Rendering(void) override
			{
				auto d2d = Game::GetSystem<System::Direct3D11>();
				auto window = Game::GetSystem<System::Window>();

				this->cb_.viewport_ = { window->Width<float>(), window->Height<float>() };

				this->cb_.color_ = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);

				this->shader_->Setup();
				this->shader_->UpdateConstantBuffer(0, &this->cb_);

				//バーテックスバッファーをセット
				UINT stride = sizeof(Shader::Line2d::Vertex);
				UINT offset = 0;

				d2d->context_->IASetVertexBuffers(0, 1, &this->shader_->vertex_buffer_, &stride, &offset);
				//プリミティブ・トポロジーをセット
				d2d->context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
				//プリミティブをレンダリング
				d2d->context_->Draw(2, 0);
			}
		};
	}
}