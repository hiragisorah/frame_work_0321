#pragma once

// システム
#include <system\direct3d11.h>
#include <system\camera.h>

// データ
#include <data\model.h>

// シェーダ
#include <data\shader\shade_specular_tex.h>

// ローダー
#include <system\loader\shader.h>
#include <system\loader\fbx.h>

namespace Data
{
	namespace Model
	{
		class Fbx : public IModel
		{
		public:
			Fbx * parent = nullptr;
			std::vector<Fbx*> children_;
			Data::Fbx * model_ = nullptr;
			Shader::ShadeSpecularTex * shader_ = nullptr;
			Shader::ShadeSpecularTex::CBUFFER cb_;

		public:
			Fbx(void) {}
			Fbx(Data::Fbx * model) : model_(model)
			{
				this->shader_ = Game::GetSystem<System::Loader::Shader>()->Get<Shader::ShadeSpecularTex>();

				for (auto child : this->model_->children_)
					this->children_.emplace_back(new Fbx(child));
			}
			~Fbx(void)
			{
				for (auto child : this->children_)
					delete child;
			}

		public:
			void Init(std::string file_name)
			{
				this->shader_ = Game::GetSystem<System::Loader::Shader>()->Get<Shader::ShadeSpecularTex>();
				this->model_ = Game::GetSystem<System::Loader::Fbx>()->Get(file_name);

				for (auto child : this->model_->children_)
					this->children_.emplace_back(new Fbx(child));
			}

		public:
			void AddToDrawList(void)
			{
				Game::GetSystem<System::Direct3D11>()->AddToDrawList(this);

				for (auto child : this->children_)
				{
					child->AddToDrawList();
					child->cb_ = this->cb_;
				}
			}

		private:
			void Rendering(void) override
			{
				if (!this->model_->mesh_.index_buffer_) return;

				if (this->model_->texture_ != "")
					this->shader_->SetTexture(0, this->model_->texture_);

				auto d3d = Game::GetSystem<System::Direct3D11>();
				auto camera = Game::GetSystem<System::Camera>();

				this->cb_.v_ = camera->GetView();
				this->cb_.p_ = camera->GetProjection();

				this->cb_.diffuse_ = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);

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