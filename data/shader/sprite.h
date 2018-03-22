#pragma once

// ƒf[ƒ^
#include <data\shader.h>

namespace Data
{
	namespace Shader
	{
		class Sprite : public IShader
		{
		public:
			struct Vertex
			{
				Vertex(D3DXVECTOR3 position, D3DXVECTOR2 uv) : position_(position), uv_(uv) {}
				D3DXVECTOR3 position_;
				D3DXVECTOR2 uv_;
			};

			struct CBUFFER
			{
				D3DXMATRIX w_;
				D3DXMATRIX v_;
				D3DXMATRIX p_;

				D3DXCOLOR color_;
			};

		public:
			ID3D11Buffer * vertex_buffer_;

		public:
			Sprite(void)
			{
				D3D11_INPUT_ELEMENT_DESC layout[] =
				{
					{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
					{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				};
				UINT num_elements = sizeof(layout) / sizeof(layout[0]);
				this->Create("sprite", layout, num_elements);
				this->CreateConstantBuffer<CBUFFER>(0);
			}
		};
	}
}