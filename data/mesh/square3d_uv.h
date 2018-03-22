#pragma once

// データ
#include <data\mesh.h>

// シェーダ
#include <data\shader\sprite.h>

namespace Data
{
	namespace Mesh
	{
		class Square3dUv : public IMesh
		{
		public:
			Square3dUv(void)
			{
				std::vector<Shader::Sprite::Vertex> vertices;

				vertices.emplace_back(D3DXVECTOR3(-.5f, +.5f, .0f), D3DXVECTOR2(1.f, 0.f));
				vertices.emplace_back(D3DXVECTOR3(+.5f, +.5f, .0f), D3DXVECTOR2(0.f, 0.f));
				vertices.emplace_back(D3DXVECTOR3(-.5f, -.5f, .0f), D3DXVECTOR2(1.f, 1.f));
				vertices.emplace_back(D3DXVECTOR3(+.5f, -.5f, .0f), D3DXVECTOR2(0.f, 1.f));

				this->CreateVertexBuffer(&vertices, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
			}
		};
	}
}