#pragma once

// ƒf[ƒ^
#include <data\shader.h>

namespace Data
{
	namespace Shader
	{
		class ShadeSpecularTex : public IShader
		{
		public:
			struct Vertex
			{
				Vertex(D3DXVECTOR3 position, D3DXVECTOR3 normal, D3DXVECTOR2 uv) : position_(position), normal_(normal), uv_(uv) {}
				D3DXVECTOR3 position_;
				D3DXVECTOR3 normal_;
				D3DXVECTOR2 uv_;
			};

			struct CBUFFER
			{
				D3DXMATRIX w_;
				D3DXMATRIX v_;
				D3DXMATRIX p_;

				D3DXVECTOR4 light_dir_;
				D3DXCOLOR diffuse_;
				D3DXVECTOR4 eye_;
			};

		public:
			ID3D11Buffer * vertex_buffer_;

		public:
			ShadeSpecularTex(void)
			{
				D3D11_INPUT_ELEMENT_DESC layout[] =
				{
					{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
					{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
					{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				};
				UINT num_elements = sizeof(layout) / sizeof(layout[0]);
				this->Create("shade_specular_tex", layout, num_elements);
				this->CreateConstantBuffer<CBUFFER>(0);
			}
		};
	}
}