#pragma once

// データ
#include <data\mesh.h>

// シェーダ
#include <data\shader\default2d.h>

namespace Data
{
	namespace Mesh
	{
		class Line2d : public IMesh
		{
		public:
			Line2d(void)
			{
				std::vector<Shader::Default2d::Vertex> vertices;

				vertices.emplace_back(D3DXVECTOR3(+100.0f, 0.0f, .0f));
				vertices.emplace_back(D3DXVECTOR3(-100.0f, 0.0f, .0f));

				this->CreateVertexBuffer(&vertices);
			}
		};
	}
}