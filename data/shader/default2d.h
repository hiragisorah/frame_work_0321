#pragma once

// ƒf[ƒ^
#include <data\shader.h>

namespace Data
{
	namespace Shader
	{
		class Default2d : public IShader
		{
		public:
			struct Vertex
			{
				Vertex(D3DXVECTOR3 position) : position_(position) {}
				D3DXVECTOR3 position_;
			};

			struct CBUFFER
			{
				ALIGN16 D3DXMATRIX w_;
				ALIGN16 D3DXVECTOR2 viewport_;

				ALIGN16 D3DXCOLOR color_;
			};

		public:
			ID3D11Buffer * vertex_buffer_;

		public:
			Default2d(void)
			{
				D3D11_INPUT_ELEMENT_DESC layout[] =
				{
					{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				};
				UINT num_elements = sizeof(layout) / sizeof(layout[0]);
				this->Create("default2d", layout, num_elements);
				this->CreateConstantBuffer<CBUFFER>(0);
			}
		};
	}
}