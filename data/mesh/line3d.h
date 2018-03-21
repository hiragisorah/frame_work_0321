#pragma once

// データ
#include <data\mesh.h>

// シェーダ
#include <data\shader\default3d.h>

namespace Data
{
	namespace Mesh
	{
		class Line3d : public IMesh
		{
		public:
			Line3d(void)
			{
				std::vector<Shader::Default3d::Vertex> vertices;

				vertices.emplace_back(D3DXVECTOR3(+.5f, 0.0f, .0f));
				vertices.emplace_back(D3DXVECTOR3(-.5f, 0.0f, .0f));

				this->CreateVertexBuffer(&vertices);
			}
		};
	}
}