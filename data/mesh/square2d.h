#pragma once

// データ
#include <data\mesh.h>

// シェーダ
#include <data\shader\default2d.h>

namespace Data
{
	namespace Mesh
	{
		class Square2d : public IMesh
		{
		public:
			Square2d(void)
			{
				std::vector<Shader::Default2d::Vertex> vertices;

				vertices.emplace_back(D3DXVECTOR3(+100.f, -100.f, .0f));
				vertices.emplace_back(D3DXVECTOR3(-100.f, -100.f, .0f));
				vertices.emplace_back(D3DXVECTOR3(+100.f, +100.f, .0f));
				vertices.emplace_back(D3DXVECTOR3(-100.f, +100.f, .0f));

				this->CreateVertexBuffer(&vertices, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
			}
		};
	}
}