#pragma once

// システム
#include <system\direct3d11.h>

// データ
#include <data\model.h>

// シェーダ
#include <data\shader\default2d.h>

// ローダー
#include <system\loader\shader.h>

namespace Data
{
	namespace Model
	{
		class Triangle2d : public IModel
		{
		public:
			Shader::Default2d * shader_;
			Shader::Default2d::CBUFFER cb_;

		public:
			Triangle2d(void)
			{
				this->shader_ = Game::GetSystem<System::Loader::Shader>()->Get<Shader::Default2d>();

				std::vector<Shader::Default2d::Vertex> vertices;

				vertices.emplace_back(D3DXVECTOR3(-100.0f, -100.0f, .0f));
				vertices.emplace_back(D3DXVECTOR3(0.0f, 100.0f, .0f));
				vertices.emplace_back(D3DXVECTOR3(+100.0f, -100.0f, .0f));

				Game::GetSystem<System::Direct3D11>()->CreateVertexBuffer(this, &vertices);
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

				d3d->context_->IASetVertexBuffers(0, 1, &this->vertex_buffer_, &this->stride_, &this->offset_);
				//プリミティブ・トポロジーをセット
				d3d->context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				//プリミティブをレンダリング
				d3d->context_->Draw(this->vtx_num_, 0);
			}
		};
	}
}