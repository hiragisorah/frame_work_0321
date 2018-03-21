#pragma once

// データ
#include <data\mesh.h>

// シェーダ
#include <data\shader\default3d.h>

namespace Data
{
	namespace Mesh
	{
		class Point3d : public IMesh
		{
		public:
			Point3d(void)
			{
				std::vector<Shader::Default3d::Vertex> vertices;

				vertices.emplace_back(D3DXVECTOR3(0.0f, 0.0f, .0f));

				this->CreateVertexBuffer(&vertices);
			}
		};
	}
}