#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

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
		class Font : public IModel
		{
		public:
			IObj * model_ = nullptr;
			Shader::Default3d * shader_ = nullptr;
			Shader::Default3d::CBUFFER cb_;

		public:
			Font(void) {}

			void Init(std::string file_name)
			{
				this->shader_ = Game::GetSystem<System::Loader::Shader>()->Get<Shader::Default3d>();
				this->model_ = Game::GetSystem<System::Loader::Obj>()->Get(file_name);

				ID3D11Resource * pRes;

				file_name = "resource/font/" + file_name;

				FILE * fp = fopen(file_name.c_str(), "rb");

				auto d3d = Game::GetSystem<System::Direct3D11>();

				fpos_t pos;
				fseek(fp, 0, SEEK_END);
				fgetpos(fp, &pos);
				fseek(fp, 0, SEEK_SET);
				fclose(fp);

				unsigned int fsize = (unsigned int)pos;
				
				HRESULT hr = D3DX11CreateTextureFromMemory(
					d3d->device_,
					fp,
					fsize,
					nullptr,
					nullptr,
					&pRes,
					nullptr);

				ID3D11Texture2D * tex2d = static_cast<ID3D11Texture2D*>(pRes);

				// テクスチャ情報を取得する
				D3D11_TEXTURE2D_DESC texDesc;
				tex2d->GetDesc(&texDesc);

				// ShaderResourceViewの情報を作成する
				D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
				ZeroMemory(&srvDesc, sizeof(srvDesc));
				srvDesc.Format = texDesc.Format;
				srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
				srvDesc.Texture2D.MostDetailedMip = 0;
				srvDesc.Texture2D.MipLevels = texDesc.MipLevels;

				// ShaderResourceViewを作成する
				hr = d3d->device_->CreateShaderResourceView(tex2d, &srvDesc, &resourceView);
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