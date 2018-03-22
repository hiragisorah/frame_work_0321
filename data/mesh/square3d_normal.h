#pragma once

// データ
#include <data\mesh.h>

// シェーダ
#include <data\shader\common.h>

namespace Data
{
	namespace Mesh
	{
		class Square3dNormal : public IMesh
		{
		public:
			Square3dNormal(void)
			{
				std::vector<Shader::Common::Vertex> vertices;

				vertices.emplace_back(D3DXVECTOR3(-.5f, +.5f, .0f), D3DXVECTOR3(0.f, 0.f, 1.f));
				vertices.emplace_back(D3DXVECTOR3(+.5f, +.5f, .0f), D3DXVECTOR3(0.f, 0.f, 1.f));
				vertices.emplace_back(D3DXVECTOR3(-.5f, -.5f, .0f), D3DXVECTOR3(0.f, 0.f, 1.f));
				vertices.emplace_back(D3DXVECTOR3(+.5f, -.5f, .0f), D3DXVECTOR3(0.f, 0.f, 1.f));

				this->CreateVertexBuffer(&vertices, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
			}
		};
	}
}