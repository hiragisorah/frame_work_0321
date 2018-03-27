#pragma once

// システム
#include <system\direct3d11.h>

// SDK
#include <D3DX10.h>
#include <D3DX11.h>

namespace Data
{
	struct Texture
	{
		ID3D11ShaderResourceView * resource_ = nullptr;
		D3DXVECTOR2 size_ = { 0.f, 0.f };

		Texture(std::string file_name, bool full_path = false)
		{
			if(!full_path)
				file_name = "resource/texture/" + file_name;

			auto d3d = Game::GetSystem<System::Direct3D11>();

			D3DX11CreateShaderResourceViewFromFileA(d3d->device_, file_name.c_str(), nullptr, nullptr, &this->resource_, nullptr);
			
			if (this->resource_ != nullptr)
			{
				D3DX11_IMAGE_INFO dii;
				D3DX11GetImageInfoFromFileA(file_name.c_str(), nullptr, &dii, nullptr);
				this->size_.x = (float)dii.Width;
				this->size_.y = (float)dii.Height;
			}
			else
			{
				Utils::EndMsg("ファイルの読み込みに失敗しました。(" + file_name + ")");
			}
		}
	};
}