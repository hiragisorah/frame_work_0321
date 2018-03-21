#pragma once

// データ
#include <data\shader.h>

namespace Data
{
	namespace Shader
	{
		class Line2d : public IShader
		{
		public:
			struct Vertex
			{
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
			Line2d(void)
			{
				auto d2d = Game::GetSystem<System::Direct3D11>();

				D3D11_INPUT_ELEMENT_DESC layout[] =
				{
					{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				};
				UINT num_elements = sizeof(layout) / sizeof(layout[0]);
				this->Create("default2d", layout, num_elements);
				this->CreateConstantBuffer<CBUFFER>(0);

				//バーテックスバッファー作成
				Vertex vertices[] =
				{
					D3DXVECTOR3(+100.0f, +100.0f, .0f),
					D3DXVECTOR3(-100.0f, -100.0f, .0f),
				};

				D3D11_BUFFER_DESC bd;
				bd.Usage = D3D11_USAGE_DEFAULT;
				bd.ByteWidth = sizeof(Vertex) * (sizeof(vertices) / sizeof(vertices[0]));
				bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				bd.CPUAccessFlags = 0;
				bd.MiscFlags = 0;

				D3D11_SUBRESOURCE_DATA init_data;
				init_data.pSysMem = vertices;

				if (FAILED(d2d->device_->CreateBuffer(&bd, &init_data, &this->vertex_buffer_)))
					Utils::EndMsg("頂点バッファーの生成に失敗しました");
			}
		};
	}
}