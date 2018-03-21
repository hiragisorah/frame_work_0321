#pragma once

// データ
#include <data\mesh.h>

// シェーダ
#include <data\shader\default3d.h>

namespace Data
{
	namespace Mesh
	{
		class Triangle3d : public IMesh
		{
		public:
			Triangle3d(void)
			{
				std::vector<Shader::Default3d::Vertex> vertices;

				vertices.emplace_back(D3DXVECTOR3(-.5f, -.5f, .0f));
				vertices.emplace_back(D3DXVECTOR3(0.0f, +.5f, .0f));
				vertices.emplace_back(D3DXVECTOR3(+.5f, -.5f, .0f));

				this->CreateVertexBuffer(&vertices);
			}
		};
	}
}