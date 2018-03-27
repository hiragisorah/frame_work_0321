#pragma once

// システム
#include <system\direct3d11.h>
#include <system\camera.h>

// データ
#include <data\model.h>

// メッシュ
#include <data\mesh\triangle3d.h>

// シェーダ
#include <data\shader\default3d.h>

// ローダー
#include <system\loader\shader.h>
#include <system\loader\obj.h>

namespace Data
{
	namespace Model
	{
		class Obj : public IModel
		{
		public:
			IObj * model_ = nullptr;
			Shader::Default3d * shader_ = nullptr;
			Shader::Default3d::CBUFFER cb_;

		public:
			Obj(void) {}

		public:
			void Init(std::string file_name)
			{
				this->shader_ = Game::GetSystem<System::Loader::Shader>()->Get<Shader::Default3d>();
				this->model_ = Game::GetSystem<System::Loader::Obj>()->Get(file_name);
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

				d3d->context_->IASetVertexBuffers(0, 1, &this->model_->mesh_.vertex_buffer_, &this->model_->mesh_.stride_, &this->model_->mesh_.offset_);
				d3d->context_->IASetIndexBuffer(this->model_->mesh_.index_buffer_, DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
				//プリミティブ・トポロジーをセット
				d3d->context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				//プリミティブをレンダリング
				d3d->context_->DrawIndexed(this->model_->mesh_.index_num_, 0, 0);
			}
		};
	}
}