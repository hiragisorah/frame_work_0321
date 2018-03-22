#pragma once

// システム
#include <system\direct3d11.h>
#include <system\camera.h>

// データ
#include <data\model.h>

// シェーダ
#include <data\shader\common.h>

// ローダー
#include <system\loader\shader.h>
#include <system\loader\mesh.h>

namespace Data
{
	namespace Model
	{
		template<class _Mesh>
		class CommonPrimitive3D : public IModel
		{
		public:
			IMesh * mesh_;
			Shader::Common * shader_;
			Shader::Common::CBUFFER cb_;

		public:
			CommonPrimitive3D(void)
			{
				this->shader_ = Game::GetSystem<System::Loader::Shader>()->Get<Shader::Common>();
				this->mesh_ = Game::GetSystem<System::Loader::Mesh>()->Get<_Mesh>();
			}

		private:
			void Rendering(void) override
			{
				auto d3d = Game::GetSystem<System::Direct3D11>();
				auto camera = Game::GetSystem<System::Camera>();

				D3DXMATRIX wvp;
				
				wvp = this->cb_.w_ * camera->GetView() * camera->GetProjection();
				D3DXMatrixTranspose(&wvp, &wvp);
				this->cb_.wvp_ = wvp;
				
				this->cb_.diffuse_ = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
				auto light = D3DXVECTOR3(0.f, 0.f, 1.f);
				D3DXVec3Normalize(&light, &light);
				this->cb_.light_dir_ = (D3DXVECTOR4)(light);
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