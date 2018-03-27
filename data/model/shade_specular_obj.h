#pragma once

// システム
#include <system\direct3d11.h>
#include <system\camera.h>

// データ
#include <data\obj.h>

// シェーダ
#include <data\shader\shade_specular.h>

// ローダー
#include <system\loader\shader.h>
#include <system\loader\obj.h>

namespace Data
{
	namespace Model
	{
		class ShadeSpecularObj : public IModel
		{
		public:
			IObj * model_ = nullptr;
			Shader::ShadeSpecular * shader_ = nullptr;
			Shader::ShadeSpecular::CBUFFER cb_;

		public:
			ShadeSpecularObj(void) {}

			void Init(std::string file_name)
			{
				this->shader_ = Game::GetSystem<System::Loader::Shader>()->Get<Shader::ShadeSpecular>();
				this->model_ = Game::GetSystem<System::Loader::Obj>()->Get(file_name);
			}

		private:
			void Rendering(void) override
			{
				auto d3d = Game::GetSystem<System::Direct3D11>();
				auto camera = Game::GetSystem<System::Camera>();

				this->cb_.v_ = camera->GetView();
				this->cb_.p_ = camera->GetProjection();

				this->cb_.diffuse_ = { 1.f, 0.f, 0.f, 1.f };

				this->cb_.light_dir_ = { 0.f, .5f, -1.f, 0.f };
				this->cb_.eye_ = { camera->eye_, 0.f };

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